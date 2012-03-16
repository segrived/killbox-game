#include <functional>

#ifndef TYPES_H_GUARD
#define TYPES_H_GUARD

#define BONUS_POINTS 0
#define BONUS_LIFE 1
#define BONUS_BULLETS 2

template <typename type>
class Coord {
	public:
        Coord() {};
        Coord(type _x, type _y): x(_x), y(_y) {};
        Coord(type _x, type _y, type _z): x(_x), y(_y), z(_z) {};
		type x;
        type y;
        type z;
};

struct Color {
    float r;
    float g;
    float b;
};

struct Bullet {
    Coord<float> coord;
};

typedef enum {
    FRAG_TYPE_NORMAL, FRAG_TYPE_BOSS
} FragType;

typedef enum {
    MODE_WINDOW, MODE_FULLSCREEN
} AppMode;

struct Opponent {
    Coord<float> coord;
    int lifes;
    float size;
    float startShift;
    FragType type;
    Color color;
};

struct Bonus {
    Coord<float> coord;
    int type;
    float speed;
};

#endif