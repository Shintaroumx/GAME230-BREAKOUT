#include "Brick.h"

using namespace sf;

bool intersects(const CircleShape & cir, const RectangleShape & rect)
{
	FloatRect r1 = cir.getGlobalBounds();
	FloatRect r2 = rect.getGlobalBounds();
	return r1.intersects(r2);
}

Brick::Brick()
{
	rows = 0;
	columns = 0;
	bricks = NULL;
	hp = 2;
	score = 0;
	gameOver = false;
	buf1.loadFromFile("break.wav");
	buf2.loadFromFile("collide.wav");
}


Brick::~Brick()
{
	if (bricks != NULL)
		delete bricks;
}



bool Brick::Collide(CircleShape & ball, Vector2f & vel,bool pene)
{
	// ball collides brick
	if (intersects(ball, this->shape))
	{
		r = this->shape.getGlobalBounds();
		FloatRect b = ball.getGlobalBounds();

		Vector2f o = Vector2f(r.left + r.width / 2, r.top + r.height / 2);
		Vector2f om = Vector2f(b.left + b.width / 2 - o.x, b.top + b.height / 2 - o.y);
		om.x /= r.width;
		om.y /= r.height;

		float angle = atan2(om.y, om.x);
		if (angle >= PI / 4 && angle <= 3 * PI / 4) //bottom
		{
			if (!pene) {
				vel.y = abs(vel.y);
				float u = r.top + r.height - b.top;
				ball.move(0, 2 * u);
			}
			return true;
		}
		if (angle <= -PI / 4 && angle >= -3 * PI / 4) //top
		{
			if (!pene) {
				vel.y = -abs(vel.y);
				float u = b.top + b.height - r.top;
				ball.move(0, -2 * u);
			}
			return true;
		}
		if (angle <= -3 * PI / 4) //left
		{
			if (!pene) {
				vel.x = -abs(vel.x);
				float u = b.left + b.width - r.left;
				ball.move(-2 * u, 0);
			}
			return true;
		}
		if (abs(angle) <= PI / 4) //right
		{
			if (!pene) {
				vel.x = abs(vel.x);
				float u = r.left + r.width - b.left;
				ball.move(2 * u, 0);
			}
			return true;
		}
	}
	return false;
}


bool Brick::GameReset(Ball &b)
{
	for (int i = 0; i < rows - 1; i++)
		for (int j = 0; j < columns; j++)
			if (bricks->at(i + j * rows).hp > 0)
				return false;

	for (int i = 0; i < rows - 1; i++)
		for (int j = 0; j < columns; j++) {
			bricks->at(i + j * rows).shape.setFillColor(Color::White);
			bricks->at(i + j * rows).hp = 2;
		}
	b.level++;
	return true;
}


void Brick::CreateBricks()
{
	tex.loadFromFile("brick.png");
	tex2.loadFromFile("hardbrick.png");
	tex3.loadFromFile("metalbrick.png");
	for (int i = 0; i < rows-3; i++)
		for (int j = 0; j < columns; j++)
		{
			bricks->at(i + j * rows).shape.setSize(Vector2f(cellSize().x - 30, cellSize().y - 30));
			bricks->at(i + j * rows).shape.setTexture(&tex);
			bricks->at(i + j * rows).shape.setPosition(r.left + j * cellSize().x, r.top + i * cellSize().y+100);
		}
	for (int i = rows-3; i < rows - 1; i++)
		for (int j = 0; j < columns; j++)
		{
			bricks->at(i + j * rows).shape.setSize(Vector2f(cellSize().x - 30, cellSize().y - 30));
			bricks->at(i + j * rows).shape.setTexture(&tex2);
			bricks->at(i + j * rows).shape.setPosition(r.left + j * cellSize().x, r.top + i * cellSize().y+100);
		}
	for (int i = rows - 1; i < rows ; i++)
		for (int j = 0; j < columns; j=j+2)
		{
			bricks->at(i + j * rows).shape.setSize(Vector2f(cellSize().x - 30, cellSize().y - 30));
			bricks->at(i + j * rows).shape.setTexture(&tex3);
			bricks->at(i + j * rows).shape.setPosition(r.left + j * cellSize().x, r.top + i * cellSize().y+100);
		}
}


void Brick::SetDimensions(unsigned int col, unsigned int row)
{
	rows = row;
	columns = col;
	if (bricks != NULL)
		delete bricks;

	bricks = new std::vector<Brick>(rows*columns);
	CreateBricks();
}


void Brick::UpdateState(Ball &ball,Item &pene,Item &longer)
{
	for (int i = 0; i < rows - 3; i++)
		for (int j = 0; j < columns; j++)
		{
			if (bricks->at(i + j * rows).hp <= 0) {
				bricks->at(i + j * rows).shape.setFillColor(Color::Transparent);
				continue;
			}
			if (bricks->at(i + j * rows).Collide(ball.ball, ball.vel, pene.penetrate))
			{
				sound.setBuffer(buf2);
				sound.play();
				bricks->at(i + j * rows).hp-=2;
				if (bricks->at(i + j * rows).hp == 0) {
					sound.setBuffer(buf1);
					sound.play();
					score += 50;
				}
			}
		}
	for (int i = rows - 3; i < rows - 1; i++)
		for (int j = 0; j < columns; j++)
		{
			if (bricks->at(i + j * rows).hp <= 0) {
				bricks->at(i + j * rows).shape.setFillColor(Color::Transparent);
				continue;
			}
			if (bricks->at(i + j * rows).Collide(ball.ball, ball.vel, pene.penetrate))
			{
				sound.setBuffer(buf2);
				sound.play();
				bricks->at(i + j * rows).hp--;
				bricks->at(i + j * rows).shape.setFillColor(Color::Blue);
				if (bricks->at(i + j * rows).hp == 0) {
					sound.setBuffer(buf1);
					sound.play();
					score += 100;
				}
			}
		}
	for (int i = rows - 1; i < rows; i++)
		for (int j = 0; j < columns; j +=2)
		{
			if (bricks->at(i + j * rows).Collide(ball.ball, ball.vel, false))
			{
				sound.setBuffer(buf2);
				sound.play();
			}
		}

	if (bricks->at(4 + 1 * 4).hp == 0) {
		pene.trigger = true;
	}
	if (bricks->at(4 + 6 * 4).hp == 0) {
		longer.trigger = true;
	}
}



