#include "Bullet.h"



Bullet::Bullet(sf::Vector2f position, int direction)
{
	BulletBody.setRadius({ 5.0f });
	BulletBody.setFillColor(sf::Color::Red);
	BulletBody.setPosition(position);
	this->direction = direction;
}


Bullet::~Bullet()
{
}

void Bullet::Update(float elapsedSec)
{
	BulletBody.move(sf::Vector2f(0.0f, direction*500.0f)*elapsedSec);
}
