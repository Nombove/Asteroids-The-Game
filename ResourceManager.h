#pragma once
#include <SFML/Graphics.hpp>
#include <map>

class ResourceManager
{
public:
	static ResourceManager* GetInstance()
	{
		static ResourceManager instance;
		return &instance;
	}
	void CleanUp();

	~ResourceManager();

	sf::Texture* RequestTexture(std::string name);

private:
	ResourceManager();
	void LoadTexture(std::string path, std::string name);
private:
	std::map<std::string, sf::Texture*>m_Textures;
};

