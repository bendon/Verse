#include "Vuzix.h"

namespace Devices {
	//Vuzix* Vuzix::pinstance=0;
	Vuzix* Vuzix::Instance()
	{
		Vuzix* pinstance_vuzix ;
		if (pinstance == 0 )
		{
				pinstance_vuzix = new Vuzix;
				pinstance=dynamic_cast<Platform*>(pinstance_vuzix);
		}
		return pinstance_vuzix;	
	}
    Vuzix::Vuzix(){
		//Variables initializations
		g_StereoHandle	= INVALID_HANDLE_VALUE;
		g_StereoEnabled = true;
		g_tracking		= false;		// True = enable head tracking
		g_Filtering		= 0;			// Provide very primitive filtering process.
		Pid				= 0;
		PDetails		= 0;
		usingWrap		= false;
		iwr_status		= IWR_OK;
		g_ProdSubID		= 0;
		g_ProdAspect	= 0;
		g_ProdTrackerStyle	= 0;

		

    }
    
	int Vuzix::Init(){
		//Load DLL Vuzix
		iwr_status = IWRLoadDll();
		if( iwr_status != IWR_OK ) {
			std::cout << "[ERROR][VUZIX] NO VR920 iwrdriver support" << std::endl;
			IWRFreeDll();
			return 0;
		}

		// Handle stereo setup
		g_StereoHandle = IWRSTEREO_Open();
		if( g_StereoHandle == INVALID_HANDLE_VALUE ) {
			if (GetLastError() == ERROR_INVALID_FUNCTION) 
				std::cout << "[ERROR][VUZIX] Your VR920 firmware does not support stereoscopy.  Please update your firmware.\n" << std::endl;
			else 
				std::cout <<  "[ERROR][VUZIX] NO VR920 Stereo Driver handle\n" << std::endl;
			IWRFreeDll();
			return 0;
		}
		// Look for proc address...Ask for device installed on users system, set/clear sidexside
		if( IWRGetProductID ) 
			Pid = IWRGetProductID();
		// Check the capabilities of the connected hardware
		if( IWRGetProductDetails ) 
			PDetails = IWRGetProductDetails();
	
		// If the hardware can do SxS stereo or Progressive Scan, set them here
		if (PDetails & IWR_FEATURE_SIDE_X_SIDE)
			stereo_mode = SIDE_X_SIDE;
		else if (PDetails & IWR_FEATURE_USB_PSCAN_3D)
			stereo_mode = PROGRESSIVE_SCAN;

		g_ProdSubID = IWR_GET_SUBID(PDetails);
		g_ProdAspect = IWR_GET_ASPECT_RATIO(PDetails);
		g_ProdTrackerStyle = IWR_GET_TRACKER_STYLE(PDetails);

		//Init cameras
        Cam1 = new cv::VideoCapture(1);
        Cam2 = new cv::VideoCapture(2);
		
		Cam1->set(CV_CAP_PROP_FRAME_WIDTH,320);
		Cam2->set(CV_CAP_PROP_FRAME_WIDTH,320);
		Cam1->set(CV_CAP_PROP_FRAME_HEIGHT,240);
		Cam2->set(CV_CAP_PROP_FRAME_HEIGHT,240);
		
		Cam1->set(CV_CAP_PROP_EXPOSURE,-3);
		Cam2->set(CV_CAP_PROP_EXPOSURE,-3);
		

		g_EyeSeparation = DEFAULT_SEPARATION;
		g_FocalLength	= DEFAULT_FOCAL_LENGTH;	
		g_CameraXPosition=0.0f, g_CameraYPosition=0.0f, g_CameraZPosition=0.0f;
		mode=MONO;

		//Force to glasses to set stereo mode.
		if( g_StereoHandle == INVALID_HANDLE_VALUE ) {
			g_StereoEnabled = false;
		}else{
			if (g_StereoEnabled)
				IWRSTEREO_SetStereo( g_StereoHandle, IWR_STEREO_MODE );
			else 
				IWRSTEREO_SetStereo( g_StereoHandle, IWR_MONO_MODE );				
		}

		return 1;
	}

