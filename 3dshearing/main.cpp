#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include <windows.h>

// Function to initialize rendering
void initRendering() {
    glEnable(GL_DEPTH_TEST);
}

// Function to handle window resize
void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Function to draw the coordinate axes
void drawAxes() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    // X-axis
    glVertex3f(-5.0f, 0.0f, 0.0f);
    glVertex3f(5.0f, 0.0f, 0.0f);
    // Y-axis
    glVertex3f(0.0f, -5.0f, 0.0f);
    glVertex3f(0.0f, 5.0f, 0.0f);
    // Z-axis
    glVertex3f(0.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 0.0f, 5.0f);
    glEnd();
}

// Function to draw the outline of a cube
void drawCubeOutline(float r, float g, float b) {
    glBegin(GL_LINES);
    glColor3f(r, g, b);
    // Bottom face
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // Top face
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // Connecting lines
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glEnd();
}

// Function to apply a transformation to the vertices
void applyTransformation(float vertices[][4], int vertexCount, float matrix[4][4]) {
    for (int i = 0; i < vertexCount; ++i) {
        float x = vertices[i][0];
        float y = vertices[i][1];
        float z = vertices[i][2];
        float w = vertices[i][3];
        vertices[i][0] = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3] * w;
        vertices[i][1] = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3] * w;
        vertices[i][2] = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3] * w;
        vertices[i][3] = matrix[3][0] * x + matrix[3][1] * y + matrix[3][2] * z + matrix[3][3] * w;
    }
}

// Function to draw the sheared cube outline along the Z-axis
void drawShearedCubeOutline(float r, float g, float b, float shearFactorZ) {
    float vertices[8][4] = {
        {-0.5f, -0.5f, -0.5f, 1.0f},
        {0.5f, -0.5f, -0.5f, 1.0f},
        {0.5f, 0.5f, -0.5f, 1.0f},
        {-0.5f, 0.5f, -0.5f, 1.0f},
        {-0.5f, -0.5f, 0.5f, 1.0f},
        {0.5f, -0.5f, 0.5f, 1.0f},
        {0.5f, 0.5f, 0.5f, 1.0f},
        {-0.5f, 0.5f, 0.5f, 1.0f}
    };

    // Shear matrix (Z-axis shear)
    float shearMatrix[4][4] = {
        {1.0f, 0.0f, shearFactorZ, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    };

    // Apply shear transformation
    applyTransformation(vertices, 8, shearMatrix);

    glBegin(GL_LINES);
    glColor3f(r, g, b);
    for (int i = 0; i < 4; ++i) {
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        glVertex3f(vertices[(i + 1) % 4][0], vertices[(i + 1) % 4][1], vertices[(i + 1) % 4][2]);
        glVertex3f(vertices[i + 4][0], vertices[i + 4][1], vertices[i + 4][2]);
        glVertex3f(vertices[(i + 1) % 4 + 4][0], vertices[(i + 1) % 4 + 4][1], vertices[(i + 1) % 4 + 4][2]);
        glVertex3f(vertices[i][0], vertices[i][1], vertices[i][2]);
        glVertex3f(vertices[i + 4][0], vertices[i + 4][1], vertices[i + 4][2]);
    }
    glEnd();
}

// Function to draw the scene
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4.0, 3.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Changed viewpoint

    drawAxes();
    drawCubeOutline(0.0f, 0.0f, 1.0f); // Blue cube

    // Shearing factor value for Z-axis
    float shearFactorZ = 0.5f; // Shear factor along the Z-axis
    drawShearedCubeOutline(1.0f, 0.0f, 0.0f, shearFactorZ); // Red sheared cube

    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("3D Sheared Cube along Z-axis");
    initRendering();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(handleResize);
    glutMainLoop();
    return 0;
}
