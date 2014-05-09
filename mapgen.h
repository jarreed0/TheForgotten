#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <SDL/SDL.h>
#ifndef MAPGEN_H
#define MAPGEN_H

class mapgen {
	int height, width;
	int water,grass,rock,flower,dirt,nothing,protect,copper,iron,wood,torch,table,stone,brick,leaf,cobble,post,chamber,workbench,plank,chickenegg,sand,cactus,snow;
	int dirtwall, rockwall, stonewall, brickwall, woodwall;
	int chambers;
	int sky;
	int biome;
	int biomesize;
	int desert, sandhills, grasslands, hills, mountians, forest, forest2, tundra, lake;
	int obiome, oheight, bscount;
	public:
	std::vector<std::vector<int> > map;
	std::vector<std::vector<int> > wall;
	mapgen();
	~mapgen();
	void start();
	void render();
	void save();
};

#endif
