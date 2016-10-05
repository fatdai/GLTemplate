简单的创造静态库的方法
g++ -c src/*.c -I./include
ar -crv libglew.a *.o