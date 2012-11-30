#ifndef UI_Menu_h
#define UI_Menu_h



#include <Core/DisplayObject.h>
#include <Core/Callback.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include <Events/MenuEvent.h>

#include <Utils/XML.h>
#include <UI/MenuItem.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <string>
#include <vector>

namespace UI {

using std::string;
using std::vector;

class MenuItem;
class Menu : public Core::DisplayObject {
	public:
		Menu(string xmlfile, freetype::font_data* f, freetype::font_data* fbutton);
		void draw(int selection=0);
                
                Core::TCallback<Menu> menuClickCallBack;
		
                void onClick(Events::Event *ev);
		void onClickItem(Events::Event *ev);
                int show;
                void addMenuSubitem(MenuItem *m);
                vector<string> path;
                string name;
                
	private:
		vector<MenuItem*> items;		
		Utils::XML *xmlData;
                TextField *textField;
                freetype::font_data* font;
                freetype::font_data* fontButton;
                int inLevel;
};

} /* End of namespace UI */

#endif // UI_Menu_h
