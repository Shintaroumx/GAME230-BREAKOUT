#include "Paddle.h"

using namespace sf;

Paddle::Paddle()
{
}


Paddle::~Paddle()
{
}


void Paddle::SetPaddle() {
	tex.loadFromFile("paddle.png");
	paddle.setSize(Vector2f(100, 10));
	paddle.setOrigin(50, 5);
	paddle.setTexture(&tex);
	paddle.setPosition(400, 780);
}


void Paddle::ResetSpeed() {
	speed = 550;
}


void Paddle::UpdateState(float dt, CircleShape b)
{
	Vector2f pos = paddle.getPosition();
	r.left = pos.x - 50;
	r.top = pos.y - 5;
	r.width = paddle.getSize().x;
	r.height = paddle.getSize().y;

	if (Keyboard::isKeyPressed(Keyboard::A) && pos.x > 50)
		pos.x -= speed * dt;
	if (Keyboard::isKeyPressed(Keyboard::D) && pos.x < 750)
		pos.x += speed * dt;

	paddle.setPosition(pos);
}

