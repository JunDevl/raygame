#include <iostream>
#include <tuple>

#include <raylib.h>

#include "general.h"

struct Button {
	enum TextOrientation {
		top, top_right, right, bottom_right, bottom, bottom_left, left, top_left, center
	};
	Rectangle rect;
	Color inner_color;
	const char* text;
	const char* text_font = "Calibri";
	int font_size = 20;
	TextOrientation text_orientation = top_left;
	Color text_color = BLACK;
	float border_thickness = 5;
	Color border_color = BLUE;

	void DrawButton() {
		Rectangle border = {rect.x - border_thickness, rect.y - border_thickness, rect.width + border_thickness * 2, rect.height + border_thickness * 2};
		if (border_thickness != 0) DrawRectangleRec(border, border_color);
		DrawRectangleRec(rect, inner_color);
		DrawText(text, rect.x + rect.width * 0.2, rect.y, font_size, text_color);
	}
};

struct Scene::Menu {
	unsigned short cursor = 0;

	float buttons_width = Scene::GetWindowWidth() * 0.3;
	float buttons_height = Scene::GetWindowHeight() * 0.18;
	float buttons_xpos = (Scene::GetWindowWidth()/2) - (buttons_width/2);
	float buttons_init_ypos = 10.0f;
	float buttons_offset = Scene::GetWindowHeight() * 0.25;

	Color buttons_color = WHITE;
	Color selected_button_color = YELLOW;

	Button play_btn = {{buttons_xpos, buttons_init_ypos, buttons_width, buttons_height}, buttons_color, "Play Game"};
	Button options_btn = {{buttons_xpos, play_btn.rect.y + buttons_offset, buttons_width, buttons_height}, buttons_color, "Options"};
	Button quit_btn = {{buttons_xpos, options_btn.rect.y + buttons_offset, buttons_width, buttons_height}, buttons_color, "Quit Game"};

	void RenderButtons() {
		switch (cursor) {
			case 0:
				play_btn.border_color = selected_button_color;
				options_btn.border_color = buttons_color;
				quit_btn.border_color = buttons_color;
				break;
			case 1:
				play_btn.border_color = buttons_color;
				options_btn.border_color = selected_button_color;
				quit_btn.border_color = buttons_color;
				break;
			case 2:
				play_btn.border_color = buttons_color;
				options_btn.border_color = buttons_color;
				quit_btn.border_color = selected_button_color;
				break;
		}

		play_btn.DrawButton();
		options_btn.DrawButton();
		quit_btn.DrawButton();
	}
};

Scene::Scene(float &wwidth, float &wheight) {
    Scene::window_width = &wwidth;
    Scene::window_height = &wheight;
    gamestate = Scene::Gamestate::mainmenu;
	menu_instance = new Menu();
	p1 = nullptr, p2 = nullptr;
}

Scene::~Scene() {
	delete menu_instance, p1, p2;
}

void Scene::InitGame() {
	// Since i'm planning to do different games, there's this switch statement to initialize every game's entities to its own defined class (i fell like i'm doing something utterly disgusting, sorry :<)
	switch(Scene::gamestate) {
		case Scene::Gamestate::pong:
			p1 = new Paddle(Paddle::left_side, 255, false);
			p2 = new Paddle(Paddle::right_side, 255, false);
			break;
	}
}

void Scene::Logic() {
	HandleInput();

	switch (Scene::gamestate) {
		case Scene::Gamestate::mainmenu:
			break; // HandleInput will handle everything menu-related
		case Scene::Gamestate::pausemenu:
			break; // HandleInput will handle everything menu-related
		case Scene::Gamestate::pong:
			/* -- to-do: calculate sin and cos of ball and collisions -- */
			break;
	}
}

void Scene::HandleInput() {
    switch (gamestate) {
        case Scene::Gamestate::mainmenu:
            if (IsKeyPressed(KEY_ENTER) && menu_instance->cursor == 0 && p1 == nullptr) {
				gamestate = Scene::Gamestate::pong;
				InitGame();
            }
            if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) 
				menu_instance->cursor = menu_instance->cursor == 0 ? 2 : menu_instance->cursor - 1;
                
            if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) 
				menu_instance->cursor = menu_instance->cursor == 2 ? 0 : menu_instance->cursor + 1;

			std::cout << menu_instance->cursor << std::endl;

            break;
        case Scene::Gamestate::pausemenu:
            break;
        case Scene::Gamestate::pong:
		
            ////////////////
            // GAME INPUT //
			////////////////

            // Workarround to "fix" dragging window problem (to prevent the paddle from going offscreen if you do an input while dragging the window)
            if (p1->GetY() < 0) {
                p1->SetY(0);
            } else if (p2->GetY() < 0) {
                p2->SetY(0);
            }

            if (p1->GetY() + p1->GetHeight() > *window_height) {
                p1->SetY(*window_height - p1->GetHeight());
            } else if (p2->GetY() + p2->GetHeight() > *window_height) {
                p2->SetY(*window_height - p2->GetHeight());
            }

            // Game input logic
            if ((IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) && p1->GetY() >= 0) 
				p1->SetY(p1->GetY() - p1->GetSpeed() * GetFrameTime());
            if ((IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) && p1->GetY() + p1->GetHeight() <= *window_height) 
                p1->SetY(p1->GetY() + p1->GetSpeed() * GetFrameTime());

            if ((IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) && p2->GetY() >= 0) 
                p2->SetY(p2->GetY() - p2->GetSpeed() * GetFrameTime());
            if ((IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)) && p2->GetY() + p2->GetHeight() <= *window_height) 
                p2->SetY(p2->GetY() + p2->GetSpeed() * GetFrameTime());
            
            break;
    }
}

void Scene::Draw() {
	BeginDrawing();

	switch(Scene::gamestate) {
		case Scene::Gamestate::mainmenu:
			menu_instance->RenderButtons();

			EndDrawing();

			if (WindowShouldClose()) CloseWindow();
			break;
		case Scene::Gamestate::pausemenu:
			break;
		case Scene::Gamestate::pong:
			ClearBackground(GRAY);

			DrawRectangle(p1->GetX(), p1->GetY(), p1->GetWidth(), p1->GetHeight(), WHITE);
			DrawRectangle(p2->GetX(), p2->GetY(), p2->GetWidth(), p2->GetHeight(), WHITE);

			DrawCircle(GetWindowWidth()/2, GetWindowHeight()/2, 10, WHITE);

			DrawFPS(25, 10);

			EndDrawing();
			break;
	}
}

void Scene::SetWindowWidth(float &width) {
    Scene::window_width = &width;
}

void Scene::SetWindowHeight(float &height) {
    Scene::window_height = &height;
}

float Scene::GetWindowWidth() {
    return Scene::window_width != nullptr ? *Scene::window_width : 0;
}

float Scene::GetWindowHeight() {
    return Scene::window_height != nullptr ? *Scene::window_height : 0;
}