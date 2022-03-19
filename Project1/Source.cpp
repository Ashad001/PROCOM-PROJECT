#include <SFML/Graphics.hpp>
#include<vector>
#include "Bullet.h"
#include "Player.h"
#include <cstdlib>
using namespace std;



int main()
{
	//Window
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(1380, 780), "Game");
	window.setFramerateLimit(60);

	// Background
	sf::Texture Background;
	Background.loadFromFile("Back.png");
	sf::Sprite Back(Background);
	Back.setScale(1.6f, 1.0f);

	// Shoot
	Bullet playerShoot(2, 20);
	playerShoot.SetBulletColor(sf::Color::Red);
	vector<Bullet> projectiles;

	// The Plane
	sf::Texture PlayerTexture;
	PlayerTexture.loadFromFile("Plane3.png");
	Player player(window,&PlayerTexture, 12);


	// Enemies 
	sf::Texture EnemyTexture;
	EnemyTexture.loadFromFile("Enemy.png");
	sf::Sprite enemy(EnemyTexture);
	sf::Vector2u EnemySize = EnemyTexture.getSize();
	vector<sf::Sprite> enemies;

	

	// GameOver
	sf::Font font;
	font.loadFromFile("Font.ttf");
	sf::Text txt;
	txt.setFont(font);
	txt.setString("Game Over");
	txt.setCharacterSize(30);
	txt.setPosition(window.getSize().x / 2 - 80, window.getSize().y / 2 - 40);
	txt.setFillColor(sf::Color::White);
	txt.setOutlineThickness(2);
	txt.setOutlineColor(sf::Color::Red);

	//Score
	sf::Text Score;
	Score.setFont(font);
	Score.setString("SCORE");
	Score.setCharacterSize(19);
	Score.setPosition(window.getSize().x - 210,  200);
	Score.setFillColor(sf::Color::White);
	Score.setOutlineThickness(3);
	Score.setOutlineColor(sf::Color::Blue);

	// Kill Count
	int killCount = 0;
	sf::Text Count;
	Count.setFont(font);
	Count.setString(to_string(killCount));
	Count.setCharacterSize(22);
	Count.setPosition(window.getSize().x - 180, 250);
	Count.setFillColor(sf::Color::White);
	Count.setOutlineThickness(1);
	Count.setOutlineColor(sf::Color::Blue);


	int shootCounter = 0;
	int respawn = 0;
	int hitcount = 0;
	float enemy_pos_x = 0.f, enemy_pos_y = 0.f;
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				window.close();
			}
			if (evnt.type == sf::Event::Resized)
			{
			}
		}
		player.MovePLayer(window);
		if (shootCounter < 10)
		{
			shootCounter++;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootCounter >= 10)
		{
			playerShoot.SetBulletPosition(player.GetPlayerCentre().x - 56.0f, player.GetPlayerCentre().y - 20.0f);
			projectiles.push_back(Bullet(playerShoot));
			playerShoot.SetBulletPosition(player.GetPlayerCentre().x + 34.0f, player.GetPlayerCentre().y - 20.0f);
			projectiles.push_back(Bullet(playerShoot));
			shootCounter = 0;
		}
		for (int i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].MoveBullets(0.0f, -10.f);
			if (projectiles[i].BulletPosition().y < 0)
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
			enemy.setPosition(enemy_pos_x, enemy_pos_y);
			enemies.push_back(sf::Sprite(enemy));
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i].move(0.0f, 0.80f);
			if (enemies[i].getPosition().y <= 0)
			{
				enemies.erase(enemies.begin() + i);
			}
			if (enemies[i].getPosition().y > window.getSize().y)
			{
				player.SetHP(0);
			}
		}
		// collision
		for (int i = 0; i < enemies.size(); i++)
		{
			if (player.GetGlobalBounds().intersects(enemies[i].getGlobalBounds()))
			{	
				enemies.erase(enemies.begin() + i);
			}
		}

		Count.setString(to_string(killCount));


		for (int i = 0; i < enemies.size(); i++)
		{
			for (int j = 0; j < projectiles.size(); j++)
			{
				if (enemies[i].getGlobalBounds().intersects(projectiles[j].BulletGlobalBounds()))
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
		player.Draw(window);
		window.draw(Score);
		window.draw(Count);
		for (int i = 0; i < projectiles.size(); i++)
		{
			projectiles[i].DrawBullets(window);
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			window.draw(enemies[i]);
		}
		player.DrawHp(window);
		if (player.GetHp() <= 0)
		{
			window.clear(sf::Color::Black);
			window.draw(txt);
		}
		window.display();
	}
}