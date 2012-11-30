/* 
 * File:   GLBaseApp.h
 * Author: damiles
 *
 * Created on 23 de enero de 2012, 21:40
 */

#ifndef GLBASEAPP_H
#define	GLBASEAPP_H



#include <Core/DisplayObject.h>
#include <Events/MouseEvent.h>
#include <Devices/Platform.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif


namespace UI {



class GLBaseApp: public Core::DisplayObject  {
public:
    GLBaseApp();
    //GLBaseApp(const GLBaseApp& orig);
	GLBaseApp(Devices::Platform *p);
    virtual ~GLBaseApp();
    void render();
    void mouseEvent(int button, int state, int x, int y);
    void selection(Events::MouseEvent e);
	Devices::Platform *platform;
        
private:
    
};
}
#endif	/* GLBASEAPP_H */

