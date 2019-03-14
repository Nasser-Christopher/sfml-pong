#include <SFML/Graphics.hpp>
#include "GlobalVar.h"
#include "Ball.h"
#include "Paddle.h"


int main()
{
	Ball myBall(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	Paddle myPaddle(50, SCREEN_HEIGHT / 2 - (PADDLEHEIGHT / 2));
	Paddle AIPaddle(SCREEN_WIDTH - 50, SCREEN_HEIGHT / 2 - (PADDLEHEIGHT / 2));

	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "sfml-pong");
	
	SoundBuffer buff;
	buff.loadFromFile("ping.wav");
	Sound pingSound;
	pingSound.setBuffer(buff);

	Music music;
	if (!music.openFromFile("battle.wav"))
		return -1;

	Text hud;
	Font font;
	std::stringstream ss;

	font.loadFromFile("Alef-Bold.ttf");
	hud.setFont(font);
	hud.setCharacterSize(75);
	hud.setFillColor(Color::White);

	int playerScore = 0;
	int AIScore = 0;

	bool firstBlood = false;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			myPaddle.moveUp();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			myPaddle.moveDown();
		}

		if (myBall.getPlayerScore() != playerScore || myBall.getAIScore() != AIScore)
		{
			pingSound.play();
			ss.str("");
			ss << myBall.getPlayerScore() << " : " << myBall.getAIScore();
			hud.setString(ss.str());
			playerScore = myBall.getPlayerScore();
			AIScore = myBall.getAIScore();

			if (firstBlood == false)
			{
				music.play();
				music.setVolume(50.f);
				music.setLoop(true);
				firstBlood = true;
			}
		}

		window.clear();
		window.draw(hud);
		window.draw(myBall.getShape());
		window.draw(myPaddle.getShape());
		window.draw(AIPaddle.getShape());
		AIPaddle.followBall(myBall);
		myBall.handlePaddleCollision(myPaddle);
		myBall.handlePaddleCollision(AIPaddle);
		myBall.update();
		myPaddle.update();
		AIPaddle.update();
		window.display();
	}

	return 0;
}