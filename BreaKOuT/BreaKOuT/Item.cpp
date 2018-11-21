#include "Item.h"

using namespace sf;

Item::Item()
{
	trigger = false;
	penetrate = false;
	buf1.loadFromFile("SFX4.wav");
	buf2.loadFromFile("SFX3.wav");
}


Item::~Item()
{
}

void Item::SetItem(int a)
{
	tex.loadFromFile("item.png");
	item.setRadius(20);
	item.setTexture(&tex);
	if (a == 1) {
		item.setPosition(200, 200);
		item.setFillColor(Color::Red);
	}
	if (a == 2) {
		item.setPosition(600, 300);
		item.setFillColor(Color::Green);
	}
}

void Item::UpdateStatus(float dt, Paddle &p, Ball &b,int a)
{
	r = item.getGlobalBounds();
	if (trigger&&!uped) {
		Vector2f pos = item.getPosition();
		pos.y += 200 * dt;
		item.setPosition(pos);
		if (a==2) {
			if (r.intersects(p.paddle.getGlobalBounds())) {
				sound.setBuffer(buf1);
				sound.play();
				p.paddle.setSize(Vector2f(200, 10));
				p.paddle.setOrigin(100, 5);
				trigger = false;
				uped = true;
				item.setPosition(600, 300);
			}
		}
		if (a==1) {
			if (r.intersects(p.paddle.getGlobalBounds())) {
				sound.setBuffer(buf2);
				sound.play();
				b.ball.setFillColor(Color::Red);
				penetrate = true;
				trigger = false;
				uped = true;
				item.setPosition(100, 200);
			}
		}
	}
}

