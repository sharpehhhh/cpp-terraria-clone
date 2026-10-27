#include <iostream>
#include <raylib.h>
#include <fstream>
#include "gameMain.h"

struct GameData
{

	float positionX = 100.0f;
	float positionY = 100.0f;

}gameData;

bool initGame()
{
	// reset game state
	gameData = {}; 

	return true;
}

bool updateGame()
{
	Color c;
	c.r = 255;
	c.g = 0;
	c.b = 0;
	c.a = 255;

	float deltaTime = GetFrameTime();
	if (deltaTime > 1.0f / 5) { deltaTime = 1 / 5.0f; }

	if (IsKeyDown(KEY_A)) { gameData.positionX -= 500.0f * deltaTime; }
	if (IsKeyDown(KEY_D)) { gameData.positionX += 500.0f * deltaTime; }
	if (IsKeyDown(KEY_W)) { gameData.positionY -= 500.0f * deltaTime; }
	if (IsKeyDown(KEY_S)) { gameData.positionY += 500.0f * deltaTime; }

	DrawRectangle(gameData.positionX, gameData.positionY, 50.0f, 50.0f, c);

	return true;
}

void closeGame()
{
	std::cout << "Closing game" << '\n';

	std::ofstream f(RESOURCES_PATH "f.txt");
	f << "Game closed.\n";
	f.close();
}
