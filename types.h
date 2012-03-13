#ifndef TYPES_H_GUARD
#define TYPES_H_GUARD

struct Color {
    float r;
    float g;
    float b;
};

typedef struct fCoord {
    float x;
    float y;
} Coord;

struct iCoord {
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
    Color color;
};

#endif