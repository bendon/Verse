#ifndef Core_DisplayObject_h
#define Core_DisplayObject_h

#include "EventDispatcher.h"
#include <Devices/Platform.h>

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#include <vector>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace Core {

class DisplayObject : public EventDispatcher {

 public:
    DisplayObject();
    virtual int hitTestObject();
    virtual int hitTestPoint();
    virtual void draw(int selection=0);
    void render(int selection=0);
    void addChild(DisplayObject *object);
    void removeChild(DisplayObject *object);
    void setOrthographicProjection(int pick);
    void restorePerspectiveProjection();
    void setBackgroundColor(int r, int g, int b);
    void setColor(int r, int g, int b);
    DisplayObject* searchChildId(int idObject);
    void setVisibleMode(int mode);
	void setPosition(float x, float y, float z);

 public:
    int visible;
	int visibleMode;
    float x;
    float y;
    int width;
    int height;
    float z;
    float scalex;
    float scaley;
    float scalez;
    float rotationx;
    float rotationy;
    float rotationz;
    int rotion;
    float red,green, blue;
    float fred,fgreen, fblue;
    float alpha;
    int blendMode;
    int mouse_x, mouse_y;
    std::vector<DisplayObject*> childs;
        
};

} /* End of namespace Core */

#endif // Core_DisplayObject_h
