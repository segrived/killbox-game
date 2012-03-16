#include "types.h"

#ifndef DRAWER_H_GUARD
#define DRAWER_H_GUARD

class Drawer {
    public:
        static void drawPoint(float x, float y);
        static void drawBox(float x, float y, float size);
        static void drawHeart(float x, float y, float size);
        static void drawCircle(float cx, float cy, float r, int segments, bool filled);
        
        static void setColor(float r, float g, float b);
        static void setColor(float r, float g, float b, float a);
        static void setColor(Color c);
};

#endif