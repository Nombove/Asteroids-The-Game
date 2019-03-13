#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
	LoadTexture("Resources/shuttle_anim.png", "shuttleA");

	LoadTexture("Resources/background.png", "background");
	LoadTexture("Resources/sky_limit.png", "sky_limit");

	LoadTexture("Resources/enemy.png", "enemy");
	LoadTexture("Resources/rock.png", "rock");
	LoadTexture("Resources/small_rockA.png", "small_rock");
	LoadTexture("Resources/b_hole.png", "b_hole");


}

void ResourceManager::LoadTexture(std::string path, std::string name)
{
	sf::Texture* t = new sf::Texture();
	t->loadFromFile(path);

	m_Textures[name] = t;
}

void ResourceManager::CleanUp()
{
	for (auto i : m_Textures)
	{
		delete i.second;
		i.second = nullptr;
	}
}

ResourceManager::~ResourceManager()
{
}

sf::Texture * ResourceManager::RequestTexture(std::string name)
{
	if (m_Textures[name])
		return m_Textures[name];

	return nullptr;
}