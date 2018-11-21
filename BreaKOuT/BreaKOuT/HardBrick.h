#pragma once
#include "Brick.h"

class HardBrick :
	public Brick
{
public:
	HardBrick();
	~HardBrick();

	virtual void CreateBrick() {
		tex.loadFromFile("hardbrick.png");
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < columns; j++)
			{
				bricks->at(i + j * rows).shape.setSize(Vector2f(cellSize().x - 30, cellSize().y - 30));
				bricks->at(i + j * rows).shape.setTexture(&tex);
				bricks->at(i + j * rows).shape.setPosition(r.left + j * cellSize().x, r.top + i * cellSize().y+200);
			}
	}


private:
	int hp;
	Texture tex;
};

