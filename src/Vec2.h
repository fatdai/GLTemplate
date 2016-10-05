//
//  Vec2.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef __GLFW_DrawTriangle__Vec2__
#define __GLFW_DrawTriangle__Vec2__

#include <stdio.h>

class Vec2{
    
public:
    float x = 0;
    float y = 0;
    
    Vec2();
    Vec2(float px,float py);
    Vec2(const Vec2& other);
    
    void normalize();
    float length();
    void print();
    
    // + - * /
    Vec2 operator+(const Vec2& other);
    Vec2 operator-(const Vec2& other);
    
    
    // 点乘
    float operator*(const Vec2& other);
};

bool operator==(const Vec2& v1,const Vec2& v2);

#endif /* defined(__GLFW_DrawTriangle__Vec2__) */
