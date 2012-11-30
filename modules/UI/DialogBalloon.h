#ifndef UI_DialogBallon_h
#define UI_DialogBallon_h

#include <Core/DisplayObject.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include "Draw2D.h"
#include "FreeType.h"
#include "TextField.h"



#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>

namespace UI {

using std::string;

class DialogBalloon : public Core::DisplayObject {
	public:
                DialogBalloon(freetype::font_data* f, freetype::font_data* ftext);
		void draw(int selection=0);
		void setTitle(string t);
		void setText(string t);
		void setWidth(int w);
                void show(string t, string txt);
		void hide();
		
		freetype::font_data* font;
		freetype::font_data* fontText;
                TextField *titleTextField;
		TextField *textField;
	private:
		int headerHeight, footerHeight ;
		string title;
		string text;
};

} /* End of namespace UI */

#endif
