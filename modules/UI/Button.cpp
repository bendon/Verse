#include "Button.h"

namespace UI {

    Button::Button()
    {
        textField=NULL;
        rounded=true;
        overRed=overGreen=overBlue=0;
        //Define our events
        overCallBack.SetCallback(this, &Button::onOver);
        addEventListener(Events::MouseEvent::MOUSE_OVER, &overCallBack);
        isOver=false;
    }
    
Button::Button(string l, freetype::font_data* f )
{
	type="Button"; 
     rounded=true;
        font=f;
        
	label=l;
	textField=new TextField(label, f, TextField::HORIZONTAL);
	textOffsetY=textOffsetX=4;
	addChild(textField);
	
        overRed=overGreen=overBlue=0;
       //Define our events
        overCallBack.SetCallback(this, &Button::onOver);
        addEventListener(Events::MouseEvent::MOUSE_OVER, &overCallBack);
        isOver=false;
        
}

void Button::onOver(Events::Event *ev){
    isOver=true;
}

void Button::setPosition(float x, float y){
	this->x=x;
	this->y=y;
	if(textField){
		textField->x=x+textOffsetX;
		textField->y=y+textOffsetY;
    }
	
}

void Button::draw(int selection)
{
	if(textField){
		textField->setColor(this->fred*255,this->fgreen*255, this->fblue*255);
	}
    setOrthographicProjection(selection);
        if(isOver)
            glColor4f(overRed, overGreen, overBlue, alpha);	
        else
            glColor4f(red, green, blue, alpha);	
	if(rounded)
		Draw2D::RoundedRectangle(x,y,width,height,height/4);
	else
		Draw2D::Rectangle(x,y,width,height);

	glColor3f(255,255,255);
	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
