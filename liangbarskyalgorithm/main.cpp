#include <iostream>
#include <cmath>
#include <algorithm>
#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
using namespace std;

void liangBarskyClip(int wxMin, int wyMin, int wxMax, int wyMax, int lx1, int ly1, int lx2, int ly2);

void display() {
    int wxMin = 200, wyMin = 300, wxMax = 700, wyMax = 750;

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1, 1, 1);

    // Draw the clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2f(wxMin, wyMin);
    glVertex2f(wxMax, wyMin);
    glVertex2f(wxMax, wyMax);
    glVertex2f(wxMin, wyMax);
    glEnd();

    // Lines to be clipped
    int line1StartX = 100, line1StartY = 400, line1EndX = 800, line1EndY = 600;
    int line2StartX = 250, line2StartY = 100, line2EndX = 600, line2EndY = 900;

    liangBarskyClip(wxMin, wyMin, wxMax, wyMax, line1StartX, line1StartY, line1EndX, line1EndY);
    liangBarskyClip(wxMin, wyMin, wxMax, wyMax, line2StartX, line2StartY, line2EndX, line2EndY);

    glutSwapBuffers();
}

void liangBarskyClip(int wxMin, int wyMin, int wxMax, int wyMax, int lx1, int ly1, int lx2, int ly2) {
    float deltaX = lx2 - lx1;
    float deltaY = ly2 - ly1;

    float u1 = 0.0, u2 = 1.0;
    float p[4], q[4];

    p[0] = -deltaX; q[0] = lx1 - wxMin;
    p[1] = deltaX;  q[1] = wxMax - lx1;
    p[2] = -deltaY; q[2] = ly1 - wyMin;
    p[3] = deltaY;  q[3] = wyMax - ly1;

    bool shouldClip = true;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0) {
            shouldClip = false;
            break;
        }
        if (p[i] != 0) {
            float r = q[i] / p[i];
            if (p[i] < 0) {
                u1 = max(u1, r);
            } else {
                u2 = min(u2, r);
            }
        }
    }

    if (u1 > u2 || !shouldClip) {
        glColor3f(1, 0, 0);
        glBegin(GL_LINES);
        glVertex2f(lx1, ly1);
        glVertex2f(lx2, ly2);
        glEnd();
    } else {
        float newX1 = lx1 + u1 * deltaX;
        float newY1 = ly1 + u1 * deltaY;
        float newX2 = lx1 + u2 * deltaX;
        float newY2 = ly1 + u2 * deltaY;

        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(newX1, newY1);
        glVertex2f(newX2, newY2);
        glEnd();

        glColor3f(1, 0, 0);
        if (u1 > 0) {
            glBegin(GL_LINES);
            glVertex2f(lx1, ly1);
            glVertex2f(newX1, newY1);
            glEnd();
        }
        if (u2 < 1) {
            glBegin(GL_LINES);
            glVertex2f(newX2, newY2);
            glVertex2f(lx2, ly2);
            glEnd();
        }
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 1000, 0, 1000);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Liang-Barsky Line Clipping Algorithm");

    init();

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
