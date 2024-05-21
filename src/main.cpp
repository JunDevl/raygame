#include <iostream>
#include <raylib.h>

int main() {
	
	InitWindow(640, 360, "raygame test");

	SetTargetFPS(60);

	SetWindowIcon(LoadImage("raygameicon.png"));

	while(!WindowShouldClose()) {
		BeginDrawing();

		ClearBackground(WHITE);

		DrawText("akokakoak", 300, 400, 24, GREEN);

		EndDrawing();
	}

	CloseWindow();

}

