#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#ifndef MOBS_H
#define MOBS_H

class mobs {
	SDL_Rect destrect, clip;
	SDL_Surface* img;
	int x,y;
	int xVel, yVel;
	const char* mobtype;
	int skin;
	int w,h;
	int water,grass,rock,flower,dirt,nothing,copper,iron,wood,torch,table,stone,brick,leaf,cobble,post,chamber,workbench,plank,chickenegg;
	int closestx, closesty;
	public:
	mobs(SDL_Surface *mobimg, int width, int height, int mobx, int moby, const char* type);
	~mobs();
	SDL_Rect getBox();
	void showMob(SDL_Surface* screen, SDL_Rect coord);
	void moveMob(std::vector<std::vector<int> > map);
};

#endif
