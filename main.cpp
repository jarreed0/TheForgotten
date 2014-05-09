//g++ *.cpp -lSDL -lSDL_ttf -lSDL_image

#include "game.h"

int main(int argc, char* argv[]) {
	game g;
	if(argv[1]!=NULL) {
		std::string map,wall;
		map.append((std::string) argv[1]);
		map.append("map");
		wall.append((std::string) argv[1]);
		wall.append("wall");
		const char* bufmap = map.c_str();
		const char* bufwall = wall.c_str();
		g.setMap(bufmap);
		g.setWall(bufwall);
	} else {
		g.rendMap();
	}
	g.start();
	return 0;
}
