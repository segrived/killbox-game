#include <vector>

#define __ENABLE_MOUSE false

#define OPP_SIZE 0.2f
#define OPP_STARTING_SPEED 0.01f
#define OPP_ACCELERATION 1.0002f
#define OPP_GEN_PAUSE 2.0f
#define OPP_BOSS_LIFES 3
#define OPP_BOSS_FREQ 10
#define OPP_BOSS_DIVIDE_DELTA 2.0f       
#define OPP_POINTS_PER_BOSS 1000
#define BULLET_SPEED 0.01f
#define MACHINE_SIZE 0.2f
#define MACHINE_SPEED 0.02f
#define MAX_BULLETS_PER_SCREEN 7
#define GAME_LIFES 3
#define POINTS_PER_GOOD 100

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


