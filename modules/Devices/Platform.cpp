#include "Platform.h"

namespace Devices {
	Platform* Platform::pinstance=0;
	Platform* Platform::Instance()
	{
		if (pinstance == 0 )
		{
				pinstance = new Platform;
		}
		return pinstance;	
	}
    Platform::Platform(){
		
    }
	int Platform::Init(){
		numCameras=0;
        Cam1 = new cv::VideoCapture(0);
		if(Cam1){
			numCameras++;
			Cam1->set(CV_CAP_PROP_FRAME_WIDTH,640);
			Cam1->set(CV_CAP_PROP_FRAME_HEIGHT,480);
			//Cam1->set(CV_CAP_PROP_EXPOSURE,0);
		}
		Cam2 = new cv::VideoCapture(0);
		if(Cam2){
			numCameras++;
			Cam2->set(CV_CAP_PROP_FRAME_WIDTH,320);
			Cam2->set(CV_CAP_PROP_FRAME_HEIGHT,240);
		}
		
		g_EyeSeparation = DEFAULT_SEPARATION;
		g_FocalLength	= DEFAULT_FOCAL_LENGTH;	
		g_CameraXPosition=0.0f, g_CameraYPosition=0.0f, g_CameraZPosition=0.0f;
		stereo_mode=MONO;
		mode=MONO;
		
		return true;
	}
    cv::Mat Platform::getFrame(int cam){
        cv::Mat img;
		
        if(cam==0){
            if (Cam1->grab()){
                    Cam1->retrieve(img, 0);
            }
        }
		if(cam==1){
            if (Cam2->grab()){
                    Cam2->retrieve(img, 0);
            }
        }
        return img;
    }

	int Platform::getNumCameras(){
		return numCameras;
	}

	void Platform::SetStereoViewport(int eye){
		if (eye == LEFT_EYE){
			glViewport( 0, 0, resolutionX/2, resolutionY );
			this->mode=eye;
		} else if (eye == RIGHT_EYE) {
			glViewport( resolutionX/2, 0, resolutionX/2, resolutionY );
			this->mode=eye;
		} else {
			glViewport( 0, 0, resolutionX, resolutionY );
			this->mode=MONO_EYES;
		}
	}

	int Platform::getActualMode(){
		return this->mode;
	}

	//
	// Set up the perspective frustum based on window properties
	// StereoScopic Mode: 
	//		Sets up an off-axis projection considering Eye separation and focal length.
	// MonoScopic Mode:
	//		Uses the same projection method with parameters to center the monoscopic 
	//      view along the viewing axis.
	//
	void Platform::SetViewingFrustum( int Eye )
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
		// Translate camera to global viewing position. 
		glTranslated(g_CameraXPosition, g_CameraYPosition, g_CameraZPosition);
	}


} /* End of namespace Devices */
