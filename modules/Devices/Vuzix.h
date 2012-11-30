#ifndef Devices_Vuzix_h
#define Devices_Vuzix_h

//Vuzix SDK
//#define IWEAR_ONETIME_DEFINITIONS
#include <iWearSDK.h>

#include <stdio.h>

#include <Core/EventDispatcher.h>
#include <Devices/Platform.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace Devices {

	#define IWR_OK					0 // Ok 2 go with tracker driver.
	#define IWR_NO_TRACKER			1 // Tracker Driver is NOT installed.
	#define IWR_OFFLINE				2 // Tracker driver installed, yet appears to be offline or not responding.
	#define IWR_TRACKER_CORRUPT		3 // Tracker driver installed, and missing exports.
	#define IWR_NOTRACKER_INSTANCE	4 // Tracker driver did not open properly.
	#define IWR_NO_STEREO			5 // Stereo driver not loaded.
	#define IWR_STEREO_CORRUPT		6 // Stereo driver exports incorrect.
	enum							{ IWR_NOT_CONNECTED=-1, IWR_IS_CONNECTED };

class Vuzix : public Platform {

 public:
	static Vuzix* Instance();
	
	void SetStereoViewport(int eye);
	void UpdateTracking();
	float getYaw();
	float getPitch();
	float getRoll();
	int Init();
	void Vuzix::SetViewingFrustum( int Eye );
	
protected:
	Vuzix();
	//static Vuzix* pinstance_vuzix;
     
private:
	HANDLE		g_StereoHandle;
	bool		g_StereoEnabled;
	bool		g_tracking;		// True = enable head tracking
	int			g_Filtering;			// Provide very primitive filtering process.
	int			Pid;
	DWORD		PDetails;
	bool		usingWrap;
	int			iwr_status;
	int			g_ProdSubID;
	int			g_ProdAspect;
	int			g_ProdTrackerStyle;
	float g_fPitch, g_fRoll, g_fYaw;
 public:
    
};

} /* End of namespace Devices */

#endif // Devices_Vuzix_h
