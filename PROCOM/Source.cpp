#include <SFML/Graphics.hpp>
#include<vector>
#include <cstdlib>
using namespace std;

int main()
{
	//Window
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(900, 512), "Game");
	window.setFramerateLimit(60);

	// Background
	sf::Texture Background;
	Background.loadFromFile("Back.png");
	sf::Sprite Back(Background);

	// Shoot
	sf::CircleShape projectile1;
	sf::CircleShape projectile2;
	projectile1.setRadius(4.0f);
	projectile1.setFillColor(sf::Color::Red);
	projectile2.setRadius(4.0f);
	projectile2.setFillColor(sf::Color::Red);
	vector<sf::CircleShape> projectiles;
	projectiles.push_back(sf::CircleShape(projectile1));
	projectiles.push_back(sf::CircleShape(projectile2));


	// The planE
	sf::Texture PlayerTexture;
	PlayerTexture.loadFromFile("Plane3.png");
	sf::Sprite player(PlayerTexture);
	sf::Vector2u size = PlayerTexture.getSize();
	player.setPosition(window.getSize().x / 2 - size.x - 300, window.getSize().y - size.y / 2 - 70);
	
	// Enemies 
	sf::Texture EnemyTexture;
	EnemyTexture.loadFromFile("Enemy.png");
	sf::Sprite enemy(EnemyTexture);
	sf::Vector2u EnemySize = EnemyTexture.getSize();
	vector<sf::Sprite> enemies;

	// Health Bar
	int hp = 12;
	sf::RectangleShape HP;
	HP.setFillColor(sf::Color::Blue);
	HP.setSize(sf::Vector2f(hp * 5.0f, 8.0f));
	HP.setPosition(player.getPosition().x + 50 , player.getPosition().y + 90);

	// GameOver
	sf::Font font;
	font.loadFromFile("Font.ttf");
	sf::Text txt;
	txt.setFont(font);
	txt.setString("Game Over");
	txt.setCharacterSize(30);
	txt.setPosition(window.getSize().x / 2 - 80,  window.getSize().y / 2 - 40);
	txt.setFillColor(sf::Color::White);
	txt.setOutlineThickness(2);
	txt.setOutlineColor(sf::Color::Red);
	
	//Score
	sf::Text Score;
	Score.setFont(font);
	Score.setString("SCORE");
	Score.setCharacterSize(17); 
	Score.setPosition(window.getSize().x - 170,window.getSize().y - 400 );
	Score.setFillColor(sf::Color::White);
	Score.setOutlineThickness(3);
	Score.setOutlineColor(sf::Color::Blue);

	// Kill Count
	int killCount = 0;
	sf::Text Count;
	Count.setFont(font);
	Count.setString(to_string(killCount));
	Count.setCharacterSize(20);
	Count.setPosition(window.getSize().x - 140, window.getSize().y - 350);
	Count.setFillColor(sf::Color::White);
	Count.setOutlineThickness(1);
	Count.setOutlineColor(sf::Color::Blue);


	sf::Vector2f PlayerCentre;
	int shootCounter = 0;
	int respawn = 0;
	int hitcount = 0;
	while (window.isOpen() )
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		PlayerCentre = sf::Vector2f(player.getPosition().x  + 75.0f, player.getPosition().y + 30 );
		player.setPosition(sf::Mouse::getPosition(window).x, player.getPosition().y) ;
		HP.setPosition(sf::Mouse::getPosition(window).x + 35, player.getPosition().y + 80);
		if (HP.getPosition().x  < 0)
		{
			HP.setPosition(0.0f, HP.getPosition().y);
		}
		if (HP.getPosition().x + HP.getSize().x  - 120 > window.getSize().y )
		{
			HP.setPosition(window.getSize().x - HP.getSize().x - 280, HP.getPosition().y);
		}
		if (player.getPosition().x + 40 < 0)
		{
			player.setPosition(-50.0f, window.getSize().y - size.y / 2 - 70);;
		}
		if (player.getPosition().x  + size.x + 250  >= window.getSize().x)
		{
			player.setPosition(window.getSize().x - size.x + 50 - 300, window.getSize().y - size.y  / 2 - 70);
		}
		if (shootCounter < 10)
		{
			shootCounter++;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootCounter >= 10)
		{
			projectile1.setPosition(PlayerCentre.x - 59.0f , PlayerCentre.y - 10);
			projectiles.push_back(sf::CircleShape(projectile1));
			projectile2.setPosition(PlayerCentre.x + 30.0f, PlayerCentre.y - 10);
			projectiles.push_back(sf::CircleShape(projectile2));
			shootCounter = 0;
			
		}
		for (int i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].move(0.0f, -10.f);
			if (projectiles[i].getPosition().y < 0)
			{
				projectiles.erase(projectiles.begin() + i);
			}
		}
		// Enemies
		if (respawn < 20)
		{
			respawn++;
		}
		if (respawn >= 20)
		{
			respawn = 0;
			enemy.setPosition((rand() % (int)(window.getSize().x - EnemySize.x * 2 - 250)), 0.0f);
			enemies.push_back(sf::Sprite(enemy));
		}

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(0.0f, 0.80f);
			if (enemies[i].getPosition().y < 0)
			{
				enemies.erase(enemies.begin() + i);
			}
			if (enemies[i].getPosition().y > window.getSize().y)
			{
				hp = 0;
			}
		}
		// collision
		for (int i = 0; i < enemies.size(); i++)
		{
			if (player.getGlobalBounds().intersects(enemies[i].getGlobalBounds()))
			{
				hp--;
				HP.setFillColor(sf::Color((hp * 10), 0 , 250));
				enemies.erase(enemies.begin() + i);
			}
		}
		
		HP.setSize(sf::Vector2f(hp * 5.0f, 8.0f));
		Count.setString(to_string(killCount));


		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < projectiles.size(); j++)
			{
				if(enemies[i].getGlobalBounds().intersects(projectiles[j].getGlobalBounds()))
				{
					hitcount++;
					if (hitcount >= 2)
					{
						killCount++;
						enemies.erase(enemies.begin() + i);
						hitcount = 0;
					}
					projectiles.erase(projectiles.begin() + j);
					break;
				}
			}
		}

		window.clear(sf::Color::Black);
		window.draw(Back);
		window.draw(player);
		window.draw(Score);
		window.draw(Count);
		for (int i = 0; i < projectiles.size(); i++)
		{
			window.draw(projectiles[i]);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}
		window.draw(HP);
		if (hp <= 0)
		{
			window.clear(sf::Color::Black);
			window.draw(txt);
		}
		window.display();			
	}
}
