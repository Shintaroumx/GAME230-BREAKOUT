#pragma once
#include"sfml.h"
#include"Ball.h"
#include"Item.h"

#define PI   3.14159265358979323846

using namespace sf;

class Brick
{
public:
	Brick();
	~Brick();

	void CreateBricks();
	void SetDimensions(unsigned int col, unsigned int row); 
	void UpdateState(Ball &ball, Item &item, Item &longer);
	bool Collide(CircleShape & ball, Vector2f & vel,bool pene);
    Vector2f cellSize(){ return Vector2f(r.width / columns, r.height / rows); }
	RectangleShape shape;
	FloatRect r;
	std::vector<Brick> * bricks;
	unsigned int rows;
	unsigned int columns;
	int score;
	bool GameReset(Ball &b);
	bool gameOver;
	int hp;

private:
	SoundBuffer buf1;
	SoundBuffer buf2;
	sf::Sound sound;
	Texture tex;
	Texture tex2;
	Texture tex3;
};
