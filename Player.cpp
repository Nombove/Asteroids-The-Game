#include "Player.h"

//animation parameters(picture)
const int Ha = 490;
const int Wa = 1390;
const int AoA = 5;


Player::Player() :
	m_Anim(2 * AoA, AoA)	//velocity, amount of animations
{
	m_Body.setSize({ 50.0f,100.0f });
	m_Body.setPosition({ 2000.0f,2000.0f });
	m_Body.setTexture(ResourceManager::GetInstance()->RequestTexture("shuttleA"));
	m_Body.setTextureRect({ 0,0,Wa / AoA,Ha }); //position of the first frame ./amount of animations
}


Player::~Player()
{
}

void Player::Update(float elapsedSec)
{
	HandleAnimation(elapsedSec);

	auto position = m_Body.getPosition();

	sf::Vector2<float> velocity;
	float speed = 200.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		velocity.y = -speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		velocity.y = speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x = -speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x = speed;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		velocity.y = -speed * 2.0f;


	//collison with the end of the universe!
	float wallSpeed = 10.0f;

	if (GetPosition().x >= 4000)
		velocity.x = -wallSpeed;
	else if (GetPosition().y >= 4000)
		velocity.y = -wallSpeed;
	else if (GetPosition().x <= 0)
		velocity.x = wallSpeed;
	else if (GetPosition().y <= 0)
		velocity.y = speed;

	position += velocity * elapsedSec;
	m_Body.setPosition(position);

}

void Player::Draw(sf::RenderWindow* pWindow)
{
	pWindow->draw(m_Body);
}

sf::Vector2f Player::GetPosition() const
{
	return m_Body.getPosition();
}

void Player::HandleAnimation(float elapsedSec)
{
	m_Anim.Update(elapsedSec);

	int currentFrame = m_Anim.GetCurrentFrame();
	m_Body.setTextureRect({ currentFrame *(Wa / AoA),0,(Wa / AoA),Ha });	//Width and Heigh(10,9)
}

