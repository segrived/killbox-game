#include <vector>

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
    float size;
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


