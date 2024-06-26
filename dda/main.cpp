#include<windows.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<math.h>

void Draw()
{
    GLfloat x1=100,y1=100,x2=500,y2=100;
    GLfloat M,p,dx,dy,x,y,t;
    glClear(GL_COLOR_BUFFER_BIT);

    if((x2-x1)==0)
       M = (y2-y1);
    else
        M = (y2-y1)/(x2-x1);

    if(fabs(M)<1)
    {
        if(x1>x2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2-x1);
        dy = fabs(y2-y1);

        p = 2*dy-dx;

        x=x1;
        y=y1;

        glBegin(GL_POINTS);
            while(x<=x2)
            {
              glVertex2f(x,y);
              x=x+1;

              if(p>=0)
              {
                 if(M<1)
                    y=y+1;
                else
                    y=y-1;
                 p = p+2*dy-2*dx;
              }
              else
              {
                  y=y;
                  p = p+2*dy;
              }
            }
        glEnd();
    }

    if(fabs(M)>=1)
    {
        if(y1>y2)
        {
            t = x1;
            x1 = x2;
            x2 = t;

            t = y1;
            y1 = y2;
            y2 = t;
        }

        dx = fabs(x2-x1);
        dy = fabs(y2-y1);

        p = 2*dx-dy;

        x=x1;
        y=y1;

        glBegin(GL_POINTS);
            while(y<=y2)
            {
              glVertex2f(x,y);
              y=y+1;

              if(p>=0)
              {
                 if(M>=1)
                    x=x+1;
                else
                    x=x-1;
                 p = p+2*dx-2*dy;
              }
              else
              {
                  x=x;
                  p = p+2*dx;
              }
            }
        glEnd();
    }

    glFlush();
}

void MyInit()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,500,0,500);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argC,char *argV[])
{
    glutInit(&argC,argV);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Bresenhamís Line Drawing Algo");
    MyInit();
    glutDisplayFunc(Draw);
    glutMainLoop();
    return 0;
}
