#include<windows.h>
#include<GL/glut.h>
#include<math.h>

void Draw()
{
    GLfloat x1=10,y1=10,x2=200,y2=100;
    GLfloat dx, dy, steps, xIncrement, yIncrement, x, y;
    dx = x2 - x1;
    dy = y2 - y1;

    if (fabs(dx) > fabs(dy))
        steps = fabs(dx);
    else
        steps = fabs(dy);

    xIncrement = dx / steps;
    yIncrement = dy / steps;
    x = x1;
    y = y1;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int i = 0; i < steps; i++)
    {
        glVertex2f(x, y);
        x += xIncrement;
        y += yIncrement;
    }
    glEnd();
    glFlush();
}

void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,1000,0,1000);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argC,char *argV[])
{
    glutInit(&argC,argV);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("DDA Line Drawing Algorithm");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
