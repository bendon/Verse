#include "List.h"

namespace UI {

    List::List()
    {
        textField=NULL;
    }
    
List::List(string title, vector<ListData> data, freetype::font_data* f)
{
	type="List"; 
    font=f;
    label=title;
	textField=new TextField(label, f, TextField::HORIZONTAL);
	addChild(textField);
	alpha=0.4;
	fred=fgreen=fblue=255;
	setData(data);
}

void List::setData(vector<ListData> data){
	this->data=data;
	
	//Remove last buttons
	for(int i=0; i< buttons.size(); i++){
		Button *b= buttons.at(i);
		removeChild(b);
	}
	buttons.erase(buttons.begin(),buttons.begin()+buttons.size());

	//Create new Buttons
	int startY=y+42;
	int heightButton=25;
	for(int i=0; i< data.size(); i++){
		ListData item=data.at(i);
		Button* b=new Button(item.label,font);
		b->rounded=false;
		b->setPosition(x,startY+i*heightButton);
		b->height=heightButton-1;
		b->textOffsetX=10;
		b->width=width;
		if(item.status==0)
			b->setColor(255,100,100);
		else if(item.status==1)
			b->setColor(100,255,100);
		else
			b->setColor(200,200,200);

		b->alpha=0.2;
		b->setVisibleMode(this->visibleMode);
		//Add button
		addChild(b);
	}
	

}

void List::setPosition(float x, float y){
	this->x=x;
	this->y=y;
	 if(textField){
		textField->setColor(this->fred,this->fgreen, this->fblue);
		textField->x=x+10;
		textField->y=y+13;
    }
}

void List::draw(int selection)
{
   
	if(textField){
		textField->setColor(this->fred,this->fgreen, this->fblue);
	}
	setOrthographicProjection(selection);
    glColor4f(red, green, blue, alpha);	
	Draw2D::Rectangle(x,y,width,height);
	
	glColor3f(255,255,255);

	glBegin(GL_LINES);
    glColor4f(1,1,1,0.5);glVertex2f(x , y+40);
    glColor4f(1,1,1,0);glVertex2f(x+width , y+40);
    glEnd();

	restorePerspectiveProjection();
	
}

} /* End of namespace UI */
