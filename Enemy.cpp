#include "Enemy.h"+



Enemy::Enemy(sf::Vector2f position, int direction)
{
	
	EnemyBody.setRadius({ 50.0f });
	EnemyBody.setTexture(ResourceManager::GetInstance()->RequestTexture("enemy"));
	int randX = rand()%4000 + 1;
	float randomX = randX;
	EnemyBody.setPosition(0.0f,randomX);
	this->direction = direction;
}


Enemy::~Enemy()
{
}

void Enemy::Update(float elapsedSec)
{
	EnemyBody.move(sf::Vector2f(direction*100.0f, 0.0f)*elapsedSec);
}

