#include <iostream>
#include <raylib.h>
#include <fstream>
#include "gameMain.h"
#include "gameMap.h"
#include "assetManager.h"

struct GameData
{
	GameMap gameMap{};
}gameData{};

namespace 
{
	AssetManager assetManager{};
}


bool initGame()
{
	assetManager.loadAll();

	gameData.gameMap.create(30, 10);

	gameData.gameMap.getBlockUnSafe(0, 0).type = Block::dirt;
	gameData.gameMap.getBlockUnSafe(1, 1).type = Block::dirt;
	gameData.gameMap.getBlockUnSafe(2, 2).type = Block::dirt;
	gameData.gameMap.getBlockUnSafe(3, 3).type = Block::dirt;
	gameData.gameMap.getBlockUnSafe(4, 4).type = Block::dirt;

	return true;
}

bool updateGame()
{
	float deltaTime { GetFrameTime() };

	if (deltaTime > 1.0f / 5) 
	{ 
		deltaTime = 1 / 5.0f; 
	}

	ClearBackground({ 75, 75, 150, 255 });

	for (int y = 0; y < gameData.gameMap.height; ++y)
	{
		for (int x = 0; x < gameData.gameMap.width; ++x)
		{
			auto& block = gameData.gameMap.getBlockUnSafe(x, y);

			if (block.type != Block::air)
			{
				float size{ 32.0f };
				float posX{ x * size };
				float posY{ y * size };

				DrawTexturePro(assetManager.dirt, 
					Rectangle{ 0.f, 0.f, (float) assetManager.dirt.width, (float) assetManager.dirt.height },
					{ posX, posY, size, size },	// destination
					{0, 0},						// origin (coordinates)
					0.f,						// rotation
					WHITE);						// tint
			}
		}
	}

	return true;
}

void closeGame()
{
}
