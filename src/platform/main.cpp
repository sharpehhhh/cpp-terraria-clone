#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

#include "imguiThemes.h"
#include "gameMain.h"

int main()
{

#if PRODUCTION_BUILD == 1
	SetTraceLogLevel(LOG_NONE);
#endif

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 600, "Hello Raylib");
	SetExitKey(KEY_NULL);
	SetTargetFPS(500);
	
#pragma region imgui
	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;

	setup_catppuccin_mocha_theme();
#pragma endregion

	if (!initGame())
	{
		return 0;
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

#pragma region imgui
		rlImGuiBegin();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
		ImGui::PopStyleColor(2);
#pragma endregion

#pragma region imgui windows
		ImGui::Begin("Styles");

		ImGui::Text("Change styles here: ");

		if (ImGui::Button("Cat Style"))
		{
			setup_catppuccin_mocha_theme();
			std::cout << "Using cat style.\n";
		}

		ImGui::SameLine();

		if (ImGui::Button("Reset to Dark Style"))
		{
			ImGui::StyleColorsDark();
			std::cout << "reset to dark Style.\n";
		}

		ImGui::End();

		// Second Window
		ImGui::Begin("Second Window");

		ImGui::Text("Hello");
		ImGui::Separator();
		ImGui::NewLine();
		static float a = 0.0f;
		ImGui::SliderFloat("Slider", &a, 0.0f, 1.0f);
		

		ImGui::End();
#pragma endregion

		ImGui::Begin("Test Window");

		ImGui::End();

		if (!updateGame())
		{
			CloseWindow();
		}

#pragma region imgui
		rlImGuiEnd();
#pragma endregion
		EndDrawing();
	}

	closeGame();

	CloseWindow();

#pragma region imgui
	rlImGuiShutdown();
#pragma endregion


	return 0;
}