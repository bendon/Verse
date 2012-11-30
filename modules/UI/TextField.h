#ifndef UI_TextField_h
#define UI_TextField_h



#include <Core/DisplayObject.h>
#include <Devices/Platform.h>
#include "Draw2D.h"
#include "FreeType.h"

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
using std::vector;

class TextField : public Core::DisplayObject {
	public:
		TextField(string label, freetype::font_data* f, int v);
		void draw(int selection=0);
		string label;
        int vertical;
        void setText(string text);
        void setWidth(int w);

	private:
		freetype::font_data *font;
		vector<string> lines;
                
public:
    static const int VERTICAL;
    static const int HORIZONTAL;


};

} /* End of namespace UI */

#endif // UI_Button_h
