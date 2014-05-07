#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#ifndef PLAYER_H
#define PLAYER_H

class player {
	SDL_Rect destrect, clip;
	SDL_Surface* img;
	int x,y;
	int xVel, yVel;
	public:
	player(SDL_Surface *playerimg);
	~player();
	void showPlayer(SDL_Surface* screen);
	SDL_Rect getBox();
};

#endif
