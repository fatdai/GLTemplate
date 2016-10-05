//
//  Texture.cpp
//  Lighting
//
//  Created by dai on 16/10/4.
//
//

#include "Texture.h"
#include <FreeImage.h>
#include <malloc/malloc.h>
#include <stdlib.h>

typedef struct
{
    int         w;
    int             h;
    unsigned char           *buf;
    GLuint          rgb_mode;
}GLBITMAP;

//  FreeImage可以帮你解析他所支持的图片文件，但OpenGL创建纹理函数glTexImage2D却有个问题，
//  最后一个参数(像素数据指针)中不需要进行行对齐, 而且会根据format参数决定RGB格式(主要有GL_RGB和GL_RGBA),
//  而且OpenGL像素rgb的顺序是低位存red, 高位存blue，这个和一般的解析库的像素存取是相反的,
//  综合上述，简单的写了一个将FreeImage的bitmap转换成OpenGL需要的bitmap格式的函数
GLBITMAP * FIBitmap2GLBitmap(FIBITMAP *fibmp)
{
    int i, j, k;
    int pitch = FreeImage_GetPitch(fibmp);
    unsigned char *bits = FreeImage_GetBits(fibmp);
    int bpp = FreeImage_GetBPP(fibmp);
    GLBITMAP *glbmp = (GLBITMAP *)malloc(sizeof(GLBITMAP));
    RGBQUAD *palette = NULL;
    
    if ( !glbmp ) return NULL;
    
    glbmp->w = FreeImage_GetWidth(fibmp);
    glbmp->h = FreeImage_GetHeight(fibmp);
    
    switch ( bpp ) {
        case 8:
            if ( !(palette = FreeImage_GetPalette(fibmp)) ) return NULL;
            if ( !(glbmp->buf = (unsigned char *)malloc(glbmp->w*glbmp->h*3)) ) return NULL;
            glbmp->rgb_mode = GL_RGB;
            for ( i = 0; i < glbmp->h; ++i ) {
                for ( j = 0; j < glbmp->w; ++j ) {
                    k = bits[i*pitch+j];
                    glbmp->buf[(i*glbmp->w+j)*3+0] = palette[k].rgbRed;
                    glbmp->buf[(i*glbmp->w+j)*3+1] = palette[k].rgbGreen;
                    glbmp->buf[(i*glbmp->w+j)*3+2] = palette[k].rgbBlue;
                }
            }
            break;
        case 24:
            if ( !(glbmp->buf = (unsigned char *)malloc(glbmp->w*glbmp->h*3)) ) return NULL;
            glbmp->rgb_mode = GL_RGB;
            for ( i = 0; i < glbmp->h; ++i ) {
                for ( j = 0; j < glbmp->w; ++j ) {
                    glbmp->buf[(i*glbmp->w+j)*3+0] = bits[i*pitch+j*3+2];
                    glbmp->buf[(i*glbmp->w+j)*3+1] = bits[i*pitch+j*3+1];
                    glbmp->buf[(i*glbmp->w+j)*3+2] = bits[i*pitch+j*3+0];
                }
            }
            break;
        case 32:
            if ( !(glbmp->buf = (unsigned char *)malloc(glbmp->w*glbmp->h*4)) ) return NULL;
            glbmp->rgb_mode = GL_RGBA;
            for ( i = 0; i < glbmp->h; ++i ) {
                for ( j = 0; j < glbmp->w; ++j ) {
                    glbmp->buf[(i*glbmp->w+j)*4+0] = bits[i*pitch+j*4+2];
                    glbmp->buf[(i*glbmp->w+j)*4+1] = bits[i*pitch+j*4+1];
                    glbmp->buf[(i*glbmp->w+j)*4+2] = bits[i*pitch+j*4+0];
                    glbmp->buf[(i*glbmp->w+j)*4+3] = bits[i*pitch+j*4+3];
                }
            }
            break;
        default: return NULL;
    }
    
    return glbmp;
}

void FreeGLBitmap(GLBITMAP *glbmp)
{
    if ( glbmp ) {
        if ( glbmp->buf ) free(glbmp->buf);
        free(glbmp);
    }
}


FIBITMAP* LoadImage(const char* fileName){
    
    FreeImage_SetOutputMessage([](FREE_IMAGE_FORMAT fif, const char *msg){
        printf("\n*** ");
        if(fif != FIF_UNKNOWN) {
            printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
        }
        printf("%s",msg);
        printf(" ***\n");
    });
    
    FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
    fif = FreeImage_GetFileType(fileName, 0);
    if ( FIF_UNKNOWN == fif ) {
        fif = FreeImage_GetFIFFromFilename(fileName);
        if ( FIF_UNKNOWN == fif ){
            printf("不支持的格式!\n");
        }
    }
    
    if (fif != FIF_UNKNOWN  && FreeImage_FIFSupportsReading(fif)){
        auto bitmap = FreeImage_Load(fif,fileName,0);
        if (bitmap == nullptr) {
            printf("读取纹理失败!\n");
        }else{
            printf("读取纹理成功!\n");
            return bitmap;
        }
    }else{
        printf("不支持的格式!\n");
    }
    return nullptr;
}

//---------------------------------------------
#pragma mark Texture 实现开始
Texture::Texture(GLenum textureTarget,const std::string& filename){
    mTextureTarget = textureTarget;
    mFileName = filename;
}

bool Texture::load(){
    
    // 1. 先加载得到 fibitmap
    FIBITMAP* bitmap = LoadImage(mFileName.c_str());
    if (bitmap == nullptr) {
        printf("read texture %s error!\n",mFileName.c_str());
        return false;
    }
    
    // 2. 转成 GLBitmap
    GLBITMAP* glbmp = FIBitmap2GLBitmap(bitmap);
    if (!glbmp) {
        printf("change fibitmap to gl bitmap error!\n");
        return false;
    }
    

    glGenTextures(1,&mTextureObj);
    glBindTexture(mTextureTarget,mTextureObj);
    glTexParameteri(mTextureTarget,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(mTextureTarget,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(mTextureTarget,0,glbmp->rgb_mode,glbmp->w,glbmp->h,0,glbmp->rgb_mode,GL_UNSIGNED_BYTE,glbmp->buf);
    glBindTexture(mTextureTarget,0);
    
    // 3. 释放内存
    FreeGLBitmap(glbmp);
    FreeImage_Unload(bitmap);

    return true;
}
void Texture::bind(GLenum textureUnit){
    glActiveTexture(textureUnit);
    glBindTexture(mTextureTarget,mTextureObj);
}