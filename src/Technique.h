//
//  Technique.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef __GLFW_DrawTriangle__Technique__
#define __GLFW_DrawTriangle__Technique__

#include <stdio.h>
#include <vector>
#include "MyHead.h"


/*    用于继承,每一个子类先必须通过 init 函数初始化.
 然后调用 addShader , 然后通过 linkAndValidate 去链接验证 program.
 
 */
class Technique{
public:
    Technique();
    virtual ~Technique();
    virtual bool init();
    void enable();
    
private:
    
    void loadFile(const char* fn,std::string& str);
    //const char* loadShader(const char* path);
    
protected:
    
    
    bool addShader(GLenum shaderType,const char* fileName);
    bool linkAndValidate();
    
    GLint getUniformLocation(const char* uniformName);
    GLint getAttribLocation(const char* attribName);
    GLint getProgramParam(GLint param);
    
protected:
    
    GLuint mShaderProg;
    std::vector<GLuint> mShaderObjVector;
    
};

#endif /* defined(__GLFW_DrawTriangle__Technique__) */
