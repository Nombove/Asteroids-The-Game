#pragma once
#include "ResourceManager.h"
#include "Game.h"

class Bullet
{
public:
	Bullet(sf::Vector2f position, int direction);
	~Bullet();

	sf::CircleShape BulletBody;
	void Update(float elapsedSec);
	int direction;
	
};

