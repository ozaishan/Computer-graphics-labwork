
#include <iostream>
#include<windows.h>
		#include <GL/glu.h>
		#include <GL/glut.h>
// Define the clipping window
const int clipXMin = 50, clipYMin = 50, clipXMax = 200, clipYMax = 200;

// Vertex structure
struct Point {
    int x, y;
};


const int MAX_VERTICES = 10;
Point shape[MAX_VERTICES] = {{150, 150}, {200, 250}, {270, 210}, {250, 100}, {150, 30}};
int shapeVertexCount = 5; // Number of vertices in the shape

// Function to compute the intersection point
Point calculateIntersection(Point s, Point p, int clipEdge) {
    Point i;
    float slope;

    if (clipEdge == 1) { // Left
        slope = (float)(p.y - s.y) / (p.x - s.x);
        i.x = clipXMin;
        i.y = s.y + slope * (clipXMin - s.x);
    } else if (clipEdge == 2) { // Right
        slope = (float)(p.y - s.y) / (p.x - s.x);
        i.x = clipXMax;
        i.y = s.y + slope * (clipXMax - s.x);
    } else if (clipEdge == 3) { // Bottom
        slope = (float)(p.x - s.x) / (p.y - s.y);
        i.y = clipYMin;
        i.x = s.x + slope * (clipYMin - s.y);
    } else if (clipEdge == 4) { // Top
        slope = (float)(p.x - s.x) / (p.y - s.y);
        i.y = clipYMax;
        i.x = s.x + slope * (clipYMax - s.y);
    }

    return i;
}

// Sutherland-Hodgeman polygon clipping algorithm
void sutherlandHodgemanClip(Point inputShape[], int& vertexCount, int clipEdge) {
    Point outputShape[MAX_VERTICES];
    int outputVertexCount = 0;
    Point s = inputShape[vertexCount - 1];

    for (int i = 0; i < vertexCount; i++) {
        Point p = inputShape[i];
        bool pInside = (clipEdge == 1 && p.x >= clipXMin) || (clipEdge == 2 && p.x <= clipXMax) ||
                       (clipEdge == 3 && p.y >= clipYMin) || (clipEdge == 4 && p.y <= clipYMax);
        bool sInside = (clipEdge == 1 && s.x >= clipXMin) || (clipEdge == 2 && s.x <= clipXMax) ||
                       (clipEdge == 3 && s.y >= clipYMin) || (clipEdge == 4 && s.y <= clipYMax);

        if (pInside) {
            if (!sInside) {
                outputShape[outputVertexCount++] = calculateIntersection(s, p, clipEdge);
            }
            outputShape[outputVertexCount++] = p;
        } else if (sInside) {
            outputShape[outputVertexCount++] = calculateIntersection(s, p, clipEdge);
        }

        s = p;
    }

    // Copy outputShape to inputShape
    vertexCount = outputVertexCount;
    for (int i = 0; i < vertexCount; i++) {
        inputShape[i] = outputShape[i];
    }
}

// Function to clip the polygon against all edges of the clipping window
void clipShape(Point inputShape[], int& vertexCount) {
    sutherlandHodgemanClip(inputShape, vertexCount, 1); // Clip against left edge
    sutherlandHodgemanClip(inputShape, vertexCount, 2); // Clip against right edge
    sutherlandHodgemanClip(inputShape, vertexCount, 3); // Clip against bottom edge
    sutherlandHodgemanClip(inputShape, vertexCount, 4); // Clip against top edge
}

// Function to check if a point is inside the clipping window
bool isInside(Point v) {
    return v.x >= clipXMin && v.x <= clipXMax && v.y >= clipYMin && v.y <= clipYMax;
}

// Display function to draw the clipping window and polygons
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the clipping window
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(clipXMin, clipYMin);
    glVertex2i(clipXMax, clipYMin);
    glVertex2i(clipXMax, clipYMax);
    glVertex2i(clipXMin, clipYMax);
    glEnd();

    // Draw the original polygon with color based on inside or outside clipping window
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < shapeVertexCount; i++) {
        Point v = shape[i];
        if (isInside(v))
            glColor3f(0.0, 1.0, 0.0); // Green for inside
        else
            glColor3f(1.0, 0.0, 0.0); // Red for outside
        glVertex2i(v.x, v.y);
    }
    glEnd();

    // Clip the polygon and draw the clipped polygon in green
    Point clippedShape[MAX_VERTICES];
    int clippedVertexCount = shapeVertexCount;
    for (int i = 0; i < shapeVertexCount; i++) {
        clippedShape[i] = shape[i];
    }
    clipShape(clippedShape, clippedVertexCount);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < clippedVertexCount; i++) {
        glVertex2i(clippedShape[i].x, clippedShape[i].y);
    }
    glEnd();

    glFlush();
}

// Initialize OpenGL
void initializeGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Sutherland-Hodgeman Polygon Clipping Algorithm");
    initializeGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
