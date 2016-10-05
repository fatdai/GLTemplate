//
//  Texture.h
//  Lighting
//
//  Created by dai on 16/10/4.
//
//

#ifndef __Lighting__Texture__
#define __Lighting__Texture__

#include <stdio.h>
#include <string>
#include "MyHead.h"
using namespace std;


class Texture{
public:
    
    Texture(GLenum textureTarget,const std::string& filename);
    bool load();
    void bind(GLenum textureUnit);
    
private:
    
    std::string mFileName;
    GLenum mTextureTarget;
    GLuint mTextureObj;
};


#endif /* defined(__Lighting__Texture__) */
