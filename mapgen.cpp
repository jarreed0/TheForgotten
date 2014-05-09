#include "mapgen.h"

mapgen::mapgen() {
	height = 1000;
	width = 1000;
	nothing=0;
	protect=999;
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
	sandwall=6;
	snowwall=7;
	chambers=0;
	sky = 40;
	srandom(time(NULL));
	biome = 0;
	biomesize=30;
	desert = 0;
	sandhills = 1;
	grasslands = 2;
	hills = 3;
	mountians = 4;
	forest = 5;
	tundra = 6;
	forest2 = 7;
	lake = 8;
	bscount=0;
}

mapgen::~mapgen() {

}

void mapgen::start() {
	std::cout << "Generating Map..." << std::endl;
	for(int h=0; h<height; h++) {
		std::vector<int > vec;
		std::vector<int > vecwall;
		for(int w=0; w<width; w++) {
			vec.push_back(0);
			vecwall.push_back(0);
		}
		map.push_back(vec);
		wall.push_back(vecwall);
	}
	render();
	save();
}

void mapgen::render() {
	int hloop=0;
	int sloop=0;
	int bloop=0;
	int hillsize = random() % 20 + 1;
	int hillheight;
	int biomesize = random() % 110 + 20;
	int biome = random() % 8;
	obiome=biome;
	if(biome==desert) {
		hillheight = random() % 3 + 27;
	} else if(biome==sandhills) {
		hillheight = random() % 12 + 18;
	} else if(biome==grasslands) {
		hillheight = random() % 3 + 27;
	} else if(biome==hills) {
		hillheight = random() % 12 + 18;
	} else if(biome==mountians) {
		hillheight = random() % 21 + 9;
	} else if(biome==forest || biome==forest2) {
		hillheight = random() % 5 + 25;
	} else if(biome==tundra) {
		hillheight = random() % 12 + 18;
	}
	int spot = (hillheight+sky);
	oheight=hillheight;
	for(int w=0; w<width; w++) {
		if(sloop>hillsize) {
			sloop=0;
			hillsize = random() % 20 + 1;
		}
		if(hloop>hillheight) {
			hloop=0;
			if(biome==desert) {
				hillheight = random() % 3 + 1;
			} else if(biome==sandhills) {
				hillheight = random() % 12 + 1;
			} else if(biome==grasslands) {
				hillheight = random() % 3 + 1;
			} else if(biome==hills) {
				hillheight = random() % 12 + 1;
			} else if(biome==mountians) {
				hillheight = random() % 21 + 1;
			} else if(biome==forest || biome==forest2) {
				hillheight = random() % 5 + 1;
			} else if(biome==tundra) {
				hillheight = random() % 12 + 1;
			} else if(biome==lake) {
				hillheight = spot-sky;
				std::cout << "lake" << std::endl;
			}
		}
		if(bloop>biomesize) {
			bloop=0;
			biomesize = random() % 110 + 20;
			biome = random() % 9;
			bscount=bscount+biomesize;
		}
		if(biomesize>=(width-bscount)) {
			hillheight=oheight;
			biome=obiome;
		}
		if(hillheight+sky>spot) {
			if(biome == forest || biome == grasslands || biome == hills || biome==forest2) {
				map[spot+1][w]=dirt;
				wall[spot+1][w]=dirtwall;
			}
			if(biome == desert || biome == sandhills) {
				map[spot+1][w]=sand;
				wall[spot+1][w]=sandwall;
			}
			if(biome == mountians) {
				map[spot+1][w]=rock;
				wall[spot+1][w]=rockwall;
			}
			if(biome == tundra) {
				map[spot+1][w]=snow;
				wall[spot+1][w]=snowwall;
			}
			if(biome == lake) {
				map[spot][w]=water;
				wall[spot][w]=sandwall;
			}
			if(biome == forest|| biome==forest2) {
				int randtree = random() % 10;
				if(randtree==0) {
					int randtsize = random() % 13 + 5;
					for(int s=0; s<randtsize; s++) {
						map[spot-s][w]=wood;
					}
					map[spot-randtsize+1][w-1]=leaf;
					map[spot-randtsize+1][w+1]=leaf;
					map[spot-randtsize][w]=leaf;
					map[spot-randtsize][w-1]=leaf;
					map[spot-randtsize][w+1]=leaf;
					map[spot-randtsize][w-2]=leaf;
					map[spot-randtsize][w+2]=leaf;
					map[spot-randtsize-1][w]=leaf;
					map[spot-randtsize-1][w-1]=leaf;
					map[spot-randtsize-1][w+1]=leaf;
					map[spot-randtsize-1][w-2]=leaf;
					map[spot-randtsize-1][w+2]=leaf;
					map[spot-randtsize-2][w]=leaf;
					map[spot-randtsize-2][w-1]=leaf;
					map[spot-randtsize-2][w+1]=leaf;
					map[spot-randtsize-2][w-2]=leaf;
					map[spot-randtsize-2][w+2]=leaf;
					map[spot-randtsize-3][w]=leaf;
					map[spot-randtsize-3][w-1]=leaf;
					map[spot-randtsize-3][w+1]=leaf;
					std::cout << "plant" << std::cout;
				}
			}
			if(biome == desert) {
				int randcac = random() % 10;
				if(randcac==0) {
					map[spot][w]=cactus;
					map[spot-1][w]=cactus;
					map[spot-2][w]=cactus;
					std::cout << "plant" << std::cout;
				}
			}
			if(biome == grasslands || biome == hills) {
				int randcac = random() % 10;
				if(randcac==0) {
					map[spot][w]=flower;
					std::cout << "plant" << std::cout;
				}
			}
			spot++;
		} else if(hillheight+sky<spot) {
			if(biome == forest || biome==forest2 || biome == grasslands || biome == hills) {
				map[spot-1][w]=dirt;
				wall[spot-1][w]=dirtwall;
			}
			if(biome == desert || biome == sandhills) {
				map[spot-1][w]=sand;
				wall[spot-1][w]=sandwall;
			}
			if(biome == mountians) {
				map[spot-1][w]=rock;
				wall[spot-1][w]=rockwall;
			}
			if(biome == tundra) {
				map[spot-1][w]=snow;
				wall[spot-1][w]=snowwall;
			}
			if(biome == lake) {
				map[spot][w]=water;
				wall[spot][w]=sandwall;
			}
			if(biome == forest || biome==forest2) {
				int randtree = random() % 10;
				if(randtree==0) {
					int randtsize = random() % 13 + 5;
					for(int s=2; s<randtsize; s++) {
						map[spot-s][w]=wood;
					}
					map[spot-randtsize+1][w-1]=leaf;
					map[spot-randtsize+1][w+1]=leaf;
					map[spot-randtsize][w]=leaf;
					map[spot-randtsize][w-1]=leaf;
					map[spot-randtsize][w+1]=leaf;
					map[spot-randtsize][w-2]=leaf;
					map[spot-randtsize][w+2]=leaf;
					map[spot-randtsize-1][w]=leaf;
					map[spot-randtsize-1][w-1]=leaf;
					map[spot-randtsize-1][w+1]=leaf;
					map[spot-randtsize-1][w-2]=leaf;
					map[spot-randtsize-1][w+2]=leaf;
					map[spot-randtsize-2][w]=leaf;
					map[spot-randtsize-2][w-1]=leaf;
					map[spot-randtsize-2][w+1]=leaf;
					map[spot-randtsize-2][w-2]=leaf;
					map[spot-randtsize-2][w+2]=leaf;
					map[spot-randtsize-3][w]=leaf;
					map[spot-randtsize-3][w-1]=leaf;
					map[spot-randtsize-3][w+1]=leaf;
					std::cout << "plant" << std::cout;
				}
			}
			if(biome == desert) {
				int randcac = random() % 10;
				if(randcac==0) {
					map[spot-2][w]=cactus;
					map[spot-3][w]=cactus;
					map[spot-4][w]=cactus;
					std::cout << "plant" << std::cout;
				}
			}
			if(biome == grasslands || biome == hills) {
				int randcac = random() % 10;
				if(randcac==0) {
					map[spot-2][w]=flower;
					std::cout << "plant" << std::cout;
				}
			}
			spot--;
		} else {
			if(biome == forest || biome==forest2 || biome == grasslands || biome == hills) {
				map[spot][w]=dirt;
				wall[spot][w]=dirtwall;
			}
			if(biome == desert || biome == sandhills) {
				map[spot][w]=sand;
				wall[spot][w]=sandwall;
			}
			if(biome == mountians) {
				map[spot][w]=rock;
				wall[spot][w]=rockwall;
			}
			if(biome == tundra) {
				map[spot][w]=snow;
				wall[spot][w]=snowwall;
			}
			if(biome == lake) {
				map[spot][w]=water;
				wall[spot][w]=sandwall;
				int randboat = random() % 20;
				if(randboat==0 && sloop>6) {
					std::cout << "boat" << std::endl;
					map[spot-5][w]=brick;
					map[spot-6][w-1]=brick;
					map[spot-5][w-1]=brick;
					map[spot-4][w-1]=post;
					map[spot-3][w-1]=post;
					map[spot-2][w-1]=plank;
					map[spot-1][w-2]=plank;
					map[spot-1][w-3]=plank;
					map[spot-1][w-4]=plank;
					map[spot-2][w-5]=plank;
					map[spot-3][w-5]=torch;
					wall[spot-2][w-2]=woodwall;
					wall[spot-2][w-3]=woodwall;
					wall[spot-2][w-4]=woodwall;
				}
			}
			if(biome == forest || biome==forest2) {
				int randtree = random() % 10;
				if(randtree==0) {
					int randtsize = random() % 13 + 5;
					for(int s=1; s<randtsize; s++) {
						map[spot-s][w]=wood;
					}
					map[spot-randtsize+1][w-1]=leaf;
					map[spot-randtsize+1][w+1]=leaf;
					map[spot-randtsize][w]=leaf;
					map[spot-randtsize][w-1]=leaf;
					map[spot-randtsize][w+1]=leaf;
					map[spot-randtsize][w-2]=leaf;
					map[spot-randtsize][w+2]=leaf;
					map[spot-randtsize-1][w]=leaf;
					map[spot-randtsize-1][w-1]=leaf;
					map[spot-randtsize-1][w+1]=leaf;
					map[spot-randtsize-1][w-2]=leaf;
					map[spot-randtsize-1][w+2]=leaf;
					map[spot-randtsize-2][w]=leaf;
					map[spot-randtsize-2][w-1]=leaf;
					map[spot-randtsize-2][w+1]=leaf;
					map[spot-randtsize-2][w-2]=leaf;
					map[spot-randtsize-2][w+2]=leaf;
					map[spot-randtsize-3][w]=leaf;
					map[spot-randtsize-3][w-1]=leaf;
					map[spot-randtsize-3][w+1]=leaf;
					std::cout << "plant" << std::cout;
				}
			}
			if(biome == desert) {
				int randcac = random() % 10;
				if(randcac==0) {
					map[spot-1][w]=cactus;
					map[spot-2][w]=cactus;
					map[spot-3][w]=cactus;
					std::cout << "plant" << std::cout;
				}
			}
			if(biome == grasslands) {
				int randegg = random() % 20;
				if(randegg==0) {
					map[spot-1][w]=chickenegg;
					std::cout << "egg" << std::cout;
				}
			}
			if(biome == grasslands || biome == hills) {
				int randcac = random() % 8;
				if(randcac==0) {
					map[spot-1][w]=flower;
					std::cout << "plant" << std::cout;
				}
			}
			if(sloop>10 && biome==grasslands) {
				int randbuild=random() % 2;
				if(randbuild==0) {
					for(int s=0; s<9; s++) {
						map[spot-1][w-s]=stone;
						map[spot-6][w-s]=stone;
						wall[spot-1][w-s]=stonewall;
						wall[spot-2][w-s]=stonewall;
						wall[spot-3][w-s]=stonewall;
						wall[spot-4][w-s]=stonewall;
						wall[spot-5][w-s]=stonewall;
						wall[spot-6][w-s]=stonewall;
					}
					map[spot-5][w]=stone;
					map[spot-4][w]=stone;	
					map[spot-5][w-8]=stone;
					map[spot-4][w-8]=stone;
					map[spot-5][w-1]=torch;
					map[spot-5][w-7]=torch;
					map[spot-2][w-3]=table;
					std::cout << "building" << std::cout;	
				}
			}
			
			spot=hillheight+sky;
			hloop++;
		}
		sloop++;
		bloop++;
	}	
	for(int h=2; h<height; h++) {
		for(int w=0; w<width; w++) {
			if(map[h-1][w] == dirt) {
				int randrock = random() & 10;
				if(h>((45+sky)-randrock)) {
					map[h][w]=rock;
					wall[h][w]=rockwall;
				} else {
					map[h][w]=dirt;
					wall[h][w]=dirtwall;
				}
			}
			if(map[h-1][w] == snow) {
				int randrock = random() & 10;
				if(h>((40+sky)-randrock)) {
					map[h][w]=rock;
					wall[h][w]=rockwall;
				} else {
					map[h][w]=snow;
					wall[h][w]=snowwall;
				}
			}
			if(map[h-1][w] == water) {
				int randrock = random() & 10;
				if(h>((20+sky)-randrock)) {
					map[h][w]=sand;
					wall[h][w]=sandwall;
				} else {
					map[h][w]=water;
					wall[h][w]=sandwall;
				}
			}
			if(map[h-1][w] == rock) {
				int randblock = random() % 1000;
				if(randblock==1) {
					map[h][w]=dirt;
					wall[h][w]=dirtwall;
				} else if(randblock==2) {
					map[h][w]=iron;
					wall[h][w]=rockwall;
				} else if(randblock==3) {
					map[h][w]=copper;
					wall[h][w]=rockwall;
				} else if(randblock==4) {
					map[h][w]=stone;
					wall[h][w]=stonewall;
				} else if(randblock==5) {
					map[h][w]=brick;
					wall[h][w]=brickwall;
				} else {
					map[h][w]=rock;
					wall[h][w]=rockwall;
				}
			}
			if(map[h-2][w] == rock) {
				if(map[h-1][w] == copper || map[h-1][w] == rock || map[h-1][w] == iron || map[h-1][w] == brick || map[h-1][w] == stone) {
					int randblock = random() % 1000;
					if(randblock==1) {
						map[h][w]=dirt;
						wall[h][w]=dirtwall;
					} else if(randblock==2) {
						map[h][w]=iron;
						wall[h][w]=rockwall;
					} else if(randblock==3) {
						map[h][w]=copper;
						wall[h][w]=rockwall;
					} else if(randblock==4) {
						map[h][w]=stone;
						wall[h][w]=stonewall;
					} else if(randblock==5) {
						map[h][w]=brick;
						wall[h][w]=brickwall;
					} else {
						map[h][w]=rock;
						wall[h][w]=rockwall;
					}
				}
			}
			if(map[h-1][w] == sand) {
				int randrock = random() & 10;
				if(h>((45+sky)-randrock)) {
					map[h][w]=rock;
					wall[h][w]=rockwall;
				} else {
					map[h][w]=sand;
					wall[h][w]=sandwall;
				}
			}
		}
	}
}

void mapgen::save() {
        char c[30];
        sprintf(c,"%d",(int)time(0));
        char t[30];
        for(int i=0; i<30; i++) {
        	t[i]=c[i];
        }
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
        out << (width/2) << " " << 0;
        out.close();
        //sprintf(c,"%d",(int)time(0));
        strcat(t,".wall");
        std::cout << "Saved wall to " << t << std::endl;
        std::ofstream out2(t);
        out2 << wall[0].size() << " " << wall.size() << std::endl;
        for(int i=0;i<wall.size();i++) {
        	for(int j=0;j<wall[0].size();j++) {
	           	out2 << wall[i][j] << " ";
            }
	        out2 << std::endl;
        }
        out2.close();
}


