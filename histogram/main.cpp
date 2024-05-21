#include <cmath>
#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

int frequencies[] = {50, 60, 10, 20, 50};

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

    // Calculate the width of each bar
    float barWidth = 500.0f / sizeof(frequencies);

    // Loop through each frequency and draw the outline of the histogram bar
    for (int i = 0; i < sizeof(frequencies) / sizeof(frequencies[0]); ++i) {
        // Calculate the height of the bar based on frequency
        float barHeight = frequencies[i] * 10.0f;

        // Calculate the position of the current bar
        float x1 = i * barWidth;
        float y1 = 0.0f;
        float x2 = x1 + barWidth;
        float y2 = barHeight;

        // Draw the outline of the histogram bar using DDA algorithm
        draw_line(x1, y1, x1, y2);  // Left vertical line
        draw_line(x1, y2, x2, y2);  // Top horizontal line
        draw_line(x2, y2, x2, y1);  // Right vertical line
        draw_line(x2, y1, x1, y1);  // Bottom horizontal line
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
    glutInitWindowSize(500, 800);
    glutCreateWindow("Histogram");
    glutDisplayFunc(draw_histogram);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
