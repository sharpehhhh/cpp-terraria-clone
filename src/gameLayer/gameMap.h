#pragma once
#include <vector>
#include <blocks.h>

struct GameMap
{
	int width{ 0 };
	int height{ 0 };

	std::vector<Block> mapData{};

	void create(int width, int height);

	Block& getBlockUnSafe(int x, int y);
	Block* getBlockSafe(int x, int y);
};