#include"hw3.h"
#include<iostream>

using namespace std;



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    cout << "请选择操作：1)中点法绘制圆 2)Bresenham绘制圆 3)中点法绘制椭圆";
    int x;
    cin >> x;
    if (x == 1)
        //draw1;
        glutDisplayFunc(draw1);
    if (x == 2)
        //draw2;
        glutDisplayFunc(draw2);
    if (x == 3)
        //draw3;
        glutDisplayFunc(draw3);
    glEnd();

    glutMainLoop();
    system("pause");
    return 0;
}