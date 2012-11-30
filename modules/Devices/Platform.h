#ifndef Devices_Device_h
#define Devices_Device_h

#include <Core/EventDispatcher.h>

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

	enum							{ LEFT_EYE=0, RIGHT_EYE, MONO_EYES, BOTH_EYES };
	enum							{ MONO, PROGRESSIVE_SCAN, SIDE_X_SIDE };
	#define SEPARATION_CHANGE		0.01f
	#define MINIMUM_SEPARATION		0.01f
	#define DEFAULT_SEPARATION		0.25f
	#define FOCAL_LENGTH_CHANGE		0.5f
	#define DEFAULT_FOCAL_LENGTH	10.0f
	#define MINIMUM_FOCAL_LENGTH	4.0f
	#define DEGREESTORADIANS		0.0174532925f


class Platform : public Core::EventDispatcher {

 public:
	static Platform* Instance();
	cv::Mat getFrame(int cam=0);

	void SetViewingFrustum(int EYE);
	void SetStereoViewport(int eye);
	int getActualMode();
	int getNumCameras();
	int Init();

	float		g_EyeSeparation;// Intraocular Distance: aka, Distance between left and right cameras.
	float		g_FocalLength;	// Screen projection plane: aka, focal length(distance to front of virtual screen).
	GLdouble	g_CameraXPosition, g_CameraYPosition, g_CameraZPosition;
	int			stereo_mode;
	int			mode;
	
protected:
	Platform();
    static Platform* pinstance;
	int numCameras;
 
private:
	
 public:
    int resolutionX;
    int resolutionY;
    
    //OpenCV capture Inputs
    cv::VideoCapture* Cam1;
    cv::VideoCapture* Cam2;
};

} /* End of namespace Devices */

#endif // Devices_Device_h
