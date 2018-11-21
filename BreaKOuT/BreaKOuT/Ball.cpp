#include "Ball.h"

using namespace sf;


Ball::Ball()
{
	isColled = false;
	reset = true;
	level = 0;
	buf1.loadFromFile("SFX1.wav");
	buf2.loadFromFile("SFX2.wav");
	buf3.loadFromFile("loseLife.wav");
}


Ball::~Ball()
{
}


void Ball::SetBall(float x, float y) {
	ball.setRadius(10);
	ball.setOrigin(10, 10);
	ball.setFillColor(Color::White);
	ball.setPosition(x, y);
}


void Ball::UpdateState(float dt,Paddle &p)
{
	pos = ball.getPosition();
	pos += vel * dt;

	if (pos.x > 800 && vel.x > 0) {
		vel.x = -vel.x;
		sound.setBuffer(buf1);
		sound.play();
	}
	if (pos.x< 0 && vel.x < 0) {
		vel.x = -vel.x;
		sound.setBuffer(buf1);
		sound.play();
	}
	if (pos.y < 0 && vel.y < 0) {
		vel.y = -vel.y;
		sound.setBuffer(buf1);
		sound.play();
	}
	if (pos.y >800 && vel.y > 0) {
		reset = true;
		sound.setBuffer(buf3);
		sound.play();
	}


	if (reset) {
		vel=Vector2f(0,0);
		pos = Vector2f(p.paddle.getPosition().x,764);

	}

	if ( ball.getGlobalBounds().intersects(p.r)&& !isColled) {
		isColled = true;
		vel = pos - p.paddle.getPosition();
		vel /= sqrt(vel.x*vel.x + vel.y*vel.y);
		vel *= speed;
		vel *= (1 + level / 20);
		sound.setBuffer(buf2);
		sound.play();
	}


	isColled = false;
	ball.setPosition(pos);
}
