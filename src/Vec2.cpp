//
//  Vec2.cpp
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#include "Vec2.h"
#include <cmath>



Vec2::Vec2(){

}
Vec2::Vec2(float px,float py){
    x = px;
    y = py;
}
Vec2::Vec2(const Vec2& other){
    x = other.x;
    y = other.y;
}

// + - * /
Vec2 Vec2::operator+(const Vec2& other){
    return Vec2(other.x + x,other.y + y);
}
Vec2 Vec2::operator-(const Vec2& other){
    return Vec2(x - other.x,y - other.y);
}

float Vec2::operator*(const Vec2& other){
    return x * other.x + y * other.y;
}

float Vec2::length(){
    return sqrtf(x * x + y * y);
}

void Vec2::normalize(){
    float len = length();
    if (len > 0) {
        x /= len;
        y /= len;
    }
}

void Vec2::print(){
    printf("-------------------------------\n");
    printf("%.3f,%.3f\n",x,y);
}

// Global
bool operator==(const Vec2& v1,const Vec2& v2){
    if (v1.x == v2.x && v1.y == v2.y) {
        return true;
    }
    return false;
}


