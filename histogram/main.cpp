
#include <cmath>
#include<windows.h>
		#include <GL/glu.h>
		#include <GL/glut.h>

int frequencies[] = { 10, 20, 30, 40,50};

// Function to draw a line using DDA algorithm
void draw_line(float x1, float y1, float x2, float y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
    float x_increment = dx / steps;
    float y_increment = dy / steps;
    float x = x1;
    float y = y1;

    glBegin(GL_POINTS);
    glLineWidth(10.0f);
    for (int i = 0; i < int(steps); ++i) {
        glVertex2f(x, y);
        x += x_increment;
        y += y_increment;
    }
    glEnd();
}

// Function to draw histogram
void draw_histogram() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
glLineWidth(5.0f);
    for (int i = 0; i < 5; ++i) {
        draw_line(i * 20, 0, i * 20, frequencies[i] * 10);
    }

    glFlush();
}

// Function to handle window resizing
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 700);
    glutCreateWindow("Histogram");
    glutDisplayFunc(draw_histogram);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
