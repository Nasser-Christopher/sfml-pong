#include "GlobalVar.h"
#include "Ball.h"
#include "Paddle.h"




using namespace std;


Ball::Ball (double startX, double startY)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 360);

	this->angle = dis(gen);

	this->velocityX = BALLSPEED * cos(this->angle);
	this->velocityY = BALLSPEED * sin(this->angle);

	this->position.x = startX;
	this->position.y = startY;

	this->ballShape.setRadius(radius);
	this->ballShape.setPosition(position);

	
	this->buff.loadFromFile("ping.wav");
	this->pingSound.setBuffer(buff);


}
CircleShape Ball::getShape()
{
	return this->ballShape;
}

FloatRect Ball::getPosition()
{
	return this->ballShape.getGlobalBounds();
}

void Ball::reset()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 359);

	int randomAngle = dis(gen);
	double velX = BALLSPEED * cos(randomAngle);
	double velY = BALLSPEED * sin(randomAngle);

	if (velX <= BALLMINVELOCITY && velX >= -(BALLMINVELOCITY))
	{
		cout << "[x]BAD ANGLE FOUND\t:\tRESETTING\n";
		this->reset();
	}
	else
	{

		this->angle = randomAngle;
		this->velocityX = velX;
		this->velocityY = velY;
		std::cout << "[v]" << this->angle << " <-- NEW RANDOM ANGLE\n";
		this->position.x = SCREEN_WIDTH / 2;
		this->position.y = SCREEN_HEIGHT / 2;
		this->ballShape.setPosition(position);
	}
}


void Ball::handleScreenCollision()
{
	if (this->getShape().getPosition().x >= SCREEN_WIDTH - BALLRADIUS) // Player Scored
	{
		this->reset();
		this->playerScore++;

	}
	else if (this->getShape().getPosition().x <= SCREEN_WIDTH - SCREEN_WIDTH - BALLRADIUS) // AI scored 
	{
		this->reset();
		this->AIScore++;
		
	}
	else if (this->getShape().getPosition().y >= SCREEN_HEIGHT - 1.5*BALLRADIUS
		|| this->getShape().getPosition().y <= SCREEN_HEIGHT - SCREEN_HEIGHT)
	{
		pingSound.play();

		this->velocityY = -(this->velocityY);
		this->velocityX *= 1.1;
		this->velocityY *= 1.1;
		std::cout << "[v] VELOCITY Y NEGATED\n";
	}
}

void Ball::handlePaddleCollision(Paddle myPaddle)
{
	
	if (this->getShape().getGlobalBounds().intersects(myPaddle.getShape().getGlobalBounds()))
	{
		pingSound.play();

		this->velocityX = -(velocityX);
		this->velocityX *= 1.2;
		this->velocityY *= 1.1;
	}
}

void Ball::update()
{
	this->position.x += velocityX;
	this->position.y += velocityY;
	this->ballShape.setPosition(this->position);
	this->handleScreenCollision();
}

int Ball::getPlayerScore()
{
	return this->playerScore;
}

int Ball::getAIScore()
{
	return this->AIScore;
}