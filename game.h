#include <vector>

#define __ENABLE_MOUSE false

// Разсер врага
#define OPP_SIZE 0.2f
// Стартовая скорость врагов
#define OPP_STARTING_SPEED 0.01f
// Ускорение врагов
#define OPP_ACCELERATION 1.0002f
// Промежуток между генерацией врагов
#define OPP_GEN_PAUSE 2.0f
// Количество жизней у босса
#define OPP_BOSS_LIFES 3
// Вероятность генерации босса (1 / значение)
#define OPP_BOSS_CHANCE 10
// Размер босса относительно обычных врагов. Чем значение
// больше — тем босс меньше. При значении 1.0f размер босса равен
// размеру обычного врага
#define OPP_BOSS_DIVIDE_DELTA 2.0f       
// Количество очков, дающихся дополнительно за убийства босса
#define OPP_POINTS_PER_BOSS 1000
// Скорость путь
#define BULLET_SPEED 0.01f
// Размер машины
#define MACHINE_SIZE 0.2f
// Скорость перемещения машины
#define MACHINE_SPEED 0.02f
// Максимальное количество пуль на одном экане
#define MAX_BULLETS_PER_SCREEN 7
// Количество жизней у игрока
#define GAME_LIFES 3
// Количество очков за попадание
#define POINTS_PER_HIT 100

struct color {
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

enum opponentType { NORMAL, BOSS };

struct Opponent {
    Coord coord;
    int lifes;
    opponentType type;
    color opColor;
};

void shutdown(int returnCode);
void onKeyPress(int key, int action);
void onMouseMove(int x, int y);
void enableCallbackBinds();

/** KILLBOXGAME CLASS **/
class Game {
    private:
        FMOD::System *audioSys;
        float machinePosition;
        float opponentSpeed;
        bool running;
        double lastTimeStamp;
        int lifes;
        int score;
        
        std::vector<Bullet> bullets;
        std::vector<Opponent> opponents;
    public:
        Game();
        pCoord getWindowSize();
        Coord convertCoords(int x, int y);

        void onKeyPress(int key, int action);
        void onMouseMove(int x, int y);
        
        void initAudioSystem();
        void initGraphicSystem(int width, int height, const char* title);
        
        void startMainLoop();
        void checkPressedKeys();
        void playSound(const char* fileName);
   
        void createNewOpponent();
   
        void drawScene();
        void drawKillMachine();
        void drawAllBullets();
        void drawAllOpponents();
        void drawBullet(Bullet b);
        void drawOpponent(Opponent opData);
};


