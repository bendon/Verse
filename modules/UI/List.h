#ifndef UI_List_h
#define UI_List_h



#include <Core/DisplayObject.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include "Draw2D.h"
#include "FreeType.h"
#include "TextField.h"
#include "Button.h"

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

class ListData{
public:
	//ListData();
	string icon;
	int status;
	string label;
	int id;
};

class List : public Core::DisplayObject {
	public:
        List();
		List(string title, vector<ListData> data, freetype::font_data* f);
		void setData(vector<ListData> data);
		void draw(int selection=0);
		vector<ListData> data;
		vector<Button*> buttons;
		freetype::font_data* font;
        TextField *textField;
		string label;
		void setPosition(float x, float y);
};

} /* End of namespace UI */

#endif // UI_List_h
