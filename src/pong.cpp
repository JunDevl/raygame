#include "pong.h"
#include "general.h"

float Entity::GetX() {
	return xpos;
}

float Entity::GetY() {
	return ypos;
}

void Entity::SetX(float value) {
	xpos = value;
}

void Entity::SetY(float value) {
	ypos = value;
}

Paddle::Paddle(int side, int speed, bool isbot) : side(side), 
												  is_bot(isbot), 
												  width(Scene::GetWindowWidth() * 0.01), 
												  height(Scene::GetWindowHeight() / 6) 
												  {

	e_speed = speed;

	xpos = side == left_side ? Scene::GetWindowWidth() * 0.01 : Scene::GetWindowWidth() * 0.98;
	ypos = (Scene::GetWindowHeight()/2) - (height/2);

};

float Paddle::GetWidth() {
	return width;
}

float Paddle::GetHeight() {
	return height;
}

void Paddle::SetWidth(float value) {
	width = value;
}

void Paddle::SetHeight(float value) {
	height = value;
}

int Paddle::GetSpeed() {
	return e_speed;
}