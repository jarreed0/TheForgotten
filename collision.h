#include <SDL/SDL.h>
#include <iostream>
#include <vector>
#ifndef COLLISION_H
#define COLLISION_H

class collision {
	public:
	collision();
	~collision();
	bool checkCollision(SDL_Rect A, SDL_Rect B);
	bool whichCollision(SDL_Rect A, SDL_Rect B);
};

#endif
