#include"sfml.h"
#include "Ball.h"
#include "Paddle.h"
#include"Item.h"
#include"Brick.h"
#include"HardBrick.h"
#include<ctime>
#include<cstdlib>

using namespace sf;

//functions
void Start();
void Update();
void RenderFrame();
void SettingText();

//variables
float x = 0;
float y = 0;
float xx = 0;
float yy = 0;
RenderWindow window;
static const int width = 800;
static const int height = 800;
static const int borderSize = 12;
Font font;
Ball ball1;
Paddle playerPaddle;
Brick brick;
Item pene;
Item longer;
int hp;
Text tScore;
Text tHp;
Text life;
Text GGInfo;
Text tscore;
bool reset;
bool isPlayed = false;
bool isPlayed2 = false;
bool added=false;
Sound sound;
Sound BGM;
SoundBuffer buf1;
SoundBuffer buf2;


int main()
{
	Start();
	Update();
	return 0;
}


void Start() {
	font.loadFromFile("verdana.ttf");
	buf1.loadFromFile("winLevel.wav");
	buf2.loadFromFile("bgm.wav");

	playerPaddle.SetPaddle();
	playerPaddle.ResetSpeed();

	ball1.SetBall(playerPaddle.paddle.getPosition().x, 764);
	ball1.vel = Vector2f(400, 400);
	ball1.speed = sqrt(ball1.vel.x*ball1.vel.x + ball1.vel.y*ball1.vel.y);
	ball1.level = 0;

	brick.SetDimensions(7, 5);
	brick.r.left = borderSize + 5;
	brick.r.top = borderSize + 5;
	brick.r.width = width - 2 * borderSize - 10;
	brick.r.height = 250;
	brick.CreateBricks();

	pene.SetItem(1);
	longer.SetItem(2);

	hp = 3;
	brick.gameOver = false;
	reset = true;
}


void Update() {
	window.create(VideoMode(width, height), "BreakOut");
	Clock clock;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

		}
		SettingText();
		float dt = clock.restart().asSeconds();


		if (!brick.gameOver) {

			if (BGM.getStatus() != SoundSource::Playing) {
				BGM.setBuffer(buf2);
				BGM.setVolume(40);
				BGM.play();
			}

			if (ball1.reset && !reset) {
				reset = true;
				hp--;
				ball1.ball.setFillColor(Color::White);
				playerPaddle.paddle.setSize(Vector2f(100, 10));
				playerPaddle.paddle.setOrigin(50, 5);
				pene.penetrate = false;
			}
			if (Keyboard::isKeyPressed(Keyboard::Space) && ball1.reset) {
				ball1.reset = false;
				reset = false;
				ball1.vel = Vector2f(-400, -400);
			}

			ball1.UpdateState(dt, playerPaddle);
			playerPaddle.UpdateState(dt, ball1.ball);
			brick.UpdateState(ball1,pene,longer);
			pene.UpdateStatus(dt,playerPaddle,ball1,1);
			longer.UpdateStatus(dt, playerPaddle, ball1,2);
			added = false;
		}

		if (brick.GameReset(ball1)) {
			sound.setBuffer(buf1);
			sound.play();

			ball1.reset = true;
			playerPaddle.paddle.setSize(Vector2f(100, 10));
			playerPaddle.paddle.setOrigin(50, 5);
			
			pene.penetrate = false;
			pene.trigger = false;
			longer.trigger = false;
			pene.uped = false;
			longer.uped = false;

			reset = true;
			added = true;
			if (added) {
				ball1.level++;
				added = false;
			}
		}


		if (hp < 0)
			brick.gameOver = true;

		if (brick.gameOver) {

			for (int i = 0; i < brick.rows - 1; i++)
				for (int j = 0; j < brick.columns; j++) {
					brick.bricks->at(i + j * brick.rows).shape.setFillColor(Color::White);
					brick.bricks->at(i + j * brick.rows).hp = 2;
				}

			ball1.vel = Vector2f(0, 0);
		
			if (Keyboard::isKeyPressed(Keyboard::R)) {
				brick.score = 0;
				ball1.ball.setFillColor(Color::White);
				ball1.reset = true;
				reset = false;
				brick.gameOver = false;

				hp = 4;
				ball1.level = 0;
				pene.trigger = false;
				longer.trigger = false;
				pene.uped = false;
				longer.uped = false;

			}
		}

		RenderFrame();
		//Score();
		window.display();
	}
}


void RenderFrame()
{
	window.clear();
	for (int i = 0; i < brick.rows; i++)
		for (int j = 0; j < brick.columns; j++)
		{
			window.draw(brick.bricks->at(i + j * brick.rows).shape);
		}

	window.draw(ball1.ball);
	window.draw(playerPaddle.paddle);
	window.draw(tScore);
	window.draw(tHp);
	window.draw(life);
	window.draw(tscore);
	if(pene.trigger&&!pene.uped)window.draw(pene.item);
	if(longer.trigger&&!longer.uped)window.draw(longer.item);
	if (brick.gameOver)window.draw(GGInfo);
}


void SettingText()
{
	tScore.setFont(font);
	tScore.setPosition(170, 0);
	tScore.setString(std::to_string(brick.score));
	tScore.setCharacterSize(50);
	tScore.setStyle(sf::Text::Bold);
	tScore.setFillColor(sf::Color::White);

	tHp.setFont(font);
	tHp.setPosition(750, 0);
	tHp.setCharacterSize(50);
	if(hp>=0)
	    tHp.setString(std::to_string(hp));
	if(hp<0)
		tHp.setString("0");
	tHp.setStyle(sf::Text::Bold);
	tHp.setFillColor(sf::Color::White);

	life.setFont(font);
	life.setPosition(650, 0);
	life.setString("life:");
	life.setCharacterSize(50);
	life.setStyle(sf::Text::Bold);
	life.setFillColor(sf::Color::White);

	tscore.setFont(font);
	tscore.setPosition(0, 0);
	tscore.setString("score:");
	tscore.setCharacterSize(50);
	tscore.setStyle(sf::Text::Bold);
	tscore.setFillColor(sf::Color::White);

	GGInfo.setFont(font);
	GGInfo.setPosition(250, 400);
	GGInfo.setString("Game Over");
	GGInfo.setCharacterSize(50);
	GGInfo.setStyle(sf::Text::Bold);
	GGInfo.setFillColor(sf::Color::White);
}






