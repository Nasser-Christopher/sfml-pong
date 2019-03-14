#include "GlobalVar.h"
#include "Paddle.h"
#include "Ball.h"


Paddle::Paddle(double startX, double startY)
{
	this->position.x = startX;
	this->position.y = startY;

	batShape.setSize(sf::Vector2f(PADDLEWIDTH, PADDLEHEIGHT));
	batShape.setPosition(position);
}

FloatRect Paddle::getPosition()
{
	return batShape.getGlobalBounds();
}

RectangleShape Paddle::getShape()
{
	return batShape;
}

void Paddle::moveUp()
{
	if (position.y > SCREEN_HEIGHT - SCREEN_HEIGHT)
	{
		//std::cout << "[-]IM BEING MOVED UP!\n";
		this->position.y -= PADDLESPEED;
	}
}

void Paddle::moveDown()
{
	if (position.y < SCREEN_HEIGHT - PADDLEHEIGHT)
	{
		//std::cout << "[-]IM BEING MOVED DOWN!\n";
		this->position.y += PADDLESPEED;
	}
}

void Paddle::update()
{
	batShape.setPosition(position);
}

void Paddle::reset()
{
	batShape.setPosition((SCREEN_WIDTH - SCREEN_WIDTH + PADDLEWIDTH), ((SCREEN_HEIGHT / 2) - PADDLEHEIGHT));


}

void Paddle::followBall(Ball myBall)
{
	if (myBall.getShape().getPosition().y > this->getShape().getPosition().y)
	{
		this->moveDown();
	}
	else if (myBall.getShape().getPosition().y < this->getShape().getPosition().y)
	{
		this->moveUp();
	}
	else
	{
		this->getShape().setPosition(myBall.getShape().getPosition());
	}
}