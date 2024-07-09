#include <iostream>
#include <raylib.h>

#include "pong.h"
#include "general.h"

int main() {

	float window_width = 640;
	float window_height = 360;

	SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);

	InitWindow(window_width, window_height, "raygame test");

	SetTargetFPS(120);

	//SetWindowIcon₢(LoadImage("../resources/icons/raygameicon.png"));

	Scene scene(window_width, window_height);

	while(!WindowShouldClose()) {
		if (IsWindowResized()) {
			window_width = GetScreenWidth();
			window_height = GetScreenHeight();
			std::cout << window_width << std::endl;
			std::cout << window_height << std::endl;
			SetWindowSize(window_width, window_height);
		}
		scene.Logic();
		scene.Draw();
	}

	CloseWindow();
}

