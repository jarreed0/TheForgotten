#include <iostream>
#include <fstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <unistd.h>
#include "player.h"
#include "collision.h"
#include "mobs.h"
#include "mapgen.h"
#ifndef GAME_H
#define GAME_H

class game {
	SDL_Surface* screen,*background,*blocks,*playerimg,*loading,*wallimg,*mobsimg;
	SDL_Rect camera,coord;
	SDL_Rect edest, eclip;
	SDL_Surface* loadImage(const char* filename);
	bool fullscreen;
	void handleEvents();
	bool running;
	int mouseX, mouseY;
	std::vector<SDL_Rect> colrect,waterrect;
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > wall;
	int inventory[20];
	int itemon,holding;
	bool erase;
	std::vector<mobs*> mobvec;
	static const int SCREEN_WIDTH=640;
	static const int SCREEN_HEIGHT=480;
	int speed, curspeed;
	int colorkey;
	void loadMap(const char* filename);
	void loadWall(const char* filename);
	void showMap();
	void showWall();
	void save();
	player* player1;
	mapgen* generatem;
	collision col;
	int water,grass,rock,flower,dirt,nothing,copper,iron,wood,torch,table,stone,brick,leaf,cobble,post,chamber,workbench,plank,chickenegg,sand,cactus,snow;
	int dirtwall, rockwall, stonewall, brickwall, woodwall;
	bool dir[4];
	bool lastdir[4];
	bool newdir[4];
	int gravity;
	bool mouseDown;
	int mapwidth;
	int mapheight;
	char* mapName;
	bool digging;
	public:
	game();
	~game();
	void setMap(const char* map);
	void setWall(const char* wall);
	void rendMap();
	void start();
	static const int TILE_SIZE = 25;
	bool coldir[4];
};

#endif
