#ifndef UI_Dialog_h
#define UI_Dialog_h


#include <Core/DisplayObject.h>
#include <Events/Event.h>
#include <Events/MouseEvent.h>
#include "Draw2D.h"
#include "Button.h"
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

/**
* Dialog popup box with buttons. Show a Dialog with ok and cancel buttons with text description inside.
* @image html dialog.jpg
* Common use:
* @code //Create dialog
* dialog=new UI::Dialog(&font, &font11);
* dialog->height=150;
* dialog->width=300;
* dialog->x=100;
* dialog->y=100;
* dialog->hide();
* addChild(dialog);
* //Show dialog
* dialog->show("Title", "Text inside dialog\\nOther line");
* @endcode
* @see freetype::font_data
* @see UI::TextField
* @see UI::Button
*/
class Dialog : public Core::DisplayObject {
	public:
                Dialog(freetype::font_data* f, freetype::font_data* ftext);
		void draw(int selection=0);
		void setTitle(string t);
		void setText(string t);
		void show(string t, string txt);
		void hide();
		void setWidth(int w);
		freetype::font_data* font;
		freetype::font_data* fontText;
                TextField *titleTextField;
		TextField *textField;
		Button *okButton;
		Button *cancelButton;
                
                Core::TCallback<Dialog> cancelClickCallBack;
                void onClickCancel(Events::Event *ev);
                
                Core::TCallback<Dialog> okClickCallBack;
                void onClickOk(Events::Event *ev);
                
                
	private:
		int headerHeight, footerHeight ;
		string title;
		string text;
};

} /* End of namespace UI */

#endif
