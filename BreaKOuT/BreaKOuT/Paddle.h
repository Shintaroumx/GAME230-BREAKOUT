#pragma once
#include"sfml.h"

class Paddle
{
public:
	Paddle();
	~Paddle();

	void SetPaddle();
	void ResetSpeed();
	void UpdateState(float dt, sf::CircleShape b);
	sf::RectangleShape paddle;
	sf::FloatRect r;
	sf::Vector2f vel;
	int speed;

private:
	sf::Texture tex;
};

