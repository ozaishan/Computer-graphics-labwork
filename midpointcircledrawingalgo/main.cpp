#include <iostream>
#include <cmath>
#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

int centerX = 350, centerY = 350, radius = 150;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x + centerX, y + centerY);
    glVertex2i(-x + centerX, y + centerY);
    glVertex2i(x + centerX, -y + centerY);
    glVertex2i(-x + centerX, -y + centerY);
    glVertex2i(y + centerX, x + centerY);
    glVertex2i(-y + centerX, x + centerY);
    glVertex2i(y + centerX, -x + centerY);
    glVertex2i(-y + centerX, -x + centerY);
    glEnd();
}

void midpointCircle() {
    int x = 0;
    int y = radius;
    int p = 1 - radius;

    plot(x, y);

    while (x < y) {
        x++;
        if (p < 0)
            p += 2 * x + 1;
        else {
            y--;
            p += 2 * (x - y) + 1;
        }
        plot(x, y);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    midpointCircle();
    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, 700, 0, 700);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Midpoint Circle Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
