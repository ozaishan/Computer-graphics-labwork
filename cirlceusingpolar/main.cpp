
#include <cmath>
#include <iostream>
#include<windows.h>
		#include <GL/glu.h>
		#include <GL/glut.h>
int centerX = 350, centerY = 350, radius = 250;

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

void polarCircle() {
    float theta, dTheta = 1.0 / radius;
    for (theta = 0; theta <= 45; theta += dTheta) {
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        plot(round(x), round(y));
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    polarCircle();
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
    glutCreateWindow("Circle Drawing Algorithm (Polar Coordinates)");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
