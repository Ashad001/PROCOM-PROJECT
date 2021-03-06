#include <SFML/Graphics.hpp>
#include<vector>
#include <iostream>
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

	// DINESH WORK
	sf::Texture Star01Pic;
	if (!Star01Pic.loadFromFile("Star01.png"))
	{
		cout << "Error! unable to load background star" << endl;
	}
	sf::Clock clock01; // starts the clock
	sf::Time elapsed1 = sf::seconds(1);
	sf::Sprite Star01[10];
	for (int i = 0; i < 10; i++)
	{
		Star01[i].setTexture(Star01Pic);
		switch (i)
		{
		case 0:
			Star01[i].setPosition(rand() % window.getSize().x, window.getSize().y);
			Star01[i].setColor(sf::Color::Cyan);
			break;
		case 1:
			Star01[i].setPosition(rand() % window.getSize().x, window.getSize().y % 5);
			Star01[i].setColor(sf::Color::Red);
			break;
		case 2:
			Star01[i].setPosition(rand() % window.getSize().x, window.getSize().y % 9);
			Star01[i].setColor(sf::Color::Blue);
			break;
		case 3:
			Star01[i].setPosition(rand() % window.getSize().x, window.getSize().y % 2);
			Star01[i].setColor(sf::Color::Yellow);
			break;
		case 4:
			Star01[i].setPosition(rand() % window.getSize().x, window.getSize().y % 2);
			Star01[i].setColor(sf::Color::Green);
			break;
		default:
			Star01[i].setPosition(rand() % window.getSize().x, window.getSize().y % 13);
			Star01[i].setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
			break;
		}
	}




	// Shoot
	Bullet playerShoot(2, 20);
	playerShoot.SetBulletColor(sf::Color::Red);
	vector<Bullet> projectiles;

	// The Plane
	sf::Texture PlayerTexture;
	PlayerTexture.loadFromFile("Plane3.png");
	Player player(window, &PlayerTexture, 12);


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
	txt.setPosition(window.getSize().x / 2 - 80, window.getSize().y / 2 - 150);
	txt.setFillColor(sf::Color::White);
	txt.setOutlineThickness(2);
	txt.setOutlineColor(sf::Color::Red);

	//Score
	sf::Text Score;
	Score.setFont(font);
	Score.setString("SCORE");
	Score.setCharacterSize(19);
	Score.setPosition(window.getSize().x - 210, 200);
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
	int hit = 0;
	float enemy_pos_x = 0.f, enemy_pos_y = 0.f;
	string Power = "111122323";
	int powerCounter = 0;
	int kill;
	while (window.isOpen())
	{
		// ALSO DINESH WORK
		if (clock01.getElapsedTime().asMilliseconds() < elapsed1.asMilliseconds())
		{
			for (int i = 0; i < 10; i++)
			{
				if (Star01[i].getPosition().y != -64)
				{
					Star01[i].setPosition(Star01[i].getPosition().x, Star01[i].getPosition().y - 1);
				}
				else
				{
					Star01[i].setPosition(Star01[i].getPosition().x, window.getSize().y + rand() % window.getSize().y);
				}
			}
		}
		else
		{
			clock01.restart();
		}

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
		if (respawn < 40)
		{
			respawn++;
		}
		if (respawn >= 40)
		{
			respawn = 0;
			if (Power[powerCounter] == '1')
			{
				enemy.setColor(sf::Color::Yellow);
			}
			else if (Power[powerCounter] == '2')
			{
				enemy.setColor(sf::Color::Green);
			}
			else if (Power[powerCounter] == '3')
			{
				enemy.setColor(sf::Color::Red);
			}
			powerCounter++;
			if (powerCounter >= Power.size() - 1)
			{
				powerCounter = 0;
			}
			enemy.setPosition((rand() % (int)(window.getSize().x - EnemySize.x * 2 - 330)), 0.0f);
			enemies.push_back(sf::Sprite(enemy));
		}
		for (int i = 0; i < enemies.size(); i++)
		{
			if (enemies[i].getColor() == sf::Color::Yellow)
			{
				enemies[i].move(0.0f, 0.8f);
			}
			else if (enemies[i].getColor() == sf::Color::Green)
			{
				enemies[i].move(0.0f, 0.5f);
			}
			else if (enemies[i].getColor() == sf::Color::Red)
			{
				enemies[i].move(0.0f, 0.3f);
			}
			if (enemies[i].getPosition().y <= 0)
			{
				enemies.erase(enemies.begin() + i);
			}
			if (enemies[i].getPosition().y + 50 > window.getSize().y)
			{
				player.SetHP(0);
			}
		}
		// collision
		for (int i = 0; i < enemies.size(); i++)
		{
			if (player.GetGlobalBounds().intersects(enemies[i].getGlobalBounds()))
			{
				player.SetHP(player.GetHp() - 1);
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
					if (enemies[i].getColor() == sf::Color::Yellow)
					{
						hit = 2;
						kill = 1;
					}
					else if (enemies[i].getColor() == sf::Color::Green)
					{
						hit = 5;
						kill = 2;
					}
					else if (enemies[i].getColor() == sf::Color::Red)
					{
						hit = 8;
						kill = 4;

					}
					if (hitcount >= hit)
					{
						killCount += kill;
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
			Score.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2);
			Count.setPosition(window.getSize().x / 2 - 25, window.getSize().y / 2 + 50);
			window.draw(Score);
			window.draw(Count);
		}
		// GUESS WHAT IT'S ALSO DINESH WORK
		for (int i = 0; i < 10; i++)
		{
			window.draw(Star01[i]);
		}
		window.display();
	}
}
