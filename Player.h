#pragma once
#include "ResourceManager.h"
#include "Animation.h"
#include "Game.h"

class Game;

class Player
{
public:
	Player();
	~Player();

	void Update(float elapsedSec);
	void Draw(sf::RenderWindow* pWindow);

	sf::Vector2f GetPosition() const;

	void HandleAnimation(float elapsedSec);

	sf::RectangleShape m_Body;
private:

	Animation m_Anim;
};

