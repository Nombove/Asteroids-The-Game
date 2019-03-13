#include "Asteroids.h"

//animation parameters(picture)
const int Ha = 64;
const int Wa = 1024;
const int AoA = 16;


Asteroids::Asteroids() :
	m_Anim(AoA, AoA)	//velocity, amount of animations
{

	for (int i = 0; i < amount; i++)
	{
		int  randomizeX = rand() % 4000 + 1;
		float randomX = randomizeX;
		int  randomizeY = rand() % 4000 + 1;
		float randomY = randomizeY;

		m_Rock[i].setRadius({ 50.0f });
		m_Rock[i].setPosition({ randomX,randomY });
		if(i<100)
			m_Rock[i].setTexture(ResourceManager::GetInstance()->RequestTexture("rock"));
		else
			m_Rock[i].setTexture(ResourceManager::GetInstance()->RequestTexture("small_rock"));
		m_Rock[i].setTextureRect({ 0,0,Wa / AoA,Ha }); //position of the first frame ./amount of animations
	}

	m_pPlayer = new Player();
}

Asteroids::~Asteroids()
{
	delete m_pPlayer;
	m_pPlayer = nullptr;
}

void Asteroids::Update(float elapsedSec)
{
	HandleAnimation(elapsedSec);

	for (int i = 0; i < amount; i++)
	{

		m_Rock[i].move((this->velocity)*elapsedSec);

		//collison with the end of the universe!    

		if (m_Rock[i].getPosition().x < 0)	//left
		{
			velocity.x = speed;
			m_Rock[i].setPosition(m_Rock[i].getPosition().y, 0.0f);
		}
		if (m_Rock[i].getPosition().x > 4000)	//right
		{
			velocity.x = speed;
			m_Rock[i].setPosition(m_Rock[i].getPosition().y, 4000.0f);
		}

		if (m_Rock[i].getPosition().y < 0)	//top
		{
			velocity.y = -speed;
			m_Rock[i].setPosition(0.0f, m_Rock[i].getPosition().x);
		}
		if (m_Rock[i].getPosition().y > 4000)	//bottom
		{
			velocity.y = -speed;
			m_Rock[i].setPosition(4000.0f, m_Rock[i].getPosition().x);
		}
	}
}

void Asteroids::Draw(sf::RenderWindow* pWindow)
{
	for (int i = 0; i < amount; i++)
		pWindow->draw(m_Rock[i]);
}

void Asteroids::HandleAnimation(float elapsedSec)
{
	m_Anim.Update(elapsedSec);

	int currentFrame = m_Anim.GetCurrentFrame();
	for (int i = 0; i < amount; i++)
		m_Rock[i].setTextureRect({ currentFrame *(Wa / AoA),0,(Wa / AoA),Ha });
}

