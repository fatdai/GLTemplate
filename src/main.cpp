//
//  main.cpp
//  GL_01
//
//  Created by dai on 16/7/7.
//  Copyright (c) 2016年 mac. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "DrawTriangle.h"
#include "Vec3.h"
#include "Quaternion.h"
#include "Mat.h"
#include <vector>
#include "TestGLSL.h"
#include "MyDefines.h"
#include "BasicTech.h"
#include "MyHead.h"
#include "TestOnlyVBO.h"
using namespace std;

/*
// 主要opengl版本改为 opengl 3.3  glsl 330 版本
// 使用 vao
// 添加了 gl3w 去加载 opengl 扩展
// 不需要使用 glew
// Question : 使用 core profile 非要使用vao?

// 第一步:实现一些基本的 3d 效果
 1. ads 光照  聚光灯
 2. shadow map
 3. normal map
 4. 天空盒
 5. billboard
 6. 粒子系统
 7. 拾取
 8. 延迟渲染
 9. 骨骼动画
 10. 轮廓检查
 11. 模板阴影体
 12. 运动模糊
 13. ssao
 14. 水的效果
 15. 简单的物理引擎
 16. 场景管理 octree
 17. 地形系统
 18. gui
 19. 2d 3d文字
 20. navMesh
 21. 实现2个小游戏(空战,赛艇)
 22. 阅读 ogre 源码

 git:
 git remote add origin https://github.com/fatdai/GLTemplate.git
 git push -u origin master
 
*/
int main(int argc,  char * argv[]) {

    DrawTriangle app("Test");
    app.runGame();
    
    return 0;
}












