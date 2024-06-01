#include <iostream>
#include <raylib.h>
#include <tuple>

#include "headers.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 360

#ifdef HEADERS_H

#ifdef CLASSES_H
class Entity {
public:
	float x, y;
	int speed;
};

class Paddle : public Entity {
public:
	float width = 15.0f;
	float height = 75.0f;

	bool is_left_sided;

	int score;

	Paddle(bool is_left_sided) : is_left_sided(is_left_sided) {
		speed = 225;
		y = (WINDOW_HEIGHT/2) - (height/2);

		if(is_left_sided) {
			x = 5.0f;
		}else {
			x = WINDOW_WIDTH - width - 5.0f;
		}
	}
};

class Ball : public Entity {

};

#endif

#include "inputs.cpp"

enum Scene::Gamestate {
	mainmenu, active, pausemenu
};

struct Scene::Menu {
	static constexpr float BUTTONS_WIDTH = 50.0f;
	static constexpr float BUTTONS_HEIGHT = 20.0f;
	static constexpr float BUTTONS_XPOS = (WINDOW_WIDTH/2) - (BUTTONS_WIDTH/2);
	static constexpr float BUTTONS_OFFSET = 10.0f;

	Color buttons_color = YELLOW;

	struct Play {
		Rectangle play_btn {BUTTONS_XPOS, 20.0f, BUTTONS_WIDTH, BUTTONS_HEIGHT};
		std::string text = "Play Game"
	};
	struct Options {
		Rectangle options_btn {BUTTONS_XPOS, play_btn.y + BUTTONS_OFFSET, BUTTONS_WIDTH, BUTTONS_HEIGHT};
		std::string text = "Options"
	};
	struct Quit {
		Rectangle quit_btn {BUTTONS_XPOS, options_btn.y + BUTTONS_OFFSET, BUTTONS_WIDTH, BUTTONS_HEIGHT};
		std::string text = "Quit Game"
	};
};

void Scene::Draw(Paddle& p1, Paddle& p2, Ball& ball, Gamestate& gamestate) {
	BeginDrawing();

	ClearBackground(GRAY);

	//while(gamestate == mainmenu) {
	//	DrawRectangleRec()
	//}

	DrawRectangle(p1.x, p1.y, p1.width, p1.height, WHITE);
	DrawRectangle(p2.x, p2.y, p2.width, p2.height, WHITE);

	DrawCircle(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 10, WHITE);

	DrawFPS(25, 10);

	EndDrawing();
}

void Scene::Logic(Paddle& p1, Paddle& p2, Ball& ball, Gamestate& gamestate) {
	Scene::Update(p1, p2, ball, gamestate);
}

#endif

// decided to create a ping pong game (a lot of work though)

int main() {
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "raygame test");

	SetConfigFlags(FLAG_VSYNC_HINT);

	SetTargetFPS(120);

	SetWindowIcon(LoadImage("raygameicon.png"));

	Scene::Gamestate gamestate = Scene::Gamestate::mainmenu;
	Scene::Menu menu;

	Paddle p1(true);
	Paddle p2(false);
	Ball ball;

	while(!WindowShouldClose()) {
		Scene::Logic(p1, p2, ball, gamestate);
		Scene::Draw(p1, p2, ball, gamestate);
	}
	CloseWindow();
}

