#include <iostream>
#include<cmath>
#include<windows.h>
		#include <GL/glu.h>
		#include <GL/glut.h>

void paraboladrawingalgo(GLfloat x1, GLfloat y1, GLfloat fc) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    GLfloat x, y, p10, p1k, p20, p2k;
    x = 0;
    y = 0;
    p10 = 1 - 2 * fc;
    p1k = p10;

    while (y < (2 * fc)) {
        if (p1k < 0) {
            x = x + 0;
            y = y + 1;
            p1k = p1k + 2 * y + 1;
        } else {
            x = x + 1;
            y = y + 1;
            p1k = p1k + 2 * y + 1 - 4 * fc;
        }
        glVertex2f(x, y);
        glVertex2f(x, -y);
    }

    p20 = (y + 1 / 2) * (y + 1 / 2) - 4 * fc * (x + 1);
    p2k = p20;

    while (x < x1 || y < y1) {
        if (p2k < 0) {
            x = x + 1;
            y = y + 1;
            p2k = p2k + 2 * y - 4 * fc;
        } else {
            x = x + 1;
            y = y + 0;
            p2k = p2k - 4 * fc;
        }
        glVertex2f(x, y);
        glVertex2f(x, -y);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    paraboladrawingalgo(-200, -200, 30);
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Parabola Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
