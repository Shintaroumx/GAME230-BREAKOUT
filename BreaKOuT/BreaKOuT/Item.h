#pragma once
#include"sfml.h"
#include"Paddle.h"
#include"Ball.h"

using namespace sf;

class Item
{
public:
	Item();
	~Item();

	void SetItem(int a);
	void UpdateStatus(float dt, Paddle &p, Ball &b,int a);
	CircleShape item;
	FloatRect r;
	bool trigger;
	bool penetrate;
	bool uped;

private:
	Texture tex;
	SoundBuffer buf1;
	SoundBuffer buf2;
	sf::Sound sound;
};

