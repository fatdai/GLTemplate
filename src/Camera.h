//
//  Camera.h
//  BasicMove
//
//  Created by dai on 16/10/4.
//
//

#ifndef __BasicMove__Camera__
#define __BasicMove__Camera__

#include <stdio.h>
#include "MyHead.h"

// 第一人称相机
class Camera{
    
public:

    Camera();
    Camera(const Vec3& pos,const Vec3& head,const Vec3& up);
    
    void forward();
    void back();
    void left();
    void right();
    void lookUp();
    void lookDown();
    
    void update();
    
    const Mat& getViewMatrix(){
        return mViewMatrix;
    }
    
    const Vec3& getPos(){
        return mPos;
    }
    
private:
    
    Vec3 mPos;
    Vec3 mHead; // 注视的方向
    Vec3 mUp;
    Vec3 mLeft; // 相机的左边
    Mat mViewMatrix;
    
    int mDirty = 0;
};

#endif /* defined(__BasicMove__Camera__) */
