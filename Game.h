#pragma once
#include "ResourceManager.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroids.h"
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <iostream>
#include <string>

#define one int


class Player;
class Asteroids;
class Enemy;
class Bullet;

class Game
{
public:
	Game();
	~Game();
	void Run();
	float RNG();
	
private:
	bool ProcessEvents();
	void Update(float deltaTime);
	void Draw(float deltaTime);

	void CreateBullet(sf::Vector2f position, one direction);
	void UpdateBullet(float deltaTime);
	void DrawBullet(sf::RenderWindow &window);

	void CreateEnemy(sf::Vector2f position,one direction);
	void UpdateEnemy(float deltaTime);
	void SpawnBullets(sf::Vector2f position, float deltaTime);
	void DrawEnemy(sf::RenderWindow &window);

	void Collision(float deltaTime);
	void Sound();
	void Font(float deltaTime);

	

	float holeSize = 100.0f;
	bool win = true;
	int point = 0;

	sf::RectangleShape m_background;
	sf::RectangleShape m_skylimit;

	sf::View m_View;
	sf::CircleShape m_score;
	std::vector<Bullet> ass;
	std::vector<Enemy> enem;


	sf::RenderWindow* m_pWindow = nullptr;
	Player* m_pPlayer = nullptr;
	Asteroids* m_pAsteroids = nullptr;
	//Enemy* m_pEnemy = nullptr;


};

