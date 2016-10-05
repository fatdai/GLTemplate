//
//  ShadowMapFBO.h
//  ShadowMap
//
//  Created by dai on 16/10/5.
//
//

#ifndef __ShadowMap__ShadowMapFBO__
#define __ShadowMap__ShadowMapFBO__

#include <stdio.h>
#include "MyHead.h"

class ShadowMapFBO{
public:
    
    ShadowMapFBO();
    ~ShadowMapFBO();
    
    bool init(unsigned int WindowWidth, unsigned int WindowHeight);
    void bindForWriting();
    void bindForReading(GLenum TextureUnit);
    
private:
    
    GLuint mFBO;
    GLuint mShadowMap;
};

#endif /* defined(__ShadowMap__ShadowMapFBO__) */
