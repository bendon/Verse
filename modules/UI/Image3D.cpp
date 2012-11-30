/* 
 * File:   Image3D.cpp
 * Author: damiles
 * 
 * Created on 23 de enero de 2012, 22:11
 */

#include "Image3D.h"
namespace UI {
    
Image3D::Image3D() 
{
    
}

Image3D::Image3D(const Image3D& orig) 
{
}

Image3D::~Image3D() 
{
}

void Image3D::loadImage(const char* file)
{
    //Load image
    image=imread(file);
    refreshTexture();
}

void Image3D::loadImage(Mat img)
{
    image=img;
    refreshTexture();
}

void Image3D::refreshTexture()
{
    //Delete texture if exist
    if (&texture)
	glDeleteTextures(1, &texture);
    
    //Generate Texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    int dataSize=image.cols*image.rows*3;
    unsigned char* data=new unsigned char[dataSize];
    int j=0;
    for( int y = 0; y < image.rows; y++ )
    { 
        for( int x = 0; x < image.cols; x++ )
                 { 
                    for( int c = 0; c < 3; c++ )
                    {
                         data[j] = image.at<Vec3b>(y,x)[c];
                         j++;           
                    }
                 }
    }
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image.cols, image.rows, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    delete data;    
}
void Image3D::draw(int selection)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture( GL_TEXTURE_2D, texture ); //bind the texture
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0f+x,			0.0f+y,				z);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( (1.0f*scalex)+x,	0.0f+y,				z);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( (1.0f*scalex)+x,	(1.0f*scaley)+y,	z);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f+x,			(1.0f*scaley)+y,	z);  // Top Left Of The Texture and Quad
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
    
}

}
