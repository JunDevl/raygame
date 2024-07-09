#include <iostream>
#include <tuple>
#include <math.h>

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
	float border_thickness = 5.0f;
	Color border_color = BLUE;

	void DrawButton() {

		Rectangle border = {rect.x - border_thickness, 
							rect.y - border_thickness, 
							rect.width + border_thickness * 2.0f, 
							rect.height + border_thickness * 2.0f};

		if (border_thickness != 0.0f) DrawRectangleRec(border, border_color);

		DrawRectangleRec(rect, inner_color);

		const Vector2 text_dim = MeasureTextEx(GetFontDefault(), text, font_size, font_size/10.0f);

		switch (text_orientation) {
			case top:
				DrawText(text, (rect.x + (rect.width/2.0f)) - text_dim.x/2.0f, rect.y, font_size, text_color);
				break;
			case top_right:
				DrawText(text, (rect.x + rect.width) - text_dim.x, rect.y, font_size, text_color);
				break;
			case right:
				DrawText(text, (rect.x + rect.width) - text_dim.x, rect.y + (rect.height/2.0f) - (text_dim.y/2.0f), font_size, text_color);
				break;
			case bottom_right:
				DrawText(text, (rect.x + rect.width) - text_dim.x, rect.y + rect.height - text_dim.y, font_size, text_color);
				break;
			case bottom:
				DrawText(text, (rect.x + (rect.width/2.0f)) - text_dim.x/2.0f, rect.y + rect.height - text_dim.y, font_size, text_color);
				break;
			case bottom_left:
				DrawText(text, rect.x, rect.y + rect.height - text_dim.y, font_size, text_color);
				break;
			case left:
				DrawText(text, rect.x, rect.y + (rect.height/2.0f) - (text_dim.y/2.0f), font_size, text_color);
				break;
			case top_left:
				DrawText(text, rect.x, rect.y, font_size, text_color);
				break;
			case center:
				DrawText(text, (rect.x + (rect.width/2.0f)) - (text_dim.x/2.0f), rect.y + (rect.height/2.0f) - (text_dim.y/2.0f), font_size, text_color);
				break;
		}
	}
};

struct Scene::Menu {
	enum Cursor : short {
		playb,
		optionsb,
		quitb
	};
	Cursor cursor = playb;
	Cursor prev_cursor = cursor;

	float buttons_width = Scene::GetWindowWidth() * 0.3f;
	float buttons_height = Scene::GetWindowHeight() * 0.18f;
	float buttons_xpos = (Scene::GetWindowWidth()/2.0f) - (buttons_width/2.0f);
	float buttons_init_ypos = 10.0f;
	float buttons_offset = Scene::GetWindowHeight() * 0.25f;

	Color buttons_color = WHITE;
	Color selected_button_color = BLUE;
	Color text_color = BLACK;
	Color selected_text_color = BLUE;

	Button play_btn = {{buttons_xpos, buttons_init_ypos, buttons_width, buttons_height}, buttons_color, "Play Game"};
	Button options_btn = {{buttons_xpos, play_btn.rect.y + buttons_offset, buttons_width, buttons_height}, buttons_color, "Options"};
	Button quit_btn = {{buttons_xpos, options_btn.rect.y + buttons_offset, buttons_width, buttons_height}, buttons_color, "Quit Game"};

	void UpdateSelection() {
		prev_cursor = cursor;

		if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) 
			cursor = cursor == playb ? quitb : (Cursor)(cursor - 1);
                
