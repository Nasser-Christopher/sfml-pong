#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <random>
#include "GlobalVar.h"

using namespace sf;

class Ball;


class Paddle
{
private:
	double velocityY = PADDLESPEED;
	Vector2f position;
	RectangleShape batShape;

public:
	Paddle(double startX, double startY);
	FloatRect getPosition(void);
	RectangleShape getShape(void);
	void update(void);
	void reset(void);
	void moveUp(void);
	void moveDown(void);
	void followBall(Ball myBall);
};