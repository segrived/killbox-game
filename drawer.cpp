#include <GL/glfw.h>
#include <cmath>
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

void Drawer::drawHeart(float x, float y, float size) {
    setColor(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(x, y - size);
        glVertex2f(x - size, y);
        glVertex2f(x - size, y + size);
        glVertex2f(x, y + size / 2.0f);
        glVertex2f(x + size, y + size);
        glVertex2f(x + size, y);
        glVertex2f(x, y - size);
    glEnd();
}

void Drawer::drawCircle(float cx, float cy, float r, int segments, bool filled) {
    if(filled) {
        glBegin(GL_POLYGON); 
    } else {
        glBegin(GL_LINE_STRIP); 
    }
    for(int i = 0; i < segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    } 
    glEnd(); 
}

void Drawer::setColor(float r, float g, float b) {
    glColor3f(r, g, b);
}

void Drawer::setColor(float r, float g, float b, float a) {
    glColor4f(r, g, b, a);
}

void Drawer::setColor(Color c) {
    glColor3f(c.r, c.g, c.b);
}