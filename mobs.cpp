#include "mobs.h"

mobs::mobs(SDL_Surface *mobimg, int width, int height, int mobx, int moby, const char* type) {
	img=mobimg;
	destrect.w=clip.w=width;
	destrect.h=clip.h=height;
	clip.x=clip.y=0;
	x=mobx;
	y=moby;
	destrect.x=x;
	destrect.y=y;
	mobtype=type;
	std::cout << "chicken hatched" << std::endl;
	w=width;
	h=height;
	srandom(time(NULL));
	nothing=0;
	grass=1;
	rock=2;
	flower=3;
	water=4;
	dirt=5;
	copper=6;
	iron=7;
	wood=8;
	torch=9;
	table=10;
	stone=11;
	brick=12;
	leaf=13;
	cobble=14;
	post=15;
	chamber=16;
	workbench=17;
	plank=18;
	chickenegg=19;
}

mobs::~mobs() {}

void mobs::showMob(SDL_Surface* screen, SDL_Rect coord) {
	destrect.x=x-coord.x;
	destrect.y=(y-coord.y)-25;
	if(destrect.x+destrect.w>0 && destrect.x<640 && destrect.y+destrect.h>0 && destrect.y<480) {
		SDL_BlitSurface(img,&clip,screen,&destrect);
	}
}

void mobs::moveMob(std::vector<std::vector<int> > map) {
	if(map[(y/25)+1][x/25]==water || map[(y/25)+1][x/25]==nothing || map[(y/25)+1][x/25]==flower || map[(y/25)+1][x/25]==wood || map[(y/25)+1][x/25]==torch || map[(y/25)+1][x/25]==post || map[(y/25)+1][x/25]==leaf || map[(y/25)+1][x/25]==workbench || map[(y/25)+1][x/25]==chickenegg) { y=y+6;
	} else { y=y-6; }
	for(int j=0; j<map[0].size(); j++) {
		if(map[y/25][j]==water) {
			closestx=(j*25);
			break;
		}
	}
	if(x<closestx) x=x+4;
}

SDL_Rect mobs::getBox() {
	return destrect;
}

