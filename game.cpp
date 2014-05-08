#include "game.h"

game::game() {
	screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_SWSURFACE | SDL_FULLSCREEN);
	fullscreen=1;
	SDL_WM_SetCaption("The Forgotten: Genesis", "The Forgotten: Genesis");
	background=loadImage("bkg.png");
	blocks=loadImage("blocks.png");
	playerimg=loadImage("player.png");
	loading=loadImage("loading.png");
	wallimg=loadImage("wall.png");
	mobsimg=loadImage("mob.png");
	running=true;
	player1=new player(playerimg);
	srandom(time(NULL));
	speed=6;
	curspeed=6;
	camera.x=camera.y=coord.x=coord.y=0;
	camera.w=coord.w=SCREEN_WIDTH;
	camera.h=coord.h=SCREEN_HEIGHT;
	edest.x=edest.y=10;
	edest.w=edest.h=eclip.w=eclip.h=25;
	eclip.y=0;
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
	sand=20;
	cactus=21;
	snow=22;
	dirtwall=1;
	rockwall=2;
	stonewall=3;
	brickwall=4;
	woodwall=5;
	dir[0]=dir[1]=dir[2]=dir[3]=0;
	gravity=6;
	mouseDown=0;
	width=500;
	height=500;
	itemon=1;
	digging=0;
	holding=1;
	erase=0;
}

game::~game() {
	SDL_FreeSurface(blocks);
	SDL_FreeSurface(background);
	SDL_FreeSurface(playerimg);
	SDL_FreeSurface(loading);
	SDL_FreeSurface(wallimg);
	SDL_FreeSurface(mobsimg);
	SDL_Quit();
}

void game::getIP(char* ip) {
	if(ip == NULL) {
		clientcnct=new client(ip);
	} else {
		clientcnct=new client("localhost");
	}
}

SDL_Surface* game::loadImage(const char* filename) {
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;
    if((Surf_Temp = IMG_Load(filename)) == NULL) return NULL;
    Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);
    return Surf_Return;
}

void game::handleEvents() {
SDL_Event event;
        while(SDL_PollEvent(&event)) {
                switch(event.type) {
                        case SDL_QUIT:
                        		std::cout << "Exiting..." << std::endl;
                        		//save();
                                running=false;
                                return;
                        case SDL_KEYDOWN:
                                switch(event.key.keysym.sym) {
                                	case SDLK_UP: dir[2]=1; break;
          							case SDLK_LEFT: dir[0]=1; break;
    						        case SDLK_RIGHT: dir[1]=1; break;
    						        //case SDLK_DOWN: dir[3]=1; break;
    						        case SDLK_s: save(); break;
                                    case SDLK_ESCAPE:
                                        	if(fullscreen) {screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_SWSURFACE); fullscreen=0; std::cout << "Exiting Fullscreen..." << std::endl;
                                        	} else {screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32,SDL_SWSURFACE | SDL_FULLSCREEN); fullscreen=1; std::cout << "Entering Fullscreen..." << std::endl;}
                                        	//save();
                                			//running=false;
                                			return;
                                	case SDLK_1: holding=1; break;
                                	case SDLK_2: holding=2; break;
                                	case SDLK_5: if(erase) {erase=0;} else {erase=1;} break;
                                	case SDLK_4:
                                		if(holding==1) { 
                                			if(itemon>21) {
                                				itemon=1;
                                			} else {
                                				itemon++;
                                			}
                                		} else if(holding==2) { 
                                			if(itemon>4) {
                                				itemon=1;
                                			} else {
                                				itemon++;
                                			}
                                		}
                                		break;
                                	case SDLK_3:
                                		if(holding==1) { 
                                			if(itemon==1) {
                                				itemon=22;
                                			} else {
                                				itemon--;
                                			}
                                		} else if(holding==2) { 
                                			if(itemon==1) {
                                				itemon=5;
                                			} else {
                                				itemon--;
                                			}
                                		}
                                		break;
                                	case SDLK_LSHIFT: digging=1; break;
                                	case SDLK_i: std::cout << coord.x/25 << "," << coord.y/25 << std::endl; std::cout << itemon << std::endl; break;
                                }
                                break;
                        case SDL_KEYUP:
                                switch(event.key.keysym.sym) {
									case SDLK_UP: dir[2]=0; break;
            						case SDLK_LEFT: dir[0]=0; break;
            						case SDLK_RIGHT: dir[1]=0; break;
            						//case SDLK_DOWN: dir[3]=0; break;
            						case SDLK_LSHIFT: digging=0; break;
                                }
                                break;
                        case SDL_MOUSEBUTTONDOWN:
                        	mouseDown=1;
                        	break;
                        case SDL_MOUSEBUTTONUP:
                        	mouseDown=0;
                        	break;
                }
        }
}

