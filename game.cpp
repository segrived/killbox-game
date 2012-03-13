#include <iostream>
#include <GL/glfw.h>
#include <fmodex/fmod.hpp>
#include "types.h"
#include "options.h"
#include "game.h"
#include "drawer.h"

// Первый и единственный экземпляр класса Game (глобальный)
Game game;

void shutdown(int returnCode) {
    glfwTerminate();
    exit(returnCode);
}

void onKeyPress(int key, int action) { game.onKeyPress(key, action); }
void onMouseMove(int x, int y) { game.onMouseMove(x, y); }

void enableCallbackBinds() {
    glfwSetKeyCallback(&onKeyPress);
    if(__ENABLE_MOUSE) {
        glfwSetMousePosCallback(&onMouseMove);
    }
}

Game::Game() {
    running = true;
    machinePosition = 0.0f;
    lastTimeStamp = glfwGetTime();
    opponentSpeed = OPP_STARTING_SPEED;
    lifes = GAME_LIFES;
    score = 0;
}

void Game::initAudioSystem() {
    FMOD::System_Create(&audioSys);
}

void Game::playSound(const char* fileName) {
    FMOD::Sound* sound;
    audioSys->setOutput(FMOD_OUTPUTTYPE_DSOUND);
    audioSys->init(32, FMOD_INIT_NORMAL, 0);
    audioSys->createSound(fileName, FMOD_DEFAULT, 0, &sound);
    FMOD::Channel* channel;
    audioSys->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
    audioSys->update();
}

void Game::initGraphicSystem(int width, int height, const char* title) {
    if (glfwInit() != GL_TRUE)
        shutdown(1);
    if (glfwOpenWindow(width, height, 5, 6, 5, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
        shutdown(1);
    glfwSetWindowTitle(title);
    glfwSwapInterval(1);
    
    enableCallbackBinds();
    
    while(running) startMainLoop();
}

void Game::startMainLoop() {
    double glfwTime = glfwGetTime();
    if(glfwTime - lastTimeStamp >= OPP_GEN_PAUSE) {
        createNewOpponent();
        lastTimeStamp = glfwTime;
    }
    checkPressedKeys();
    drawScene();
    glfwSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
}

void Game::createNewOpponent() {
    Opponent o;
    o.coord.x = (rand() % 100 - 50) / (float)50;
    o.coord.y = 1.0f;
    if(rand() % OPP_BOSS_CHANCE == 0) {
		o.lifes = OPP_BOSS_LIFES;
		o.type = BOSS;
        o.size = OPP_SIZE * OPP_BOSS_SIZE_MULTIPLER;
	} else {
		o.lifes = 1;
		o.type = NORMAL;
        o.size = OPP_SIZE;
	}
    float cr = (rand() % 100) / 100.0f;
    float cg = (rand() % 100) / 100.0f;
    float cb = (rand() % 100) / 100.0f;
    o.opColor = {cr, cg, cb};
    opponents.push_back(o);
}

void Game::onKeyPress(int key, int action) {
    if ((key == GLFW_KEY_UP || key == ' ' || key == 'W') && action == GLFW_PRESS) {
		if(bullets.size() >= MAX_BULLETS_PER_SCREEN) {
			return;
		}
        Bullet b;
        b.coord.x = machinePosition;
        b.coord.y = -0.95f;
        bullets.push_back(b);
        playSound("sounds/shot.wav");
    }
}

void Game::onMouseMove(int x, int y) {
    Coord c = convertCoords(x, y);
    machinePosition = c.x;
}

Coord Game::convertCoords(int x, int y) {
    pCoord winSize = getWindowSize();
    Coord newCoords;
    newCoords.x = (x - (float)winSize.x / 2) / ((float)winSize.x / 2);
    newCoords.y = -(y - (float)winSize.y / 2) / ((float)winSize.y / 2);
    return newCoords;
}

pCoord Game::getWindowSize() {
    pCoord pc;
    glfwGetWindowSize(&pc.x, &pc.y);
    return pc;
}

void Game::drawScene() {
    glLoadIdentity();
    std::vector<Bullet>::iterator bi;
    for(bi = bullets.begin(); bi < bullets.end(); bi++) {
		std::vector<Opponent>::iterator oi;
		float bx = (*bi).coord.x;
		float by = (*bi).coord.y;
		for(oi = opponents.begin(); oi < opponents.end(); oi++) {
			float ox = (*oi).coord.x;
			float oy = (*oi).coord.y;
			float hs = (*oi).size / 2;
            // Пуля попала во врага
			if((bx > ox - hs) && (bx < ox + hs) && (by > oy - hs) && (by < oy + hs)) {
				if(--(*oi).lifes == 0) {
					score += ((*oi).type == BOSS) ? OPP_POINTS_PER_BOSS : 0;
					opponents.erase(oi);
				}
                score += POINTS_PER_HIT;
				bullets.erase(bi);
				continue;
            }
		}
	}
    drawAllBullets();
    drawAllOpponents();
    drawKillMachine();
}

void Game::checkPressedKeys() {
    float hom = MACHINE_SIZE / 2;
    
    // Нажата левая стрелка
    if ((glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) || (glfwGetKey('A') == GLFW_PRESS)) {
        if ((machinePosition - hom) >= -1.0f) {
            machinePosition -= MACHINE_SPEED;
        }
    }
    
    // Нажата правая стрелка
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey('D') == GLFW_PRESS) {
        if ((machinePosition + hom) <= 1.0f) {
            machinePosition += MACHINE_SPEED;
        }
    }
}

void Game::drawAllOpponents() {
    opponentSpeed *= OPP_ACCELERATION;
    std::vector<Opponent>::iterator oi;
    for (oi = opponents.begin(); oi < opponents.end(); ++oi) {
        drawOpponent(*oi);
        if(((*oi).coord.y -= opponentSpeed) < -1.0f) {
			if(--lifes == 0) {
				std::cout << "Game over. Your Result: "
                          << score << std::endl;
				exit(0);
			}
            opponents.erase(oi);
        }
    }
}

void Game::drawKillMachine() {
    float h = MACHINE_SIZE / 2;
    glBegin(GL_POLYGON);
        glColor3f(0.2f, 0.2f, 0.2f);
        glVertex2f(machinePosition - h, -1.0f);
        glColor3f(0.4f, 0.4f, 0.4f);
        glVertex2f(machinePosition + h, -1.0f);
        glColor3f(0.6f, 0.6f, 0.6f);
        glVertex2f(machinePosition + h, -0.95f);
        glColor3f(0.8f, 0.8f, 0.8f);
        glVertex2f(machinePosition - h, -0.95f);
    glEnd();
}

// Функция рисует все запущенные патроны и перемещает их вверх
void Game::drawAllBullets() {
    std::vector<Bullet>::iterator bi;
    for (bi = bullets.begin(); bi < bullets.end(); ++bi) {
        // Перемещаем патрон вверх
        if (((*bi).coord.y += BULLET_SPEED) > 1.0f) {
            bullets.erase(bi);
            continue;
        }
        // Рисуем пулю
        drawBullet(*bi);
    }
}

void Game::drawBullet(Bullet b) {
    Drawer::drawPoint(b.coord.x, b.coord.y);
}

void Game::drawOpponent(Opponent o) {
    glColor3f(o.opColor.r, o.opColor.g, o.opColor.b);
    Drawer::drawBox(o.coord.x, o.coord.y, o.size);
}



int main(int argc, char ** argv) {
    game.initAudioSystem();
    game.initGraphicSystem(500, 500, "Killbox Game");
}
