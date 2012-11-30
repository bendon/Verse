/**
 * @file Model.h
 * @author   Augmate <info@augmate.com>
 * @version 0.1
 *
 * @section LICENSE
 *
 * Copyright © 2011, Augmate Corporation LLC.
 * This file is part of VERSE.
 * 
 * VERSE is free software: you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License 
 * as published by the Free Software Foundation, either version 3 
 * of the License, or (at your option) any later version.
 * 
 * VERSE is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty 
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with VERSE. If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * ToDo Description.
 */


#ifndef MODEL3D_H
#define MODEL3D_H

#ifdef WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <assimp.hpp>
#include <assimp.h>
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Core/DisplayObject.h>

#include <vector>

#include <iostream>


namespace UI {

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)

using namespace cv;

struct TextureAndPath
{
	GLuint hTexture;
	aiString pathName;
};

class Model3D : public Core::DisplayObject
{
public:
	std::vector<TextureAndPath> texturesAndPaths;
	std::string foldername;
	std::string texturename;
	const struct aiScene* scene;

	void recursiveTextureLoad(const struct aiScene *sc, const struct aiNode* nd);
	void recursive_render(const struct aiScene *sc, const struct aiNode* nd);

	void get_bounding_box_for_node(const struct aiNode* nd, struct aiVector3D* min, struct aiVector3D* max, struct aiMatrix4x4* trafo);
	void get_bounding_box(struct aiVector3D* min, struct aiVector3D* max);

	Model3D();
	~Model3D();

	void loadModel(const char* fileName);
	void draw(int selection);
        void setModelMatrix(double *matrix);

	struct aiVector3D min;
	struct aiVector3D max;
	float scale;
        
        double modelview_matrix[16];
};


void color4_to_float4(const struct aiColor4D *c, float f[4]);

void set_float4(float f[4], float a, float b, float c, float d);

void apply_material(const struct aiMaterial *mtl);

// Can't send color down as a pointer to aiColor4D because AI colors are ABGR.
void Color4f(const struct aiColor4D *color);
}
#endif
