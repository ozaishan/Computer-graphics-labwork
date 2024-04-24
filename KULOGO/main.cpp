#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
int screen_width, screen_height;
void drawRectangle() {
    glColor3f(0.0, 0.0, 0.5);// dark blue color
    glBegin(GL_POLYGON);
    glVertex2f(-0.75, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.75, 0.5);
    glEnd();
}void drawK(float x, float y, float radius) {
    glColor3f(0.0, 0.0, 0.0);
    // Draw the vertical line of the letter K
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glVertex2f(x - radius / 4 + 0.03, y + radius / 4);
    glVertex2f(x - radius / 4 + 0.03, y - radius / 4);
    glEnd();

    // Draw the first diagonal line of the letter K
    glBegin(GL_LINES);
    glVertex2f(x - radius / 4 + 0.03, y);
    glVertex2f(x + 0.03, y + radius / 4);
    glEnd();

    // Draw the second diagonal line of the letter K
    glBegin(GL_LINES);
    glVertex2f(x - radius / 4 + 0.03, y);
    glVertex2f(x + 0.03, y - radius / 4);
    glEnd();

    // Draw the third diagonal line parallel to the first diagonal line with thicker width
    glBegin(GL_LINES);
    glVertex2f(x + 0.03, y - radius / 4);
    glVertex2f(x + radius / 4 + 0.03, y);
    glEnd();
}

void drawCircle(float x, float y, float radius, float red, float green, float blue) {
    int num = 100;
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < num; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num);
        float dx = radius * cosf(theta);
        float dy = radius * sinf(theta);
        glVertex2f(x + dx, y + dy);
    }
    glEnd();
}
void drawTriangle(float x, float y, float radius) {
    glColor3f(1.0, 1.0, 1.0);
     glLineWidth(4.0);
glBegin(GL_LINE_LOOP);

    glVertex2f(x - radius, y - 0.15 );
    glVertex2f(x + radius, y - 0.15);
    glVertex2f(x, y + 2 * radius - 0.15);
    glEnd();
}
void drawrevTriangle(float x, float y, float radius) {
    glColor3f(0.9921, 0.6823, 0.6745);
glBegin(GL_POLYGON);
    glVertex2f(x - radius, y - 0.15 );
    glVertex2f(x + radius, y - 0.15);
    glVertex2f(x, y + 2 * radius - 0.15);
    glEnd();
}
void drawOutline(float x, float y, float radius) {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(1.5);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x - radius, y - 0.15 );
    glVertex2f(x + radius, y - 0.15);
    glVertex2f(x, y + 2 * radius - 0.15);
    glEnd();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawRectangle();
    drawCircle(0.0, 0.0, 0.3, 1.0, 0.0, 0.0);
    drawCircle(0.0, 0.0, 0.23, 0.6627, 0.7764, 0.8941);
    drawCircle(0.0, 0.0, 0.182, 0.9568, 0.9137, 0.4431);
    drawrevTriangle(0.0, 0.260, -0.182);
    drawTriangle(0.0, 0.0, 0.182);
    drawOutline(0.0, 0.260, -0.182);
    drawK(0.0, 0.0, 0.182);
    glFlush();
}
void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set background color to white
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the viewing area
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);  // Set window size
    glutInitWindowPosition(100, 100); // Set window position
    glutCreateWindow("KU ");  // Set window title
     // Get monitor resolution
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);
    std::cout << "Monitor resolution: " << screen_width << "x" << screen_height << std::endl;
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
