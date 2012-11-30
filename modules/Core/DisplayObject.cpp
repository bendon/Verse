#include "DisplayObject.h"

namespace Core {

DisplayObject::DisplayObject()
{
	type="DisplayObject";
	alpha=1;
    visible=true;
	this->setVisibleMode(Devices::BOTH_EYES);
}

int DisplayObject::hitTestObject()
{
    return 0;
}

int DisplayObject::hitTestPoint()
{
    return 0;
}

void DisplayObject::draw(int selection)
{
	
}

void DisplayObject::render(int selection)
{
	Devices::Platform *platform=Devices::Platform::Instance();
	if(visible && (visibleMode==Devices::BOTH_EYES || visibleMode==platform->getActualMode()))
    {
		//Save position for x
		float tempX=x;
	    if(selection)
                glLoadName(id);
		if(visibleMode==Devices::BOTH_EYES){
			if(platform->getActualMode()==Devices::LEFT_EYE){
				x=tempX+25;
			}else if(platform->getActualMode()==Devices::RIGHT_EYE){
				x=tempX-25;
			}
		}
		draw(selection);
		//Restore X position
		x=tempX;

		for(int i=0; i<childs.size(); i++)
		{
			DisplayObject* child=childs[i];
			child->mouse_x=mouse_x;
			child->mouse_y=mouse_y;
			child->render(selection);	
		}
		
    }
}

void DisplayObject::addChild(DisplayObject* object)
{
	childs.push_back(object);
}

void DisplayObject::removeChild(DisplayObject* object)
{
	int i=0;
	for(i=0; i<childs.size(); i++)
	{
		DisplayObject* testChild=childs[i];
		if(testChild==object)
			break;
	}	
	childs.erase(childs.begin()+i);
}

void DisplayObject::setBackgroundColor(int r, int g, int b)
{
	red=(float)r/255.0f;
	green=(float)g/255.0f;
	blue=(float)b/255.0f;
}

void DisplayObject::setColor(int r, int g, int b)
{
	fred=(float)r/255.0f;
	fgreen=(float)g/255.0f;
	fblue=(float)b/255.0f;
}


void DisplayObject::setVisibleMode(int mode){
	visibleMode=mode;
	for(int i=0; i<childs.size(); i++)
	{
		DisplayObject* child=childs[i];
		child->setVisibleMode(mode);	
	}

}

void DisplayObject::setPosition(float x, float y, float z){
	this->x=x;
	this->y=y;
	this->z=z;

}

void DisplayObject::setOrthographicProjection(int pick) {
    /*
    //Get viewport resolution
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    // switch to projection mode
    glMatrixMode(GL_PROJECTION);

    // save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();

    // reset matrix
    glLoadIdentity();

    // set a 2D orthographic projection
    gluOrtho2D(0, viewport[2], 0, viewport[3]);

    // invert the y axis, down is positive
    glScalef(1, -1, 1);

    // mover the origin from the bottom left corner
    // to the upper left corner
    glTranslatef(0, -viewport[3], 0);

    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
    */
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    if (pick)
		gluPickMatrix(mouse_x,  viewport[3]-mouse_y, 1.0, 1.0, viewport);
    glOrtho(0, viewport[2], viewport[3], 0, -5, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DisplayObject::restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();
	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

DisplayObject* DisplayObject::searchChildId(int idObject)
{
	if(id==idObject){
		return this;
	}else{
		for(int i=0; i<childs.size(); i++)
		{
			DisplayObject* child=childs[i];
			DisplayObject* objectSel=child->searchChildId(idObject);
			if(objectSel!=NULL)
				return objectSel;
		}
	}
	return NULL;

	
}

} /* End of namespace Core */
