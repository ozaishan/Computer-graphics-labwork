#include <iostream>
#include <cmath>
#include<windows.h>
		#include <GL/glu.h>
		#include <GL/glut.h>

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
    // Find the centroid of the triangle
    float centroidX = (vertices[0][0] + vertices[0][1] + vertices[0][2]) / 3;
    float centroidY = (vertices[1][0] + vertices[1][1] + vertices[1][2]) / 3;

    // Translate the triangle to the origin
    float translation1[3][3] = {
        {1, 0, -centroidX},
        {0, 1, -centroidY},
        {0, 0, 1}
    };
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.0, 1.0); // Blue color for original triangle
    for (int i = 0; i < 3; i++) {
        glVertex2f(vertices[0][i], vertices[1][i]);
    }
    glEnd();



    float ang1 = 45 * 3.14159 / 180;

    float rotation[3][3]={
        {cos(ang1), sin(ang1), 0},
        {-sin(ang1), cos(ang1), 0},
        {0,0,1}
    };

    float translation2[3][3]={
        {1, 0, centroidX},
        {0, 1, centroidY},
        {0, 0, 1}
    };

    float trans1[3][3];
    float rot[3][3];
    float trans2[3][3];

    multiplyMatrices(translation1, vertices, trans1);
    multiplyMatrices(rotation, trans1, rot);
    multiplyMatrices(translation2, rot, trans2);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 0.0, 0.0); // Red color for transformed triangle
    for(int i=0;i<3;i++){
        glVertex2f(trans2[0][i], trans2[1][i]);
    }
    glEnd();
    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Transformation");
    glClearColor(1.0, 1.0, 1.0, 0.0); // White background
    gluOrtho2D(-1, 1, -1, 1); // Coordinate system setup
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
