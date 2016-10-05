//
//  Technique.cpp
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#include "Technique.h"
#include "MyDefines.h"
#include <fstream>
#include <iostream>
using namespace std;

Technique::Technique(){
    mShaderProg = 0;
}

Technique::~Technique(){
    for (auto it = mShaderObjVector.begin(); it != mShaderObjVector.end(); ++it) {
        glDeleteShader(*it);
    }
    if (mShaderProg != 0) {
        glDeleteProgram(mShaderProg);
        mShaderProg = 0;
    }
}
bool Technique::init(){
    mShaderProg = glCreateProgram();
    if (mShaderProg == 0) {
        printf("Create shader program error!\n");
        return false;
    }
    return true;
}

bool Technique::addShader(GLenum shaderType,const char* fileName){
    
    //    std::string sources;
    //    loadFile(fileName,sources);
    //
    //    printf("--------------------------------------------------------\n");
    //    printf("code:\n%s\n",sources.c_str());
    //    printf("--------------------------------------------------------\n");
    //    printf("code:\n%ld\n",sources.size());
    
    GLuint shaderObj = glCreateShader(shaderType);
    if (shaderObj == 0) {
        printf("create shaderType : %d error!\n",shaderType);
        return false;
    }
    
    mShaderObjVector.push_back(shaderObj);
    
    string sources;
    loadFile(fileName,sources);
    
    const char* csource = sources.c_str();//loadShader(fileName);
    glShaderSource(shaderObj,1,&csource,NULL);
    glCompileShader(shaderObj);
    
    GLint success;
    glGetShaderiv(shaderObj,GL_COMPILE_STATUS,&success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shaderObj,1024,NULL,infoLog);
        printf("Compile shader error, error : %s\n",infoLog);
        return false;
    }
    
    glAttachShader(mShaderProg,shaderObj);
    return true;
}

void Technique::enable(){
    glUseProgram(mShaderProg);
}

bool Technique::linkAndValidate(){
    GLint success = 0;
    char errorLog[1024] = { 0 };
    
    CHECK_GL_ERROR();
    glLinkProgram(mShaderProg);
    glGetProgramiv(mShaderProg,GL_LINK_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(mShaderProg,1024,NULL,errorLog);
        printf("link program error. error : %s\n",errorLog);
        return false;
    }
    
    /*
     Question : Why does glValidateProgram fail when no VAO is bound?
     This behavior matches the OpenGL spec. I'm using the OpenGL 3.3 spec as reference.
     
     In appendix E.2.2 "Removed Features" on page 344, it says:
     
     The default vertex array object (the name zero) is also deprecated. Calling VertexAttribPointer when no buffer object or no vertex array object is bound will generate an INVALID_OPERATION error, as will calling any array drawing command when no vertex array object is bound.
     The spec for glValidateProgram() on page 82 says:
     
     ValidateProgram will check for all the conditions that could lead to an INVALID_OPERATION error when rendering commands are issued, and may check for other conditions as well.
     So because issuing a draw command without a VAO bound will given a GL_INVALID_OPERATION error, and glValidateProgram() checks if a draw command would give a GL_INVALID_OPERATION error, what you're seeing is exactly as expected.
     */
#if 0
    glValidateProgram(mShaderProg);
    glGetProgramiv(mShaderProg,GL_VALIDATE_STATUS,&success);
    if (!success) {
        glGetProgramInfoLog(mShaderProg,1024, NULL, errorLog);
        printf("validate program error. error : %s\n",errorLog);
        return false;
    }
#endif
    
    CHECK_GL_ERROR();
    return true;
}

GLint Technique::getAttribLocation(const char* attribName){
    GLint location = glGetAttribLocation(mShaderProg,attribName);
    if (location == -1) {
        printf("Warning! Unable to get the %s.\n",attribName);
    }
    return location;
}

GLint Technique::getUniformLocation(const char* uniformName){
    GLint location = glGetUniformLocation(mShaderProg,uniformName);
    if (location == -1) {
        printf("Warning! Unable to get the %s.\n",uniformName);
    }
    return location;
}

GLint Technique::getProgramParam(GLint param){
    GLint ret;
    glGetProgramiv(mShaderProg,param,&ret);
    return ret;
}


//const char* Technique::loadShader(const char* path)
//{
//    std::string out = "";
//    
//    std::ifstream in(path, std::ios::in);
//    std::string line = "";
//    if (in.is_open())
//    {
//        while (getline(in, line))
//        {
//            out += line + "\n";
//        }
//        
//        in.close();
//    }
//    return out.c_str();
//}

void Technique::loadFile(const char* fn,std::string& str){
    
    std::ifstream in(fn,std::ios::in);
    
#if 0
    std::istreambuf_iterator<char> beg(in), end;
    str = std::string(beg, end);
    in.close();
#endif
    
    if(!in.is_open())
    {
        std::cout << "The file " << fn << " cannot be opened\n";
        return;
    }
    char tmp[1024];
    while(!in.eof())
    {
        in.getline(tmp,1024);
        str+=tmp;
        str+='\n';
    }
    in.close();
}