#include <vector>
#include "types.h"

#ifndef GAME_H_GUARD
#define GAME_H_GUARD

void shutdown(int returnCode);
void onKeyPress(int key, int action);
void enableCallbackBinds();

/** KILLBOXGAME CLASS **/
class Game {
    private:
        FMOD::System *audioSys;
        float machinePosition;
        float opponentSpeed;
        bool isFullscreen;
        bool running;
        double lastTimeStamp;
        int lifes;
        int score;
        std::vector<Bullet> bullets;
        std::vector<Opponent> opponents;
        std::vector<Bonus> bonuses;
        std::vector<Timer> timers;
    public:
        Game();
        Coord<int> getWindowSize();
        void onKeyPress(int key, int action);
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
        void parseOptions(int argc, char ** argv, const char * data);
        void showAvailableBullets();
        void drawAvailableLifes();
        void drawBonus(Bonus b);
        void drawAllBonuses();
        void createNewBonus();
};

#endif
