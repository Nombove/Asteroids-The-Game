#include "Game.h"



Game::Game()
{
	m_pWindow = new sf::RenderWindow{ {1280,720},"SkyLimit" };


	//background
	m_background.setTexture(ResourceManager::GetInstance()->RequestTexture("background"));
	m_background.setSize({ 4072.0f,4133.0f });
	m_skylimit.setTexture(ResourceManager::GetInstance()->RequestTexture("sky_limit"));
	m_skylimit.setSize({ 6000.0f, 6000.0f });
	m_skylimit.setPosition(-900.0f, -900.0f);
	//b_hole & exit
	m_score.setPosition(RNG(),RNG());
	m_score.setTexture(ResourceManager::GetInstance()->RequestTexture("b_hole"));
	//set icon
	sf::Image icon;
	if (!icon.loadFromFile("Resources/icon.png"))
		std::cout << "Nie zaladowano ikonki";
	m_pWindow->setIcon(128, 128, icon.getPixelsPtr());
	//pointers
	m_pPlayer = new Player();
	m_pAsteroids = new Asteroids();
	//view
	m_View.setSize(1280, 720);
	m_View.zoom(1.0f);
}


Game::~Game()
{
	ResourceManager::GetInstance()->CleanUp();
	delete m_pWindow;
	m_pWindow = nullptr;

	delete m_pPlayer;
	m_pPlayer = nullptr;

	delete m_pAsteroids;
	m_pAsteroids = nullptr;

	delete m_pAsteroids;
	m_pAsteroids = nullptr;
}

void Game::Run()
{
	sf::Clock clock;
	float deltaTime;

	bool isRunning = true;

	m_pWindow->setFramerateLimit(60);

	while (isRunning)
	{

		deltaTime = clock.restart().asSeconds();
		
		
		isRunning = ProcessEvents();
		if (!isRunning) return;


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			isRunning = false;
		}
		
		Update(deltaTime);
		
		Draw(deltaTime);

			
	}
}

bool Game::ProcessEvents()
{
	sf::Event event;
	while (m_pWindow->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_pWindow->close();
			return false;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Space)
			{
				CreateBullet(m_pPlayer->GetPosition(), -1);
				CreateEnemy(m_pPlayer->GetPosition(), 1);
			}
		default:
			break;
		}
	}
	return true;
}

void Game::Update(float deltaTime)
{
	m_View.setCenter(m_pPlayer->GetPosition());
	m_pPlayer->Update(deltaTime);
	m_pAsteroids->Update(deltaTime);

	Collision(deltaTime);
	UpdateBullet(deltaTime);
	UpdateEnemy(deltaTime);
}

void Game::Draw(float deltaTime)
{
	m_pWindow->clear();

	m_pWindow->setView(m_View);

	m_pWindow->draw(m_background);
	

	m_pPlayer->Draw(m_pWindow);
	m_pAsteroids->Draw(m_pWindow);
	DrawEnemy(*m_pWindow);
	DrawBullet(*m_pWindow);

	m_pWindow->draw(m_skylimit);

	m_pWindow->draw(m_score);
	Font(deltaTime);



	m_pWindow->display();
}

void Game::CreateBullet(sf::Vector2f position, one direction)
{
	Bullet bullet(position, direction);
	ass.push_back(bullet);
}

void Game::UpdateBullet(float deltaTime)
{
	std::vector<Bullet> newBullets;
	for (std::vector<Bullet>::iterator it = ass.begin(); it != ass.end(); ++it)
	{
		it->Update(deltaTime);
		if (it->BulletBody.getPosition().y >= 0)
			newBullets.push_back(*it);
	}
	ass = newBullets;
}

void Game::DrawBullet(sf::RenderWindow & window)
{
	for (std::vector<Bullet>::iterator it = ass.begin(); it != ass.end(); ++it)
		window.draw(it->BulletBody);
}

void Game::CreateEnemy(sf::Vector2f position,one direction)
{
	Enemy enemy(position,direction);
	enem.push_back(enemy);
}

void Game::UpdateEnemy(float deltaTime)
{
	std::vector<Enemy> newEnemy;
	for (std::vector<Enemy>::iterator it = enem.begin(); it != enem.end(); ++it)
	{
		it->Update(deltaTime);
		if (it->EnemyBody.getPosition().x <= 4000)
			newEnemy.push_back(*it);
	}
	enem = newEnemy;


}