	void Vuzix::UpdateTracking(){
		// Poll input devices.
		long	Roll=0,Yaw=0, Pitch=0;
		iwr_status = IWRGetTracking( &Yaw, &Pitch, &Roll );
		if(	iwr_status != IWR_OK ){
			// iWear tracker could be OFFLine: just inform user, continue to poll until its plugged in...
			g_tracking = false;
			Yaw = Pitch = Roll = 0;
			IWROpenTracker();
		}
		// Always provide for a means to disable filtering;
		//Not implemented see OpenGL vuzix sample 
		/*
		if( g_Filtering == APPLICATION_FILTER){ 
			IWRFilterTracking( &Yaw, &Pitch, &Roll ); 
		}
		*/

		// Convert the tracker's inputs to angles
		g_fPitch =  (float)Pitch * IWR_RAWTODEG; 
		g_fYaw   =  (float)Yaw * IWR_RAWTODEG;
		g_fRoll  =  (float)Roll * IWR_RAWTODEG;
	}

	float Vuzix::getYaw(){
		return g_fYaw;
	}
	float Vuzix::getPitch(){
		return g_fPitch;
	}
	float Vuzix::getRoll(){
		return g_fRoll;
	}

	//
	// Set up the perspective frustum based on window properties
	// StereoScopic Mode: 
	//		Sets up an off-axis projection considering Eye separation and focal length.
	// MonoScopic Mode:
	//		Uses the same projection method with parameters to center the monoscopic 
	//      view along the viewing axis.
	//
	void Vuzix::SetViewingFrustum( int Eye )
	{
		GLfloat		fovy	= 45.0;                                          //field of view in y-axis
		GLfloat		aspect	= float(this->resolutionX)/float(this->resolutionY);    //screen aspect ratio
		GLfloat		nearZ	= 1.0;                                        //near clipping plane
		GLfloat		farZ	= 1000.0;                                      //far clipping plane
		GLfloat		top		= nearZ * tan( DEGREESTORADIANS * fovy / 2);     
		GLdouble	right	= aspect * top;                             
		GLdouble	frustumshift= (g_EyeSeparation / 2) * nearZ / g_FocalLength;
		GLdouble	leftfrustum, rightfrustum, bottomfrustum, topfrustum;
		GLfloat		modeltranslation;

		switch( Eye ) {
			case LEFT_EYE:
				// Setup left viewing frustum.
				topfrustum		= top;
				bottomfrustum	= -top;
				leftfrustum		= -right + frustumshift;
				rightfrustum	= right + frustumshift;
				modeltranslation= g_EyeSeparation / 2;
			break;
			case RIGHT_EYE:
				// Setup right viewing frustum.
				topfrustum		= top;
				bottomfrustum	= -top;
				leftfrustum		= -right - frustumshift;
				rightfrustum	= right - frustumshift;
				modeltranslation= -g_EyeSeparation / 2;
			break;
			case MONO_EYES:
				// Setup mono viewing frustum.
				topfrustum		= top;
				bottomfrustum	= -top;
				leftfrustum		= -right;
				rightfrustum	= right;
				modeltranslation= 0.0f;
			break;
		}
		// Initialize off-axis projection if in stereoscopy mode.
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();                  
		glFrustum(leftfrustum, rightfrustum, bottomfrustum, topfrustum,	nearZ, farZ);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		// Translate Camera to cancel parallax.
		glTranslated(modeltranslation, 0.0f, 0.0f);
		// Add headtracking from VR920 tracker.
		if (g_tracking){		// if tracking is enabled, apply pitch, roll, and yaw.
			glRotated(-g_fPitch, 1.0, 0.0, 0.0);
			glRotated(g_fRoll, 0.0, 0.0, 1.0);
			glRotated(-g_fYaw, 0.0, 1.0, 0.0);
			}
		// Translate camera to global viewing position. 
		glTranslated(g_CameraXPosition, g_CameraYPosition, g_CameraZPosition);
	}


} /* End of namespace Devices */
