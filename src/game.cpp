#include <iostream>
#include <math.h>
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

void Game::parseOptions(int argc, char ** argv, const char * data) {
    int result = 0;
    while((result = getopt(argc, argv, data)) != -1) {
        switch (result) {
            case 'f':
                game.isFullscreen = true; break;
            case 'w':
                game.isFullscreen = false; break;
            default:
                std::cout << "Error. Incorect parameter" << std::endl;
        }
    }
}

void onKeyPress(int key, int action) { game.onKeyPress(key, action); }

void enableCallbackBinds() {
    glfwSetKeyCallback(&onKeyPress);
}

Game::Game() {
    running = true;
    machinePosition = 0.0f;
    lastTimeStamp = glfwGetTime();
    opponentSpeed = Options::Frag::startSpeed;
    lifes = Options::Player::lifes;
    score = 0;
    isFullscreen = DEFAULT_FULLSCREEN;
    ticksFromStart = 0;
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
    int mode = (isFullscreen) ? GLFW_FULLSCREEN : GLFW_WINDOW;
    glfwOpenWindow(width, height, 5, 6, 5, 0, 0, 0, mode);
    glfwSetWindowTitle(title);
    glfwSwapInterval(1);
    
    enableCallbackBinds();
   
    while(running) startMainLoop();
}

void Game::timerTick(int ticksFromStart) {
    if(ticksFromStart % Options::Frag::generatingSpeed == 0) {
        createNewOpponent();
    }
    if(rand() % Options::Bonus::chance == 0) {
        createNewBonus();
    }
}

void Game::startMainLoop() {
	double glfwTime = glfwGetTime();
    if(glfwTime - lastTimeStamp >= 0.1f) {
        timerTick(ticksFromStart++);
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
    o.coord = Coord<float>((rand() % 100 - 50) / (float)50, 1.0f);
    if(rand() % Options::Frag::Boss::chance == 0) {
		o.lifes = Options::Frag::Boss::lifes;
		o.type = FRAG_TYPE_BOSS;
        o.size = Options::Frag::size * Options::Frag::Boss::sizeMultipler;
	} else {
		o.lifes = 1;
		o.type = FRAG_TYPE_NORMAL;
        o.size = Options::Frag::size;
	}
    float cr = ((rand() % 80) / 100.0f) + 0.2f;
    float cg = ((rand() % 80) / 100.0f) + 0.2f;
    float cb = ((rand() % 80) / 100.0f) + 0.2f;
    o.color = {cr, cg, cb};
    o.startShift = (rand() % 100) / 10.0f;
    opponents.push_back(o);
}

void Game::createNewBonus() {
    Bonus b;
    float xCoord = (rand() % 100) / 100.f;
    b.coord = Coord<float>(xCoord, 1.0f);
    b.type = rand() % 3;
    bonuses.push_back(b);
}

void Game::onKeyPress(int key, int action) {
    if ((key == GLFW_KEY_UP || key == ' ' || key == 'W') && action == GLFW_PRESS) {
		if(bullets.size() >= Options::Bullet::maxPerScreen) return;
        Bullet b;
        b.coord = Coord<float>(machinePosition, -0.95f);
        bullets.push_back(b);
        playSound("sounds/shot.wav");
    }
}

Coord<int> Game::getWindowSize() {
    Coord<int> ic;
    glfwGetWindowSize(&ic.x, &ic.y);
    return ic;
}

void Game::drawScene() {
    glLoadIdentity();
    std::vector<Bullet>::iterator bi;
    
    if(SHOW_AVAILABLE_BULLETS) {
        Drawer::setColor(0.2f, 0.7f, 0.9f);
        showAvailableBullets();
    }
    
    if(SHOW_AVAILABLE_LIFES) {
        Drawer::setColor(1.0f, 0.0f, 0.0f);
        drawAvailableLifes();
    }
    
    for(bi = bullets.begin(); bi < bullets.end(); bi++) {
		std::vector<Opponent>::iterator oi;
		float bx = (*bi).coord.x;
		float by = (*bi).coord.y;
		for(oi = opponents.begin(); oi < opponents.end(); oi++) {
			float ox = (*oi).coord.x;
			float oy = (*oi).coord.y;
			float hs = (*oi).size / 2;
            // Пуля попала в врага
			if((bx > ox - hs) && (bx < ox + hs) && (by > oy - hs) && (by < oy + hs)) {
				if(--(*oi).lifes == 0) {
					score += ((*oi).type == FRAG_TYPE_BOSS) ? Options::Frag::Boss::pointsPerKill : 0;
					opponents.erase(oi);
				}
                score += Options::Frag::pointsPerHit;
                playSound("sounds/kill.wav");
				bullets.erase(bi);
				continue;
            }
		}
	}
    
    std::vector<Bonus>::iterator bonusIter;
    float halfOfBonus = Options::Bonus::size / 2.f;
    float halfOfMachine = Options::Machine::size / 2.f;
    for(bonusIter = bonuses.begin(); bonusIter < bonuses.end(); bonusIter++) {
        if((*bonusIter).coord.x - halfOfBonus <= machinePosition + halfOfMachine
        && (*bonusIter).coord.x + halfOfBonus >= machinePosition - halfOfMachine
        && (*bonusIter).coord.y -halfOfBonus <= -0.95f) {
            switch((*bonusIter).type) {
                case BONUS_LIFE:
                    lifes++; break;
                case BONUS_POINTS:
                    score += 1000; break;
                default: break;
            }
            bonuses.erase(bonusIter);
        }
    }
    drawAllBullets();
    drawAllOpponents();
    drawAllBonuses();
    Drawer::drawMachine(Options::Machine::size, machinePosition);
}

void Game::showAvailableBullets() {
    for(int i = 0; i < Options::Bullet::maxPerScreen - bullets.size(); i++) {
        Drawer::drawBox((1 - i / 20.0f) - 0.05f, 0.95f, 0.03f);
    }
}

void Game::drawAvailableLifes() {
    for(int i = 0; i < lifes; i++) {
        Drawer::drawHeart((i / 20.0f) - 0.95f, 0.95f, 0.02f);
    }
}

void Game::checkPressedKeys() {
    // Нажата левая стрелка
    if ((glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS) || (glfwGetKey('A') == GLFW_PRESS)) {
        if ((machinePosition - Options::Machine::size / 2) >= -1.0f) {
            machinePosition -= Options::Machine::speed;
        }
    }
    
    // Нажата правая стрелка
    if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey('D') == GLFW_PRESS) {
        if ((machinePosition + Options::Machine::size / 2) <= 1.0f) {
            machinePosition += Options::Machine::speed;
        }
    }
}

