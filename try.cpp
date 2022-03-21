#include <SFML/Graphics.hpp>
#include<vector>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include <cstdlib>
#include "Animation.h"
using namespace std;



int main()
{
	int Is_Game_Start = 0;
	int startGame = 0;
	int Is_Game_Pause = 0;

	//Window
	srand(time(NULL));
	//sf::RenderWindow window(sf::VideoMode(700, 700), "Game");
	sf::RenderWindow window(sf::VideoMode(1380, 780), "Game", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	// DINEHS WORK 2
	sf::RectangleShape MainScreen(sf::Vector2f(window.getSize()));
	MainScreen.setFillColor(sf::Color(13, 13, 13));

	sf::Texture EarthTexture;
	EarthTexture.loadFromFile("try.png");
	EarthTexture.setSmooth(true);
	sf::Sprite Picture0;
	Picture0.setTexture(EarthTexture);
	Picture0.setScale(2.f, 2.f);
	Picture0.setOrigin(EarthTexture.getSize().x / 2.0, EarthTexture.getSize().y / 2.0);
	Picture0.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2, MainScreen.getPosition().y + MainScreen.getSize().y / 2);

	sf::Text GameTitle;
	sf::Font TitleFont;
	TitleFont.loadFromFile("Bungee-Regular.ttf");
	GameTitle.setFont(TitleFont);
	GameTitle.setString("Space War");
	GameTitle.setCharacterSize(MainScreen.getSize().y / 6.0);
	GameTitle.setOrigin(GameTitle.getGlobalBounds().width / 2.f, (GameTitle.getGlobalBounds().height / 2.f) + GameTitle.getGlobalBounds().height);
	GameTitle.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0);
	GameTitle.setStyle(sf::Text::Bold);

	sf::Text Start;
	Start.setFont(TitleFont);
	Start.setString("START");
	Start.setCharacterSize(MainScreen.getSize().y / 20.0);
	Start.setOrigin(Start.getGlobalBounds().width / 2.f, (Start.getGlobalBounds().height / 2.f) - GameTitle.getGlobalBounds().height);
	Start.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0);
	Start.setStyle(sf::Text::Bold);

	sf::Text Pause;
	Pause.setFont(TitleFont);
	Pause.setString("PAUSE");
	Pause.setCharacterSize(MainScreen.getSize().y / 25.0);
	//Pause.setOrigin(Pause.getGlobalBounds().width / 2.f, (Pause.getGlobalBounds().height / 2.f) - GameTitle.getGlobalBounds().height);
	Pause.setPosition(window.getSize().x - 210, 500);
	Pause.setStyle(sf::Text::Bold);
	Pause.setOutlineThickness(3);


	sf::Text Quit;
	Quit.setFont(TitleFont);
	Quit.setString("QUIT");
	Quit.setCharacterSize(MainScreen.getSize().y / 20.0);
	Quit.setOrigin(Quit.getGlobalBounds().width / 2.f, Quit.getGlobalBounds().height / 2.f);
	Quit.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0 + GameTitle.getGlobalBounds().height + Start.getGlobalBounds().height + Quit.getGlobalBounds().height);
	Quit.setStyle(sf::Text::Bold);


	// Background
	sf::Texture Background;
	Background.loadFromFile("Back.png");
	//sf::Sprite Back(Background);
	//Back.setScale(1.6f, 1.0f);

	// DINESH WORK
	sf::Texture Star01Pic;
	if (!Star01Pic.loadFromFile("Meteors.png"))
	{
		cout << "Error! unable to load background star" << endl;
	}
	sf::Clock clock01; // starts the clock
	sf::Time elapsed1 = sf::seconds(1);
	sf::Sprite Star01[10];
	Animation animation_meteors(&Star01Pic, sf::Vector2u(4, 1), 400);

	sf::Texture Star02Pic;
	if (!Star02Pic.loadFromFile("Star02.png"))
	{
		cout << "Error! unable to load background star" << endl;
	}
	sf::Sprite Star02;
	vector<sf::Sprite> stars;
	Star02.setTexture(Star02Pic);

	float deltaTime = 0.0f;

	for (int i = 0; i < 10; i++)
	{
		Star01[i].setTexture(Star01Pic);
		switch (i)
		{
		case 0:
			Star01[i].setPosition(rand() % window.getSize().x - 350, window.getSize().y);
			Star01[i].setColor(sf::Color(128, 128, 128));
			Star01[i].setScale(1.5f, 1.5f);
			break;
		case 1:
			Star01[i].setPosition(rand() % window.getSize().x - 350, window.getSize().y % 5);
			Star01[i].setColor(sf::Color(105, 105, 105));
			Star01[i].setScale(3.f, 3.f);
			break;
		case 2:
			Star01[i].setPosition(rand() % window.getSize().x - 350, window.getSize().y % 9);
			Star01[i].setColor(sf::Color(105, 105, 105));
			Star01[i].setScale(2, 2);

			break;
		case 3:
			Star01[i].setPosition(rand() % window.getSize().x - 350, window.getSize().y % 2);
			Star01[i].setColor(sf::Color(119, 136, 153));
			Star01[i].setScale(1.4f, 1.4f);
			break;
		case 4:
			Star01[i].setPosition(rand() % window.getSize().x - 350, window.getSize().y % 2);
			Star01[i].setColor(sf::Color(112, 128, 144));
			Star01[i].setScale(4.f, 4.f);

			break;
		default:
			Star01[i].setPosition(rand() % window.getSize().x - 350, window.getSize().y % 13);
			Star01[i].setScale(1.f, 1.f);
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
	EnemyTexture.loadFromFile("Enemy4.png");
	sf::Sprite enemy(EnemyTexture);
	sf::Vector2u EnemySize = EnemyTexture.getSize();
	enemy.setScale(1.f, 1.f);
	vector<sf::Sprite> enemies;
	Animation animation_enemy(&EnemyTexture, sf::Vector2u(3, 2), 300);



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
	Score.setFont(TitleFont);
	Score.setString("SCORE");
	Score.setCharacterSize(MainScreen.getSize().y / 25.0);
	Score.setPosition(window.getSize().x - 210, 200);
	Score.setFillColor(sf::Color::White);
	Score.setOutlineThickness(3);
	Score.setOutlineColor(sf::Color::Blue);

	// Kill Count
	int killCount = 0;
	sf::Text Count;
	Count.setFont(TitleFont);
	Count.setString(to_string(killCount));
	Count.setCharacterSize(MainScreen.getSize().y / 25.0);
	Count.setPosition(window.getSize().x - 180, 250);
	Count.setFillColor(sf::Color::White);
	Count.setOutlineThickness(1);
	Count.setOutlineColor(sf::Color::Blue);


	int shootCounter = 0;
	int respawn = 0;
	int hitcount = 0;
	int hit = 0;
	float enemy_pos_x = 0.f, enemy_pos_y = 0.f;
	string Power = "1213121213123";
	int powerCounter = 0;
	int kill;
	int OverHeat = 0; // Yeah I am Evil ;)
	bool Over = true;
	int dead = 0;
	int StarCount = 0;



	while (window.isOpen())
	{
		Pause.setFillColor(sf::Color::White);
		Pause.setOutlineColor(sf::Color::Blue);
		
		GameTitle.setFillColor(sf::Color::White);
		Start.setFillColor(sf::Color::White);
		Quit.setFillColor(sf::Color::White);

		// Pause Game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			if (Is_Game_Pause == 0)
			{
				Pause.setFillColor(sf::Color::Blue);
				Pause.setOutlineColor(sf::Color::White);
				Is_Game_Pause = 1;
			}
			else
			{
				Pause.setFillColor(sf::Color::Blue);
				Pause.setOutlineColor(sf::Color::White);
				Is_Game_Pause = 0;
			}
		}
		if (Is_Game_Pause == 0)
		{
			deltaTime = clock01.restart().asMilliseconds();
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

		if (Is_Game_Pause == 0)
		{
			player.MovePLayer(window, deltaTime);
			if (shootCounter < 8)
			{
				shootCounter++;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootCounter >= 8)
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
			//Stars in background
			if (StarCount < 10)
			{
				StarCount++;
			}
			if (StarCount >= 10)
			{
				StarCount = 0;
				Star02.setColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
				Star02.setPosition((rand() % (int)(window.getSize().x - 330)), 0.0f);
				stars.push_back(sf::Sprite(Star02));
			}


			// Enemies
			if (respawn < 70)
			{
				respawn++;
			}
			if (respawn >= 70)
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
			for (int i = 0; i < stars.size(); i++)
			{
				stars[i].move(0.0f, 0.8f + float(killCount / 100.0f));
			}
			for (int i = 0; i < enemies.size(); i++)
			{
				if (enemies[i].getColor() == sf::Color::Yellow)
				{
					enemies[i].move(0.0f, 0.8f + float(killCount / 150.0f));
				}
				else if (enemies[i].getColor() == sf::Color::Green)
				{
					enemies[i].move(0.0f, 0.5f + float(killCount / 250.0f));
				}
				else if (enemies[i].getColor() == sf::Color::Red)
				{
					enemies[i].move(0.0f, 0.3f + float(killCount / 350.0f));
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
							dead = i;
							hitcount = 0;
							enemies.erase(enemies.begin() + i);
						}

						projectiles.erase(projectiles.begin() + j);
						break;
					}
				}
			}

			animation_enemy.Update(0, deltaTime);
			animation_meteors.Update(0, deltaTime);
		}
		window.clear(sf::Color::Black);
		if (Is_Game_Start == 1)
		{

			for (int i = 0; i < stars.size(); i++)
			{
				window.draw(stars[i]);
			}
			for (int i = 0; i < 10; i++)
			{
				Star01[i].setTextureRect(animation_meteors.uvRect);
				window.draw(Star01[i]);
			}

			player.Draw(window);
			window.draw(Score);

			window.draw(Count);
			for (int i = 0; i < projectiles.size(); i++)
			{
				projectiles[i].DrawBullets(window);
			}
			for (int i = 0; i < enemies.size(); i++)
			{
				enemies[i].setTextureRect(animation_enemy.uvRect);
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
			window.draw(Pause);
		}
		else
		{
			if (Start.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Start.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					startGame = 1;
				}
			}
			else if (Quit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				Quit.setFillColor(sf::Color::Red);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					window.close();
				}
			}

			if (startGame == 1)
			{
				if (MainScreen.getPosition().x >= -(MainScreen.getSize().x))
				{
					MainScreen.setPosition((MainScreen.getPosition().x) - 50.5, MainScreen.getPosition().y);
				}
				else
				{
					Is_Game_Start = 1;
				}

			}
			window.draw(MainScreen);
			window.draw(Picture0);
			window.draw(GameTitle);
			window.draw(Start);
			window.draw(Quit);
		}
		
		window.display();
	}
}
