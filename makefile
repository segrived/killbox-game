CC=g++

killboxgame: game.cpp
	mkdir -p bin
	mkdir -p bin/sounds
	cp -r _gamedata/sounds/* bin/sounds
	$(CC) -std=c++0x -lGL -lglfw -lfmodex game.cpp -o bin/game
