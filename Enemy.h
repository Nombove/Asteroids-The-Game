#pragma once
#include "Game.h"
#include "ResourceManager.h"


class Enemy
{
public:
	Enemy(sf::Vector2f position, int direction);
	~Enemy();

	sf::CircleShape EnemyBody;
	void Update(float elapsedSec);
	int direction;

};

