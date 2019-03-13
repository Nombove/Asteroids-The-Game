#pragma once
#include "ResourceManager.h"
#include "Animation.h"
#include "Game.h"
#include "Player.h"



class Player;


class Asteroids
{
public:
	Asteroids();
	~Asteroids();

	void Update(float elapsedSec);
	void Draw(sf::RenderWindow* pWindow);

	//amount of asteroids
	static const int amount = 180;


	

	sf::CircleShape m_Rock[amount];
	sf::CircleShape rock;


private:
	void HandleAnimation(float elapsedSec);

	sf::Vector2f velocity{ 75.0f,75.0f };
	float speed = 75.0f;

	Animation m_Anim;
	Player* m_pPlayer = nullptr;

};