void game::loadMap(const char* filename) {
        std::ifstream in(filename);
        if(!in.is_open()) {
                std::cout << "Problem with loading the file" << std::endl;
                return;
        }
        int width,height;
        in >> width;
        in >> height;
        int current;
        for(int i=0;i<height;i++) {
                std::vector<int> vec;
                for(int j=0;j<width;j++) {
                        if(in.eof()) {
                                std::cout << "File end reached too soon" << std::endl;
                                return;                        
                        }
                        in >> current;
                        if(current>=1 && current<=23) {
							vec.push_back(current);
                        }else{
                        	vec.push_back(0);
                        }
                }
                map.push_back(vec);
        }
        if(!in.eof()) {
        	int mapX, mapY;
        	//in >> mapX;
        	//in >> mapY;
        	//coord.x = mapX;
        	//coord.y = mapY;
        }
        in.close();
}

void game::loadWall(const char* filename) {
        std::ifstream in(filename);
        if(!in.is_open()) {
                std::cout << "Problem with loading the file" << std::endl;
                return;
        }
        int width,height;
        in >> width;
        in >> height;
        int current;
        for(int i=0;i<height;i++) {
                std::vector<int> vec;
                for(int j=0;j<width;j++) {
                        if(in.eof()) {
                                std::cout << "File end reached too soon" << std::endl;
                                return;                        
                        }
                        in >> current;
                        if(current>=1 && current<=23) {
							vec.push_back(current);
                        }else{
                        	vec.push_back(0);
                        }
                }
                wall.push_back(vec);
        }
        in.close();
}


void game::save() {
        char c[30];
        sprintf(c,"%d",(int)time(0));
        strcat(c,".map");
        std::cout << "Saved map to " << c << std::endl;
        std::ofstream out(c);
        out << map[0].size() << " " << map.size() << std::endl;
        for(int i=0;i<map.size();i++) {
        	for(int j=0;j<map[0].size();j++) {
	           	out << map[i][j] << " ";
            }
	        out << std::endl;
        }
        out.close();
        sprintf(c,"%d",(int)time(0));
        strcat(c,".wall");
        std::cout << "Saved wall to " << c << std::endl;
        std::ofstream out2(c);
        out2 << wall[0].size() << " " << wall.size() << std::endl;
        for(int i=0;i<wall.size();i++) {
        	for(int j=0;j<wall[0].size();j++) {
	           	out2 << wall[i][j] << " ";
            }
	        out2 << std::endl;
        }
        out2.close();
}


void game::showMap() {
	std::vector<SDL_Rect> testrect,test2rect;
	int start=(coord.x-(coord.x%TILE_SIZE))/TILE_SIZE;
	int end=(coord.x+coord.w+(TILE_SIZE-(coord.x+coord.w)%TILE_SIZE))/TILE_SIZE;
	if (start<0) start=0;
	if (end>map[0].size()) end=map[0].size();
	for (int i=0;i<map.size();i++) {
		for (int j=start;j<end;j++) {
			if (map[i][j]!=nothing) {
				SDL_Rect blockrect = {(map[i][j]-1)*TILE_SIZE,0,TILE_SIZE,TILE_SIZE};
				SDL_Rect destrect = {j*TILE_SIZE-coord.x,i*TILE_SIZE-coord.y};
				SDL_BlitSurface(blocks,&blockrect,screen,&destrect);
				if(map[i][j]==water || map[i][j]==nothing || map[i][j]==flower || map[i][j]==wood || map[i][j]==torch || map[i][j]==post || map[i][j]==leaf || map[i][j]==workbench || map[i][j]==chickenegg || map[i][j]==cactus) {
					test2rect.push_back(destrect);
				} else {
					testrect.push_back(destrect);
				}
			}
			if(map[i][j]==dirt || map[i][j]==grass) {
        		if(map[i-1][j]==nothing || map[i-1][j]==flower || map[i-1][j]==wood || map[i-1][j]==post || map[i-1][j]==chickenegg) {
        			map[i][j]=grass;
        		} else {
        			map[i][j]=dirt;
        		}
        	}
        	if(map[i][j]==wood) {
        		if(map[i+1][j]==nothing || map[i+1][j]==torch) {
        			int w=1;
        			for(int h=0; h<w; h++) {
        				if(map[i-h][j]==wood) {
        					j++;
        					map[i-h][j]=nothing;
        				}
        			}
        		}
        	}
        	if(map[i][j]==chickenegg) {
		   		int randhatch = random() % 100;
		   		if(randhatch==0 && mobvec.size()<10) {
		   			mobvec.push_back(new mobs(mobsimg, 50, 50, j*25, i*25, "chicken"));
		   			map[i][j]=nothing;
		   		}
		   		if(map[i+1][j]==nothing) {
		   			map[i][j]=nothing;
		   			map[i+1][j]=chickenegg;
		   		}
        	}
        }
    }
	colrect=testrect;
	waterrect=test2rect;
}

