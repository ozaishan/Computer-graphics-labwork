#include <iostream>
#include<windows.h>
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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);

    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 0.0); // Black color for axes
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    float vertices[3][3] = {
        {0.05, 0.3, 0.6},
        {0.05, 0.7, 0.1},
        {1, 1, 1}
    };

    // Draw original triangle in blue
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Blue color for original triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(vertices[0][i], vertices[1][i]);
    }
    glEnd();

    float scaling[3][3] = {
        {0.70, 0, 0},
        {0, 0.50, 0},
        {0, 0, 1}
    };

    float scaled[3][3];
    multiplyMatrices(scaling, vertices, scaled);

    // Draw scaled triangle in yellow
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 0.0); // Yellow color for scaled triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(scaled[0][i], scaled[1][i]);
    }
    glEnd();

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Scaling");
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    gluOrtho2D(-1, 1, -1, 1); // Coordinate system setup
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
