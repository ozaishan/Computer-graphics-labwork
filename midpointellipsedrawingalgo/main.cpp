#include <iostream>
#include <cmath>
#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

void drawEllipse(GLfloat x_center, GLfloat y_center, GLfloat rx, GLfloat ry) {
    glBegin(GL_POINTS);

    GLfloat x = 0, y = ry;
    GLfloat p10 = ry * ry - rx * rx * ry + (1.0 / 4) * rx * rx;
    GLfloat p1k = p10;

    glVertex2f(x + x_center, y + y_center);
    glVertex2f(-x + x_center, y + y_center);
    glVertex2f(x + x_center, -y + y_center);
    glVertex2f(-x + x_center, -y + y_center);

    while (2 * ry * ry * x < 2 * rx * rx * y) {
        if (p1k < 0) {
            x++;
            y = y;
            p1k = p1k + 2 * ry * ry * x + ry * ry;
        } else {
            x++;
            y--;
            p1k = p1k + 2 * ry * ry * x - 2 * rx * rx * y + ry * ry;
        }

        glVertex2f(x + x_center, y + y_center);
        glVertex2f(-x + x_center, y + y_center);
        glVertex2f(x + x_center, -y + y_center);
        glVertex2f(-x + x_center, -y + y_center);
    }

    GLfloat p20 = ry * ry * (x + 1 / 2) * (x + 1 / 2) + rx * rx * (y - 1) * (y - 1) - rx * rx * ry * ry;
    GLfloat p2k = p20;

    while (y != 0) {
        if (p2k <= 0) {
            x++;
            y--;
            p2k = p2k + 2 * ry * ry * x - 2 * rx * rx * y + rx * rx;
        } else {
            x = x;
            y--;
            p2k = p2k - 2 * rx * rx * y + rx * rx;
        }

        glVertex2f(x + x_center, y + y_center);
        glVertex2f(-x + x_center, y + y_center);
        glVertex2f(x + x_center, -y + y_center);
        glVertex2f(-x + x_center, -y + y_center);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    drawEllipse(0, 0, 350, 200); // input yeta rakhne center center rx,ry
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
    glutCreateWindow("Ellipse Drawing Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
