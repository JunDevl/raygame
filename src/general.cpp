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
	TextOrientation text_orientation = center;
	Color text_color = BLACK;
	float border_thickness = 5;
	Color border_color = BLUE;

	void DrawButton() {

		Rectangle border = {rect.x - border_thickness, 
							rect.y - border_thickness, 
							rect.width + border_thickness * 2, 
							rect.height + border_thickness * 2};

		if (border_thickness != 0) DrawRectangleRec(border, border_color);

		DrawRectangleRec(rect, inner_color);

		const Vector2 text_dim = MeasureTextEx(GetFontDefault(), text, font_size, font_size/10);

		switch (text_orientation) {
			case top:
				DrawText(text, (rect.x + (rect.width/2)) - text_dim.x/2, rect.y, font_size, text_color);
				break;
			case top_right:
				DrawText(text, (rect.x + rect.width) - text_dim.x, rect.y, font_size, text_color);
				break;
			case right:
				DrawText(text, (rect.x + rect.width) - text_dim.x, rect.y + (rect.height/2) - (text_dim.y/2), font_size, text_color);
				break;
			case bottom_right:
				DrawText(text, (rect.x + rect.width) - text_dim.x, rect.y + rect.height - text_dim.y, font_size, text_color);
				break;
			case bottom:
				DrawText(text, (rect.x + (rect.width/2)) - text_dim.x/2, rect.y + rect.height - text_dim.y, font_size, text_color);
				break;
			case bottom_left:
				DrawText(text, rect.x, rect.y + rect.height - text_dim.y, font_size, text_color);
				break;
			case left:
				DrawText(text, rect.x, rect.y + (rect.height/2) - (text_dim.y/2), font_size, text_color);
				break;
			case top_left:
				DrawText(text, rect.x, rect.y, font_size, text_color);
				break;
			case center:
				DrawText(text, (rect.x + (rect.width/2)) - (text_dim.x/2), rect.y + (rect.height/2) - (text_dim.y/2), font_size, text_color);
				break;
		}
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

	void UpdateSelection() {
		if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) 
			cursor = cursor == 0 ? 2 : cursor - 1;
                
		if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) 
			cursor = cursor == 2 ? 0 : cursor + 1;

		const int mousex = GetMouseX();
		const int mousey = GetMouseY();

		if ((mousex >= play_btn.rect.x && mousey >= play_btn.rect.y) && 
			(mousex <= play_btn.rect.x + play_btn.rect.width && mousey <= play_btn.rect.y + play_btn.rect.height))
			cursor = 0;

		if ((mousex >= options_btn.rect.x && mousey >= options_btn.rect.y) && 
			(mousex <= options_btn.rect.x + options_btn.rect.width && mousey <= options_btn.rect.y + options_btn.rect.height))
			cursor = 1;

		if ((mousex >= quit_btn.rect.x && mousey >= quit_btn.rect.y) && 
			(mousex <= quit_btn.rect.x + quit_btn.rect.width && mousey <= quit_btn.rect.y + quit_btn.rect.height))
			cursor = 2;

	}

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
}

Scene::~Scene() {
	delete menu_instance, p1, p2, p3, p4, ball;
}

void Scene::InitGame() {
	// Since i'm planning to do different games, there's this switch statement to initialize every game's entities to its own defined class (i feel like i'm doing something utterly disgusting, sorry :<)
	if (in_game == false) {
		switch(gamestate) {
			case Scene::Gamestate::ponggame:
				p1 = new Paddle(Paddle::left, 255, false);
				p2 = new Paddle(Paddle::right, 255, false);
				ball = new Ball();

				in_game = true;
				
				break;
		}
	}
	return;
}

void Scene::Logic() {
	HandleInput();

	switch (Scene::gamestate) {
		case Scene::Gamestate::ponggame:
			/* -- to-do: calculate sin and cos of ball and collisions -- */
			break;
	}
}

void Scene::HandleInput() {
    switch (gamestate) {
        case Scene::Gamestate::mainmenu:
            if ((IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) && menu_instance->cursor == 0 && p1 == nullptr) {
				gamestate = Scene::Gamestate::ponggame;
				InitGame();
			}

			menu_instance->UpdateSelection();

			std::cout << menu_instance->cursor << std::endl;

            break;
        case Scene::Gamestate::pausemenu:
            break;
        case Scene::Gamestate::ponggame:

			Paddle* base_p1 = dynamic_cast<Paddle*>(p1);
			Paddle* base_p2 = dynamic_cast<Paddle*>(p2);
    
            if ((IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) && base_p1->GetY() >= 0) 
				base_p1->SetY(base_p1->GetY() - base_p1->GetSpeed() * GetFrameTime());
            if ((IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) && base_p1->GetY() + base_p1->GetHeight() <= *window_height) 
                base_p1->SetY(base_p1->GetY() + base_p1->GetSpeed() * GetFrameTime());

            if ((IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) && base_p2->GetY() >= 0) 
                base_p2->SetY(base_p2->GetY() - base_p2->GetSpeed() * GetFrameTime());
            if ((IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)) && base_p2->GetY() + base_p2->GetHeight() <= *window_height) 
                base_p2->SetY(base_p2->GetY() + base_p2->GetSpeed() * GetFrameTime());
            
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
		case Scene::Gamestate::ponggame:
			ClearBackground(GRAY);

			Paddle* base_p1 = dynamic_cast<Paddle*>(p1);
			Paddle* base_p2 = dynamic_cast<Paddle*>(p2);

			DrawRectangle(base_p1->GetX(), base_p1->GetY(), base_p1->GetWidth(), base_p1->GetHeight(), WHITE);
			DrawRectangle(base_p2->GetX(), base_p2->GetY(), base_p2->GetWidth(), base_p2->GetHeight(), WHITE);

			DrawCircle(GetWindowWidth()/2, GetWindowHeight()/2, 10, WHITE);

			DrawFPS(25, 10);

			EndDrawing();
			break;
	}
}

void Scene::SetWindowWidth(float *width) {
    Scene::window_width = width;
}

void Scene::SetWindowHeight(float *height) {
    Scene::window_height = height;
}

float Scene::GetWindowWidth() {
    return Scene::window_width != nullptr ? *Scene::window_width : 0;
}

float Scene::GetWindowHeight() {
    return Scene::window_height != nullptr ? *Scene::window_height : 0;
}