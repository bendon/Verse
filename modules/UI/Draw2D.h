#ifndef UI_Draw2D_h
#define UI_Draw2D_h

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

namespace UI {

class Draw2D{
	public:
		static void Rectangle(int x, int y, int width, int height);
		static void RoundedRectangle(int x, int y, int width, int height, int radius);
                static void drawLine2D(int x1, int y1, int x2, int y2);
};

}

#endif // UI_Button_h