void Game::drawAllOpponents() {
    opponentSpeed *= Options::Frag::acceleration;
    std::vector<Opponent>::iterator oi;
    for (oi = opponents.begin(); oi < opponents.end(); ++oi) {
        (*oi).coord.x = sin((*oi).coord.y + (*oi).startShift);
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

void Game::drawAllBonuses() {
	std::vector<Bonus>::iterator bi;
	for(bi = bonuses.begin(); bi < bonuses.end(); ++bi) {
		Drawer::drawBonus((*bi).coord, Options::Bonus::size, (*bi).type);
        (*bi).coord.y -= 0.01f;
        if((*bi).coord.y <= -1.0f) {
            bonuses.erase(bi);
        }
	}
}

// Функция рисует все запущенные патроны и перемещает их вверх
void Game::drawAllBullets() {
    std::vector<Bullet>::iterator bi;
    for (bi = bullets.begin(); bi < bullets.end(); ++bi) {
        // Перемещаем патрон вверх
        if (((*bi).coord.y += Options::Bullet::speed) > 1.0f) {
            bullets.erase(bi);
            continue;
        }
        // Рисуем пулю
        Drawer::drawBullet((*bi).coord, Options::Bullet::size);
    }
}

void Game::drawOpponent(Opponent o) {
    Drawer::setColor(o.color);
    Drawer::drawBox(o.coord.x, o.coord.y, o.size);
}


int main(int argc, char ** argv) {
    // Включаем рандомизатор
    srand(time(NULL));
    game.parseOptions(argc, argv, "fw");
    game.initAudioSystem();
    int height, width;
    height = WINDOW_MODE_HEIGHT;
    width = WINDOW_MODE_WIDTH;
    game.initGraphicSystem(height, width, "Killbox Game");
}