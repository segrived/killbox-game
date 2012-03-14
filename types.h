#ifndef TYPES_H_GUARD
#define TYPES_H_GUARD

template < typename type, int count >
class Coord {
	public:
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
    Coord<float, 3> coord;
};

typedef enum {
    FRAG_TYPE_NORMAL, FRAG_TYPE_BOSS
} FragType;

typedef enum {
    BONUS_LIFES, BONUS_POINTS
} BonusType;

typedef enum {
    MODE_WINDOW, MODE_FULLSCREEN
} AppMode;

struct Opponent {
    Coord<float, 3> coord;
    int lifes;
    float size;
    float startShift;
    FragType type;
    Color color;
};

struct Bonus {
    Coord<float, 2> coord;
    BonusType type;
};

#endif
