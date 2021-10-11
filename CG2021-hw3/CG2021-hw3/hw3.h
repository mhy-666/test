#include<GL/glut.h>
#include<math.h>
#include<vector>
#include<iostream>

using namespace std;

const int WindowWidth = 600, WindowHeight = 600;

/************************************************************************/
/* 中点线画圆                                                            */
/************************************************************************/
void CirclePoints(int CenterX, int CenterY, int x, int y)
{
    glVertex2i(x + CenterX, y + CenterY);
    glVertex2i(y + CenterX, x + CenterY);
    glVertex2i(-y + CenterX, x + CenterY);
    glVertex2i(-x + CenterX, y + CenterY);
    glVertex2i(y + CenterX, -x + CenterY);
    glVertex2i(x + CenterX, -y + CenterY);
    glVertex2i(-x + CenterX, -y + CenterY);
    glVertex2i(-y + CenterX, -x + CenterY);
    cout << x + CenterX << "," << y + CenterY << ";";
    cout << y + CenterX << "," << x + CenterY << ";";
    cout << -y + CenterX << "," << x + CenterY << ";";
    cout << -x + CenterX << "," << y + CenterY << ";";
    cout << y + CenterX << "," << -x + CenterY << ";";
    cout << x + CenterX << "," << -y + CenterY << ";";
    cout << -x + CenterX << "," << -y + CenterY << ";";
    cout << -y + CenterX << "," << -x + CenterY << ";";
}

void MidPointCircle(int CenterX, int CenterY, int r)
{
    //绘制第一象限偏上部分的八分之一圆
    int x = 0;
    int y = r;
    float d = 1.25 - r;
    CirclePoints(CenterX, CenterY, x, y);
    //45°界限
    while (x < y)
    {
        x++;
        if (d <= 0)
        {
            d += 2 * x + 3;
        }
        else
        {
            d += 2 * (x - y) + 5;
            y--;
        }
        CirclePoints(CenterX, CenterY, x, y);
    }
}


/************************************************************************/
/* Bresenham画圆                                                  */
/************************************************************************/
void BresenhamPointCircle(int CenterX, int CenterY, int r)
{
    vector<pair<int, int>> result;
    int x, y, d, d1, d2, direction;
    x = 0, y = r;
    d = 2 * (1 - r);
    CirclePoints(CenterX, CenterY, x, y);
    while (x <= y)
    {
        if (d < 0)
        {
            d1 = 2 * (d + y) - 1;
            if (d1 <= 0)
            {
                direction = 1;
            }
            else
            {
                direction = 2;
            }
        }
        else if (d > 0)
        {
            d2 = 2 * (d - x) - 1;
            if (d2 <= 0)
            {
                direction = 2;
            }
            else
            {
                direction = 3;
            }
        }
        else
        {
            direction = 2;
        }


        switch (direction)
        {
        case 1:
        {
            x++;
            d += 2 * x + 1;
            break;
        }
        case 2:
        {
            x++;
            y--;
            d += 2 + (x - y + 1);
            break;
        }
        case 3:
        {
            y--;
            d += 1 - 2 * y;
            break;
        }
        }
        CirclePoints(CenterX, CenterY, x, y);
    }
}

/************************************************************************/
/* 中点线绘制椭圆算法                                                     */
/************************************************************************/
void EllipsePoints(int CenterX, int CenterY, int x, int y)
{
    glVertex2i(x + CenterX, y + CenterY);
    glVertex2i(-x + CenterX, y + CenterY);
    glVertex2i(x + CenterX, -y + CenterY);
    glVertex2i(-x + CenterX, -y + CenterY);
    cout << x + CenterX << "," << y + CenterY << ";";
    cout << -x + CenterX << "," << y + CenterY << ";";
    cout << x + CenterX << "," << -y + CenterY << ";";
    cout << -x + CenterX << "," << -y + CenterY << ";";
}

void MidpointEllipse(int CenterX, int CenterY, int a, int b)
{
    double d2, d1 = pow(b, 2) - (pow(a, 2) * b) + 0.25 * pow(a, 2);
    int x = 0, y = b;
    EllipsePoints(CenterX, CenterY, x, y);

    //梯度检测
    while (pow(a, 2) * (y - 0.5) > pow(b, 2) * (x + 1))
    {
        //在区域一
        if (d1 < 0)
        {
            d1 += pow(b, 2) * (2 * x + 3);
        }
        else
        {
            d1 += pow(b, 2) * (2 * x + 3) + pow(a, 2) * (-2 * y + 2);
            y--;
        }
        x++;
        EllipsePoints(CenterX, CenterY, x, y);

    }
    d2 = pow(b, 2) * pow(x + 0.5, 2) + pow(a, 2) * pow(y - 1, 2) - pow(a * b, 2);
    while (y > 0)       //区域二
    {
        if (d2 < 0)
        {
            d2 += pow(b, 2) * (2 * x + 2) + pow(a, 2) * (-2 * y + 3);
            x++;
        }
        else
        {
            d2 += pow(a, 2) * (-2 * y + 3);
        }
        y--;
        EllipsePoints(CenterX, CenterY, x, y);
    }
}



void draw1()
{
    glBegin(GL_POINTS);
    //中点线画圆，圆为蓝色
    glColor3f(0.4, 0.5, 1);
    MidPointCircle(250, 250, 200);
    cout << endl  << "一次循环结束" << endl;
    glEnd();
    glFlush();
}
void draw2()
{

    glBegin(GL_POINTS);
    //Bresenham绘制圆,圆为白色

    glColor3f(1, 1, 1);
    BresenhamPointCircle(250, 250, 200);
    cout << endl << "一次循环结束" << endl;
    glEnd();
    glFlush();
}
void draw3()
{
    glBegin(GL_POINTS);
    glColor3f(1, 0.5, 0.7);
    MidpointEllipse(250, 250, 249, 200);
    cout << endl << "一次循环结束" << endl;
    glEnd();
    glFlush();
}

void resetSize(int w, int h)
{
    glutReshapeWindow(WindowWidth, WindowHeight);
}

void init()
{
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WindowWidth, WindowHeight);
    glutCreateWindow("cg2021");
    gluOrtho2D(0, WindowWidth, 0, WindowHeight);
    glutReshapeFunc(resetSize);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.1, 0.1, 0.1);
    glBegin(GL_LINES);
    glVertex2i(-WindowWidth, 0);
    glVertex2i(WindowWidth, 0);
    glVertex2i(0, -WindowHeight);
    glVertex2i(0, WindowHeight);
    glEnd();
}

