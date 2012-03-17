CC=g++

killboxgame: src/game.cpp
	mkdir -p bin
	mkdir -p bin/sounds
	cp -r media/sounds/* bin/sounds
	$(CC) -std=c++0x -lGL -lglfw -lfmodex src/game.cpp src/drawer.cpp  -o bin/game
