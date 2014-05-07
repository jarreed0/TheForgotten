#include "collision.h"

collision::collision() {}

collision::~collision() {}

bool collision::checkCollision(SDL_Rect A, SDL_Rect B) {
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

	//ground
    if( bottomA <= topB ) {
        return false;
    }

	//cieling
    if( topA >= bottomB ) {
        return false;
    }

	//right
    if( rightA <= leftB ) {
        return false;
    }

	//left
    if( leftA >= rightB ) {
        return false;
    }

    return true;
}

bool collision::whichCollision(SDL_Rect A, SDL_Rect B) {
	bool dir[4];
	dir[0]=dir[1]=dir[2]=dir[3]=0;

    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

	//ground
    if( bottomA <= topB ) {
        dir[3]=0;
    } else {
    	dir[3]=1;
    	std::cout << "ground" << std::endl;
    }

	//cieling
    if( topA >= bottomB ) {
        dir[2]=0;
    } else {
    	dir[2]=1;
        std::cout << "cieling" << std::endl;
    }

	//right
    if( rightA <= leftB ) {
        dir[1]=0;
    } else {
    	dir[1]=1;
    	std::cout << "right" << std::endl;
    }

	//left
    if( leftA >= rightB ) {
        dir[0]=0;
    } else {
    	dir[0]=1;
    	std::cout << "left" << std::endl;
    }

    return dir;
}

