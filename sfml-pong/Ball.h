#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <random>
#include <iostream>
#include <sstream>


using namespace sf;

class Paddle;

class Ball
{
private:
	double radius = BALLRADIUS;
	double angle;
	double velocityX = BALLSPEED;
	double velocityY = BALLSPEED;

	int playerScore = 0;
	int AIScore = 0;

	SoundBuffer buff;
	
	Sound pingSound;
	

	Vector2f position;
	CircleShape ballShape;



public:
	Ball(double startX, double startY);
	FloatRect getPosition(void);
	CircleShape getShape(void);
	void update(void);
	void reset(void);
	void handleScreenCollision(void);
	void handlePaddleCollision(Paddle);
	int getPlayerScore();
	int getAIScore();

	
};