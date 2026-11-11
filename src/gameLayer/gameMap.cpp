#include "gameMap.h"
#include <asserts.h>

void GameMap::create(int width, int height)
{
	*this = {}; //resets all the data
	mapData.resize(width * height);

	this->width = width;
	this->height = height;

	for (auto& e : mapData) 
	{
		e = {}; // clear block data
	}
}

Block& GameMap::getBlockUnSafe(int x, int y)
{
	permaAssertCommentDevelopement(mapData.size() == width * height, "Map data not initialized");

	permaAssertCommentDevelopement(x >= 0 &&
		y >= 0 && x < width && y < height, "getBlockUnSafe out of bounds error");

	return mapData[x + y * width];
}

Block* GameMap::getBlockSafe(int x, int y)
{
	permaAssertCommentDevelopement(mapData.size() == width * height, "Map data not initialized");
	
	if (x < 0 || y < 0 || x >= width || y >= height)
	{
		return nullptr;
	}

	return &mapData[x + y * width];
}


