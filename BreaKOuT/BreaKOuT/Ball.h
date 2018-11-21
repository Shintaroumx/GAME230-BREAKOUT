#pragma once
#include"sfml.h"
#include"Paddle.h"
#include<cmath>

class Ball
{
public:
	Ball();
	~Ball();

	void SetBall(float x, float y);
	void UpdateState(float dt,Paddle &p);
	sf::CircleShape ball;
	sf::Vector2f vel;
	sf::Vector2f pos;
	float speed;
	float level;
	bool reset;

	sf::SoundBuffer buf1;
	sf::SoundBuffer buf2;
	sf::SoundBuffer buf3;
	sf::Sound sound;
	bool isColled;

private:

};


