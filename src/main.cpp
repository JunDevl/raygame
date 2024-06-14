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
			std::cout << "asdfasdfasdf";
		}
		scene.Logic();
		scene.Draw();
	}

	CloseWindow();
}

