#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

int main()
{
	
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 600, "Hello Raylib");
	
#pragma region imgui
	rlImGuiSetup(true);

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.FontGlobalScale = 2;
#pragma endregion
	

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

#pragma region imgui
		rlImGuiBegin();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()->ID);
		ImGui::PopStyleColor(2);
#pragma endregion

		DrawText("First Window", 200, 200, 20, BLACK);

		DrawRectangle(50, 50, 200, 100, {255, 0, 0, 127});
		DrawRectangle(60, 60, 200, 100, {0, 255, 0, 127});

#pragma region imgui windows
		ImGui::Begin("First Window");

		ImGui::Text("Hello");

		if (ImGui::Button("Button"))
		{
			std::cout << "Pressed button.\n";
		}

		ImGui::SameLine();

		if (ImGui::Button("Button2"))
		{
			std::cout << "Pressed second button.\n";
		}

		ImGui::ShowDemoWindow();

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

#pragma region imgui
		rlImGuiEnd();
#pragma endregion


		EndDrawing();
	}

#pragma region imgui
	rlImGuiShutdown();
#pragma endregion

	CloseWindow();

	return 0;
}