		if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) 
			cursor = cursor == quitb ? playb : (Cursor)(cursor + 1);

		const int mousex = GetMouseX();
		const int mousey = GetMouseY();

		if ((mousex >= play_btn.rect.x && mousey >= play_btn.rect.y) && 
			(mousex <= play_btn.rect.x + play_btn.rect.width && mousey <= play_btn.rect.y + play_btn.rect.height))
			cursor = playb;

		if ((mousex >= options_btn.rect.x && mousey >= options_btn.rect.y) && 
			(mousex <= options_btn.rect.x + options_btn.rect.width && mousey <= options_btn.rect.y + options_btn.rect.height))
			cursor = optionsb;

		if ((mousex >= quit_btn.rect.x && mousey >= quit_btn.rect.y) && 
			(mousex <= quit_btn.rect.x + quit_btn.rect.width && mousey <= quit_btn.rect.y + quit_btn.rect.height))
			cursor = quitb;

	}

	void RenderButtons() {
		switch (prev_cursor) {
			case playb:
				play_btn.border_color = buttons_color;
				play_btn.text_color = text_color;
				break;
			case optionsb:
				options_btn.border_color = buttons_color;
				options_btn.text_color = text_color;
				break;
			case quitb:
				quit_btn.border_color = buttons_color;
				quit_btn.text_color = text_color;
				break;
		}
		switch (cursor) {
			case playb:
				play_btn.border_color = selected_button_color;
				play_btn.text_color = selected_text_color;
				break;
			case optionsb:
				options_btn.border_color = selected_button_color;
				options_btn.text_color = selected_text_color;
				break;
			case quitb:
				quit_btn.border_color = selected_button_color;
				quit_btn.text_color = selected_text_color;
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
	// Since i'm planning to do different games, i repeated this switch statement throughout the entire codebase (i feel like i'm doing something utterly disgusting with this approach, but it works so idfc)
	if (in_game == false) {
		switch(gamestate) {
			case Scene::Gamestate::ponggame:
				p1 = new Paddle(Paddle::left, 255, false);
				p2 = new Paddle(Paddle::right, 255, false);
				ball = new Ball(355, 6.0f);

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
			Paddle *base_p1 = dynamic_cast<Paddle*>(p1);
			Paddle *base_p2 = dynamic_cast<Paddle*>(p2);
			Ball* base_ball = dynamic_cast<Ball*>(ball);

			base_ball->CheckCollision(base_p1);
			base_ball->CheckCollision(base_p2);

			Vector2 next_pos = base_ball->GetNextPosition();

			if (base_ball->GetY() + next_pos.y * GetFrameTime() <= 0.0f || base_ball->GetY() + next_pos.y * GetFrameTime() >= Scene::GetWindowHeight()) 
				base_ball->SetAngle(-base_ball->GetAngle());

			base_ball->IncrementX(next_pos.x * GetFrameTime(), &gamestate);
			base_ball->IncrementY(next_pos.y * GetFrameTime(), &gamestate);

			if (base_ball->GetX() - base_ball->radius <= 0) {
				base_p2->score++;
				base_ball->ResetPosition(base_p2->side);
			}
			if (base_ball->GetX() + base_ball->radius >= Scene::GetWindowWidth()) {
				base_p1->score++;
				base_ball->ResetPosition(base_p1->side);
			}

			break;
	}
}

void Scene::HandleInput() {
    switch (gamestate) {
        case Scene::Gamestate::mainmenu:
            if ((IsKeyPressed(KEY_ENTER) || (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && 
				GetMouseX() >= menu_instance->play_btn.rect.x && GetMouseX() <= menu_instance->play_btn.rect.x + menu_instance->play_btn.rect.width &&
				GetMouseY() >= menu_instance->play_btn.rect.y && GetMouseY() <= menu_instance->play_btn.rect.y + menu_instance->play_btn.rect.height)) &&
				menu_instance->cursor == Scene::Menu::Cursor::playb && p1 == nullptr) 
			{
				gamestate = Scene::Gamestate::ponggame;
				InitGame();
			}

			menu_instance->UpdateSelection();

            break;
        case Scene::Gamestate::pausemenu:
            break;
        case Scene::Gamestate::ponggame:

			Paddle *base_p1 = dynamic_cast<Paddle*>(p1);
			Paddle *base_p2 = dynamic_cast<Paddle*>(p2);
    
            if ((IsKeyDown(KEY_W) && !IsKeyDown(KEY_S)) && base_p1->GetY() >= 0.0f) 
				base_p1->IncrementY(-(base_p1->GetVelocity() * GetFrameTime()), &gamestate);
            if ((IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) && base_p1->GetY() + base_p1->GetHeight() <= *window_height) 
                base_p1->IncrementY(base_p1->GetVelocity() * GetFrameTime(), &gamestate);

            if ((IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN)) && base_p2->GetY() >= 0.0f) 
                base_p2->IncrementY(-(base_p2->GetVelocity() * GetFrameTime()), &gamestate);
            if ((IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP)) && base_p2->GetY() + base_p2->GetHeight() <= *window_height) 
                base_p2->IncrementY(base_p2->GetVelocity() * GetFrameTime(), &gamestate);
            
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
			Ball* base_ball = dynamic_cast<Ball*>(ball);

			DrawRectangle(base_p1->GetX(), base_p1->GetY(), base_p1->GetWidth(), base_p1->GetHeight(), WHITE);
			DrawRectangle(base_p2->GetX(), base_p2->GetY(), base_p2->GetWidth(), base_p2->GetHeight(), WHITE);

			DrawCircle(base_ball->GetX(), base_ball->GetY(), base_ball->radius, WHITE);

			DrawText(std::to_string(base_p1->score).c_str(), 0, 20, 20, BLACK);
			DrawText(std::to_string(base_p2->score).c_str(), Scene::GetWindowWidth() - 40, 20, 20, BLACK);
			//DrawFPS(25, 10);

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
    return Scene::window_width != nullptr ? *Scene::window_width : 0.0f;
}

float Scene::GetWindowHeight() {
    return Scene::window_height != nullptr ? *Scene::window_height : 0.0f;
}