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
    NORMAL, BOSS
} opponentType;

struct Opponent {
    Coord<float, 3> coord;
    int lifes;
    float size;
    opponentType type;
    Color color;
};

#endif
