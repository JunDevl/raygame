#include <random>
#include <time.h>
#include <math.h>
#include "pong.h"
#include "general.h"

float Entity::GetX() {
	return position.x;
}

float Entity::GetY() {
	return position.y;
}

void Entity::IncrementX(float x, void *gamestate) {
	switch (*((Scene::Gamestate*)gamestate)) {
		case Scene::Gamestate::ponggame:
			if ((x + position.x) >= 0.0f && (x + position.x) < Scene::GetWindowWidth()) position.x += x;
			break;
	}
	
	return;
}

void Entity::IncrementY(float y, void *gamestate) {
	switch (*((Scene::Gamestate*)gamestate)) {
		case Scene::Gamestate::ponggame:
			if ((y + position.y) >= 0.0f && (y + position.y) < Scene::GetWindowHeight()) position.y += y;
			break;
	}
	return;
}

int Entity::GetVelocity() {
	return e_velocity;
}

Paddle::Paddle(Side side, int velocity, bool isbot) : side(side), 
												   is_bot(isbot), 
												   score(0),
												   width(Scene::GetWindowWidth() * 0.01f), 
												   height(Scene::GetWindowHeight() * 0.23f) 
{

	e_velocity = velocity;

	position.x = side == left ? Scene::GetWindowWidth() * 0.01f : Scene::GetWindowWidth() * 0.98f;
	position.y = (Scene::GetWindowHeight()/2.0f) - (height/2.0f);

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

Ball::Ball(int velocity, float ball_radius) : radius(ball_radius) {
	position.x = Scene::GetWindowWidth()/2.0f;
	position.y = Scene::GetWindowHeight()/2.0f;

	srand((unsigned)time(NULL));
	angle = rand() % 360;

	e_velocity = velocity;
}

void Ball::SetAngle(Degree new_angle) {
	if (new_angle < 0.0f) 
		new_angle += 360.0f; 
	else if (new_angle >= 360.0f) 
		new_angle -= 360.0f; 
	
	angle = new_angle;
}

void Ball::ResetPosition(int side) {
	position.x = Scene::GetWindowWidth()/2.0f;
	position.y = Scene::GetWindowHeight()/2.0f;

	srand((unsigned)time(NULL));

	angle = side == Paddle::Side::left ? (rand() % 360) - 180 : rand() % 360;
	
}

Vector2 Ball::GetNextPosition() {
	float radian = angle * PI / 180.0f;
	return {e_velocity * cos(radian), e_velocity * sin(radian)};
}

Degree Ball::GetAngle() {
	return angle;
}

void Ball::CheckCollision(Paddle* player) {
	const Degree BOUNCE_OFFSET = 75;
	if (player->side == Paddle::Side::left && position.x - radius <= player->GetX() + player->GetWidth() && (position.y >= player->GetY() && position.y <= player->GetY() + player->GetHeight())) {

		float rel_intersect_y = (player->GetY()+(player->GetHeight()/2)) - position.y;
		float normal_rel_intersection_y = rel_intersect_y/(player->GetHeight()/2);
		Degree bounce_angle = normal_rel_intersection_y * -BOUNCE_OFFSET;

		SetAngle(bounce_angle);
	} 
	if (player->side == Paddle::Side::right && position.x + radius >= player->GetX() && (position.y >= player->GetY() && position.y <= player->GetY() + player->GetHeight())) {

		float rel_intersect_y = (player->GetY()+(player->GetHeight()/2)) - position.y;
		float normal_rel_intersection_y = rel_intersect_y/(player->GetHeight()/2);
		Degree bounce_angle = normal_rel_intersection_y * BOUNCE_OFFSET;

		SetAngle(180 + bounce_angle);
	}
}