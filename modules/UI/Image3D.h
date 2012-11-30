/* 
 * File:   Image3D.h
 * Author: damiles
 *
 * Created on 23 de enero de 2012, 22:11
 */

#ifndef IMAGE3D_H
#define	IMAGE3D_H

#include <Core/DisplayObject.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

namespace UI {
    
    using namespace cv;
    
class Image3D: public Core::DisplayObject  {
public:
    Image3D();
    Image3D(const Image3D& orig);
    virtual ~Image3D();
    void draw(int selection=0);
    void loadImage(const char* file);
    void loadImage(Mat img);
    void refreshTexture();
    
private:
    GLuint texture;
    Mat image;

};
}
#endif	/* Image3D_H */

