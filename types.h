#ifndef TYPES_H_GUARD
#define TYPES_H_GUARD

struct Color {
    float r;
    float g;
    float b;
};

struct Coord {
    float x;
    float y;
};

struct pCoord {
    int x;
    int y;
};

struct Bullet {
    Coord coord;
};

typedef enum {
    NORMAL, BOSS
} opponentType;

struct Opponent {
    Coord coord;
    int lifes;
    float size;
    opponentType type;
    Color opColor;
};

#endif