void game::showWall() {
	int start=(coord.x-(coord.x%TILE_SIZE))/TILE_SIZE;
	int end=(coord.x+coord.w+(TILE_SIZE-(coord.x+coord.w)%TILE_SIZE))/TILE_SIZE;
	if (start<0) start=0;
	if (end>wall[0].size()) end=wall[0].size();
	for (int i=0;i<wall.size();i++)
		for (int j=start;j<end;j++)
			if (wall[i][j]!=nothing) {
				SDL_Rect blockrect = {(wall[i][j]-1)*TILE_SIZE,0,TILE_SIZE,TILE_SIZE};
				SDL_Rect destrect = {j*TILE_SIZE-coord.x,i*TILE_SIZE-coord.y};
				SDL_BlitSurface(wallimg,&blockrect,screen,&destrect);
			}
}

void game::setMap(const char* map) {
	SDL_BlitSurface(loading,&camera,screen,NULL);
	SDL_Flip(screen);
	if(map!=NULL) {
		loadMap(map);
	}
}

void game::setWall(const char* wall) {
	if(wall!=NULL) {
		loadWall(wall);
	}
}

void game::start() {
	Uint32 start;
	while(running) {
		start=SDL_GetTicks();
		handleEvents();
		
		SDL_BlitSurface(background,&camera,screen,NULL);
		
		lastdir[0]=lastdir[1]=lastdir[2]=lastdir[3]=0; //left, right, up, down
		if(dir[0]) { coord.x-=curspeed; lastdir[0]=1;
		} else if(dir[1]) { coord.x+=curspeed; lastdir[1]=1; }
		if(dir[2]) { coord.y-=curspeed; lastdir[2]=1;
		} else if(dir[3]) { coord.y+=gravity; lastdir[3]=1; }
		showWall();
		showMap();
		
		if(digging) {
			int dX = ((SCREEN_WIDTH/2)+coord.x)/TILE_SIZE;
   			int dY = ((SCREEN_HEIGHT/2)+coord.y)/TILE_SIZE;
			if(dir[0]) { map[dY-1][dX]=map[dY-2][dX-1]=nothing; }
			if(dir[1]) { map[dY-1][dX]=map[dY-2][dX+1]=nothing; }
			if(dir[2]) { map[dY-2][dX]=map[dY-2][dX-1]=nothing; }
			if(dir[3]) { map[dY][dX]=map[dY][dX-1]=nothing; }
		}

		for(int i=0;i<colrect.size();i++) {
    		if(col.checkCollision(player1->getBox(), colrect[i]))  { //if colliding
       			if(lastdir[2]) { coord.y+=curspeed; lastdir[2]=0; //move back if moved up
       			} else if(lastdir[3]) { coord.y-=gravity; lastdir[3]=0;} //move back if moved down
       			dir[3]=false;
       			//if(lastdir[0]) { coord.x+=curspeed; lastdir[0]=0; //move back if moved left
       			//} else if(lastdir[1]) { coord.x-=curspeed; lastdir[1]=0;} //move back if moved right
   			} else {
   				dir[3]=true;
   			}
		}
   		
   		//std::cout << coord.x << "," << coord.y << std::endl;
   		
   		if(mouseDown) {
   			int mcX = (mouseX+coord.x)/TILE_SIZE;
   			int mcY = (mouseY+coord.y)/TILE_SIZE;
   			/*if(holding==3) {
	   			wall[mcY][mcX]=0;
	   		} else if(holding==4) {
	   			wall[mcY][mcX]=itemon;
	   		} else if(holding==1) {
	   				inventory[map[mcY][mcX]]++;
	   				map[mcY][mcX]=0;
	   		} else if(holding==2 && map[mcY][mcX]==nothing) {
		   		map[mcY][mcX]=itemon;
		   	}*/
		   	if(erase) {
		   		if(holding==1) {
		   			map[mcY][mcX]=nothing;
			   	} else if(holding==2) {
		   			wall[mcY][mcX]=nothing;
		   		}
		   	} else {
		   		if(holding==1 && map[mcY][mcX]==nothing) {
		   			map[mcY][mcX]=itemon;
		   		} else if(holding==2) {
		   			wall[mcY][mcX]=itemon;
		   		}
		   	}
   		}
        
        for(int i=0;i<mobvec.size();i++) {
			mobvec[i]->showMob(screen, coord);
			mobvec[i]->moveMob(map);
		}
		
		eclip.x=(itemon*25)-25;
		if(fullscreen){
			edest.x=mouseX;
			edest.y=mouseY;
		} else {
			edest.x=edest.y=10;
		}
		if(holding==1) { SDL_BlitSurface(blocks,&eclip,screen,&edest);
		} else if(holding==2) { SDL_BlitSurface(wallimg,&eclip,screen,&edest); }
		
		player1->showPlayer(screen);
		SDL_GetMouseState(&mouseX,&mouseY);
		SDL_Flip(screen);
		if(1000/30>(SDL_GetTicks()-start)) SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
}
