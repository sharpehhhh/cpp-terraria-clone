#include <iostream>
#include <raylib.h>
#include <fstream>
#include "gameMain.h"
#include "gameMap.h"
#include "assetManager.h"
#include "helpers.h"

struct GameData
{
	GameMap gameMap{};
	Camera2D camera{};
}gameData{};

namespace 
{
	AssetManager assetManager{};
}


bool initGame()
{
	assetManager.loadAll();

	gameData.gameMap.create(30, 30);

	// shitty world gen
	for (int y = 0; y < gameData.gameMap.height; y++)
	{
		for (int x = 0; x < gameData.gameMap.width; x++)
		{
			float s = (std::sin(x) + 0.2f) / 2.0f;
			float s2 = (std::sin(x * 0.5) + 1.0f) / 2.0f;

			if (gameData.gameMap.height - (gameData.gameMap.height * 0.3 * s) - gameData.gameMap.height * 0.5 * s2 < y)
			{
				gameData.gameMap.getBlockUnSafe(x, y).type = Block::dirt;
			}
			else if (gameData.gameMap.height - (gameData.gameMap.height * 0.5 * s) - gameData.gameMap.height * 0.5 * s2 < y)
			{
				gameData.gameMap.getBlockUnSafe(x, y).type = Block::grassBlock;
			}
			else
			{
				gameData.gameMap.getBlockUnSafe(x, y).type = Block::air;
			}

 		}
	}

	gameData.camera.target = { 0.0f, 0.0f };
	gameData.camera.offset = { 0.0f, 0.0f };
	gameData.camera.zoom = 50.0f; 

	return true;
}

bool updateGame()
{
	float deltaTime { GetFrameTime() };

	if (deltaTime > 1.0f / 5) 
	{ 
		deltaTime = 1 / 5.0f; 
	}

	gameData.camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };

	ClearBackground({ 75, 75, 150, 255 });

#pragma region camera movement

	if (IsKeyDown(KEY_A)) gameData.camera.target.x -= 10.0f * deltaTime;
	if (IsKeyDown(KEY_D)) gameData.camera.target.x += 10.0f * deltaTime;
	if (IsKeyDown(KEY_W)) gameData.camera.target.y -= 10.0f * deltaTime;
	if (IsKeyDown(KEY_S)) gameData.camera.target.y += 10.0f * deltaTime;
#pragma endregion

	BeginMode2D(gameData.camera);

	for (int y = 0; y < gameData.gameMap.height; ++y)
	{
		for (int x = 0; x < gameData.gameMap.width; ++x)
		{
			auto& block = gameData.gameMap.getBlockUnSafe(x, y);

			if (block.type != Block::air)
			{
				Rectangle textureUV;
				textureUV.width = 32.0f;
				textureUV.height = 32.0f;
				textureUV.x = block.type * 32.0f;
				textureUV.y = 0.0f;

				DrawTexturePro(assetManager.textures, 
					getTextureAtlas(block.type, 0, 32, 32), // source
					{ (float)x, (float)y, 1, 1 },	// destination
					{0, 0},						// origin (coordinates)
					0.0f,						// rotation
					WHITE);						// tint
			}
		}
	}

	EndMode2D();

	return true;
}

void closeGame()
{
}
