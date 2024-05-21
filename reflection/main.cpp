#include <iostream>
#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
// Function to multiply two 3x3 matrices
void multiplyMatrices(float mat1[3][3], float mat2[3][3], float result[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i][j] = 0.0f;
            for (int k = 0; k < 3; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0);
    // Draw X axis
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-1.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glEnd();
    // Draw Y axis
    glBegin(GL_LINES);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(0.0f, 1.0f);
    glEnd();
    // Define the vertices of the smaller triangle
    float vertices[3][3] = {
        {0.1f, 0.1f, 1.0f},
        {0.2f, 0.4f, 1.0f},
        {0.3f, 0.1f, 1.0f}
    };
    // Reflection matrices
    float reflectionX[3][3] = {
        {1.0f, 0.0f, 0.0f},
        {0.0f, -1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    float reflectionY[3][3] = {
        {-1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f}
    };
    // Arrays to store reflected vertices
    float reflectedX[3][3];
    float reflectedY[3][3];
    // Perform matrix multiplication
    multiplyMatrices(vertices, reflectionX, reflectedX);
    multiplyMatrices(vertices, reflectionY, reflectedY);

    // Draw the original triangle in blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i) {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();

    // Draw the triangle reflected on the X axis in green
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i) {
        glVertex2f(reflectedX[i][0], reflectedX[i][1]);
    }
    glEnd();

    // Draw the triangle reflected on the Y axis in red
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i) {
        glVertex2f(reflectedY[i][0], reflectedY[i][1]);
    }
    glEnd();
    glFlush();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Reflection on X and Y Axis");
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
