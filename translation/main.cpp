#include <iostream>
#include <windows.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <cmath>
// Function to multiply two 3x3 matrices
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

    // Draw X-axis
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
        {0.1f, 0.3f, 0.6f},  // x coordinates
        {0.1f, 0.7f, 0.1f},  // y coordinates
        {1.0f, 1.0f, 1.0f}    // homogeneous coordinates
    };
    // Draw original triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Blue color for original triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(vertices[0][i], vertices[1][i]);
    }
    glEnd();

    float translation[3][3] = {
        {1.0f, 0.0f, -0.7f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };

    float translated[3][3];
    multiplyMatrices(translation, vertices, translated);

    // Draw translated triangle
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 0.0); // Yellow color for translated triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(translated[0][i], translated[1][i]);
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Translation Transformation");
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    gluOrtho2D(-1, 1, -1, 1); // Coordinate system setup
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
