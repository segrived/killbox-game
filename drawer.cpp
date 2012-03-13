#include <GL/glfw.h>
#include "drawer.h"

void Drawer::drawPoint(float x, float y) {
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void Drawer::drawBox(float x, float y, float size) {
    float halfOfSize = size / 2;
    glBegin(GL_QUADS);
        glVertex2f(x - halfOfSize, y - halfOfSize);
        glVertex2f(x - halfOfSize, y + halfOfSize);
        glVertex2f(x + halfOfSize, y + halfOfSize);
        glVertex2f(x + halfOfSize, y - halfOfSize);
    glEnd();
}