void Game::DrawEnemy(sf::RenderWindow & window)
{
	for (std::vector<Enemy>::iterator it = enem.begin(); it != enem.end(); ++it)
		window.draw(it->EnemyBody);
}

void Game::SpawnBullets(sf::Vector2f position, float deltaTime)
{
	for (std::vector<Enemy>::iterator it = enem.begin(); it != enem.end(); ++it)
	{
		CreateBullet(it->EnemyBody.getPosition(), 1);
		Bullet bullet(position, -1);
		ass.push_back(bullet);

		std::vector<Bullet> newBullets;
		for (std::vector<Bullet>::iterator it = ass.begin(); it != ass.end(); ++it)
		{
			it->Update(deltaTime);
			if (it->BulletBody.getPosition().y >= 0)
				newBullets.push_back(*it);
		}
		ass = newBullets;
	}


}




void Game::Collision(float deltaTime)
{
	int amount = Asteroids::amount;

	auto CollPlayer = m_pPlayer->m_Body.getGlobalBounds();

	//repair rotation
	///float DT = 0.0f;
	///	DT += deltaTime;
	///m_score.setRotation(DT*10);

	//size of hole
	holeSize += 2 * deltaTime;
	m_score.setRadius(holeSize);

	//bullet vs asteroids

	bool flag = false;

	std::vector<Bullet>::iterator it = ass.begin();

	while (it != ass.end())
	{
		for (int i = 0; i < amount; i++)
		{
			if (it->BulletBody.getGlobalBounds().intersects(m_pAsteroids->m_Rock[i].getGlobalBounds()))
			{
				///Sound();
				point++;
				m_pAsteroids->m_Rock[i].setRadius({ 0.0f });
				it = ass.erase(it);
				flag = true;
				break;
			}

		}
		if (!flag)
		{
			++it;
		}
		else
		{
			flag = false;
		}

	}

	//player vs asteroids 
	for (int i = 0; i < amount; i++)
	{


		if (CollPlayer.intersects(m_pAsteroids->m_Rock[i].getGlobalBounds()))
		{
			///	Sound();
			holeSize -= 10.0f;	//do naprawy
			point--;
			m_score.setRadius(holeSize);
			if (holeSize <= 0.0f && win)
			{
				
				std::cout << "Przegrales!";
				win = false;
				
			}
			m_pAsteroids->m_Rock[i].setRadius({ 0.0f });

		}
	}

	if (CollPlayer.intersects(m_score.getGlobalBounds() )&& win)
	{
		std::cout << "Wygrales!";
		win = false;
	}
}

void Game::Sound()
{
	sf::SoundBuffer buffer;
	if(!buffer.loadFromFile("Resources/Explosion.wav"))
		std::cout << "Nie zaladowano dzwieku";
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
}

void Game::Font(float deltaTime)
{
	sf::Text scoreText,winText;
	sf::Font font;

	if (!font.loadFromFile("Resources/Font.ttf"))
		std::cout << "Nie zaladowano czcionki";

	scoreText.setFont(font);
	scoreText.setCharacterSize(30);
	scoreText.setFillColor(sf::Color::Red);

	auto CollPlayer = m_pPlayer->m_Body.getGlobalBounds();

	if (CollPlayer.intersects(m_score.getGlobalBounds()))
	{
		winText.setFont(font);
		winText.setCharacterSize(200);
		winText.setFillColor(sf::Color::Blue);
		winText.setPosition(m_score.getPosition().x-200.0f , m_score.getPosition().y);
		//if (!win)
			//winText.setString("Przegrales");
		
		winText.setString("Wygrales!");

		m_pWindow->draw(winText);
	}
	

		scoreText.setPosition(m_pPlayer->GetPosition().x - 1260.0f/2.0f, m_pPlayer->GetPosition().y-700.0f/2.0f);
		scoreText.setString("Zdobyles " + std::to_string(point)+ " Punktow");

		m_pWindow->draw(scoreText);


	

}

float Game::RNG()
{
	std::random_device dev;
	std::mt19937 gen(dev());
	std::uniform_real_distribution<> dis(2000, 4000);

	return dis(gen);
}

