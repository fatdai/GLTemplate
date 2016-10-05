//
//  Quaternion.h
//  GLFW_DrawTriangle
//
//  Created by dai on 16/10/3.
//
//

#ifndef __GLFW_DrawTriangle__Quaternion__
#define __GLFW_DrawTriangle__Quaternion__

#include <stdio.h>


// 四元数
// 其中x，y，z用来确定旋转轴，w为旋转的角度
/*
重要结论:
     1.如果 q 是一个单位四元数,则 q^2 = 1,并且 q^-1 = q^*
     2.如果我们想要把空间的一个点P绕着单位向量轴u = (x, y, z)表示的旋转轴旋转θ角度，我们首先把点P扩展到四元数空间，即四元数p = (P, 0)。那么，旋转后新的点对应的四元数（当然这个计算而得的四元数的实部为0，虚部系数就是新的坐标）为：p′=q * p * q^-1,其中 q=((Ux,Uy,Uz)sinθ/2, cosθ/2)
 
*/
class Quaternion{
public:
    
    float x;
    float y;
    float z;
    float w;
    
    Quaternion();
    Quaternion(float px,float py,float pz,float pw);
    
    // 四元数 乘法
    Quaternion operator*(const Quaternion& other);
    
    // 共轭
    Quaternion conjugate();
    
    // 模长
    float length();
    void normalize();
    
    
};

#endif /* defined(__GLFW_DrawTriangle__Quaternion__) */
