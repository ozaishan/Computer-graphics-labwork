#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>

void multiplyMatrices(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0); // Black color for axes
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();

    // Draw Y-axis
    glBegin(GL_LINES);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    float vertices[3][3] = {
        {0.25, 0.25, 1.0},
        {0.5, 0.9, 1.0},
        {0.8, 0.3, 1.0}
    };

    // Draw original triangle in blue
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Blue color for original triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();

    float ang = 180 * 3.14159 / 180;

    float rotation[3][3]={
        {cos(ang), sin(ang), 0},
        {-sin(ang), cos(ang), 0},
        {0,0,1}
    };

    float rotated[3][3];

    multiplyMatrices(vertices, rotation, rotated);

    // Draw rotated triangle in red
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red color for rotated triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(rotated[i][0], rotated[i][1]);
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Rotation");
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    gluOrtho2D(-1, 1, -1, 1); // Coordinate system setup
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
