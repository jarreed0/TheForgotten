#include "player.h"

player::player(SDL_Surface *playerimg) {
	x=((640/2)-25);
	y=((430/2)-25);
	xVel=yVel=0;
	img=playerimg;
	destrect.w=clip.w=25;
	destrect.h=clip.h=45;
	clip.x=clip.y=0;
	destrect.x=x;
	destrect.y=y;
}

player::~player() {}


void player::showPlayer(SDL_Surface* screen) {
	SDL_BlitSurface(img,&clip,screen,&destrect);
}	

SDL_Rect player::getBox() {
	return destrect;
}

