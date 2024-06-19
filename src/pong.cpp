#include "pong.h"
#include "general.h"

float Entity::GetX() {
	return xpos;
}

float Entity::GetY() {
	return ypos;
}

void Entity::SetX(float x) {
	if (x >= 0 && x < Scene::GetWindowWidth()) {
		xpos = x;
	}
	return;
}

void Entity::SetY(float y) {
	if (y >= 0 && y < Scene::GetWindowHeight()) {
		ypos = y;
	}
	return;
}

int Entity::GetSpeed() {
	return e_speed;
}

Paddle::Paddle(Side side, int speed, bool isbot) : side(side), 
												  is_bot(isbot), 
												  width(Scene::GetWindowWidth() * 0.01), 
												  height(Scene::GetWindowHeight() * 0.23) 
												  {

	e_speed = speed;

	xpos = side == left ? Scene::GetWindowWidth() * 0.01 : Scene::GetWindowWidth() * 0.98;
	ypos = (Scene::GetWindowHeight()/2) - (height/2);

};

float Paddle::GetWidth() {
	return width;
}

float Paddle::GetHeight() {
	return height;
}

void Paddle::SetWidth(float new_width) {
	width = new_width;
}

void Paddle::SetHeight(float new_height) {
	height = new_height;
}