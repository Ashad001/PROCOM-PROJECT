#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include<vector>
#include "Bullet.h"
#include "Player.h"
#include "Animation.h"
using namespace std;


int main()
{
	int Is_Game_Start = 0;
	int startGame = 0;
	int Is_Game_Pause = 0;
	int HighScorePanel = 0;
	int HighScoresOfPlayers[10] = { 0 }, countOfScores = 10;

	// Reading Data of scores from file.
	fstream HighScoresFile;
	HighScoresFile.open("High Scores.txt", ios::in);
	if (!HighScoresFile)
	{
		cout << "Unable to open the High Scores file" << endl;
	}
	int Temp_Score;
	for (int i = 0; HighScoresFile >> Temp_Score; i++)
	{
		HighScoresOfPlayers[i] = Temp_Score;
	}
	HighScoresFile.close();
	// Arranging in Desending order
	for (int i = 0; i < countOfScores; i++)
	{
		for (int j = i; j < countOfScores; j++)
		{
			if (HighScoresOfPlayers[j] > HighScoresOfPlayers[i])
			{
				HighScoresOfPlayers[j] += HighScoresOfPlayers[i];
				HighScoresOfPlayers[i] = HighScoresOfPlayers[j] - HighScoresOfPlayers[i];
				HighScoresOfPlayers[j] = HighScoresOfPlayers[j] - HighScoresOfPlayers[i];
			}
		}
	}

	//Window
	srand(time(NULL));
	// sf::RenderWindow window(sf::VideoMode(700, 700), "Game");
	sf::RenderWindow window(sf::VideoMode(1380, 780), "Game", sf::Style::Fullscreen);
	window.setFramerateLimit(60);

	// DINEHS WORK 2
	sf::RectangleShape HighScoresScreen(sf::Vector2f(window.getSize()));
	HighScoresScreen.setFillColor(sf::Color::Black);

	sf::RectangleShape MainScreen(sf::Vector2f(window.getSize()));
	MainScreen.setFillColor(sf::Color(13, 13, 13));

	sf::Texture EarthTexture;
	EarthTexture.loadFromFile("try.png");
	EarthTexture.setSmooth(true);
	sf::Sprite Picture0;
	Picture0.setTexture(EarthTexture);
	Picture0.setScale(2.f, 2.f);
	Picture0.setOrigin(EarthTexture.getSize().x / 2.0, EarthTexture.getSize().y / 2.0);

	sf::Text GameTitle;
	sf::Font TitleFont;
	TitleFont.loadFromFile("Bungee-Regular.ttf");

	GameTitle.setFont(TitleFont);
	GameTitle.setString("Space War");
	GameTitle.setCharacterSize(MainScreen.getSize().y / 6.0);
	GameTitle.setOrigin(GameTitle.getGlobalBounds().width / 2.f, (GameTitle.getGlobalBounds().height / 2.f) + GameTitle.getGlobalBounds().height);
	GameTitle.setStyle(sf::Text::Bold);

	sf::Text Start;
	Start.setFont(TitleFont);
	Start.setString("START");
	Start.setCharacterSize(MainScreen.getSize().y / 20.0);
	Start.setOrigin(Start.getGlobalBounds().width / 2.f, (Start.getGlobalBounds().height / 2.f) - GameTitle.getGlobalBounds().height);
	Start.setStyle(sf::Text::Bold);
	Start.setOutlineThickness(3);

	sf::Text Pause;
	Pause.setFont(TitleFont);
	Pause.setString("PAUSE[P]");
	Pause.setCharacterSize(MainScreen.getSize().y / 25.0);
	Pause.setPosition(window.getSize().x - 210, 500);
	Pause.setStyle(sf::Text::Bold);
	Pause.setOutlineThickness(3);


	sf::Text Quit;
	Quit.setFont(TitleFont);
	Quit.setString("QUIT");
	Quit.setCharacterSize(MainScreen.getSize().y / 20.0);
	Quit.setOrigin(Quit.getGlobalBounds().width / 2.f, Quit.getGlobalBounds().height / 2.f);
	Quit.setStyle(sf::Text::Bold);
	Quit.setOutlineThickness(3);


	sf::Text Restart;
	Restart.setFont(TitleFont);
	Restart.setString("PLAY AGAIN");
	Restart.setCharacterSize(MainScreen.getSize().y / 20.0);
	Restart.setOrigin(Restart.getGlobalBounds().width / 2.f, Restart.getGlobalBounds().height / 2.f);
	Restart.setStyle(sf::Text::Bold);
	Restart.setOutlineThickness(3);

	sf::Text HighScores;
	HighScores.setFont(TitleFont);
	HighScores.setString("HIGH SCORES");
	HighScores.setCharacterSize(MainScreen.getSize().y / 20.0);
	HighScores.setOrigin(HighScores.getGlobalBounds().width / 2.f, HighScores.getGlobalBounds().height / 2.f);
	HighScores.setStyle(sf::Text::Bold);
	HighScores.setOutlineThickness(3);

	sf::SoundBuffer buffer;
	buffer.loadFromFile("shoot.wav");
	sf::Sound Shoot;
	Shoot.setBuffer(buffer);
	Shoot.setVolume(20.f);

	sf::SoundBuffer buffer_Select;
	buffer_Select.loadFromFile("Select.wav");
	sf::Sound Select;
	Select.setBuffer(buffer_Select);
	Select.setVolume(20.f);
	
	sf::Music Intro;
	Intro.openFromFile("Intro.ogg");
	Intro.setVolume(20.f);
	Intro.play();
	Intro.setLoop(1);

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
	PlayerTexture.loadFromFile("Plane4.png");
	Player player(window, &PlayerTexture, 12);
	Animation animation_player(&PlayerTexture, sf::Vector2u(5, 1), 40);

	// Enemies 
	sf::Texture EnemyTexture;
	EnemyTexture.loadFromFile("Enemy4.png");
	sf::Sprite enemy(EnemyTexture);
	sf::Vector2u EnemySize = EnemyTexture.getSize();
	enemy.setScale(1.f, 1.f);
	vector<sf::Sprite> enemies;
	Animation animation_enemy(&EnemyTexture, sf::Vector2u(3, 2), 300);

	// Powerups
	sf::Texture HeartTexture;
	HeartTexture.loadFromFile("Heart.png");
	sf::Sprite Heart;
	Heart.setTexture(HeartTexture);
	vector< sf::Sprite> Hearts;
	Animation animaion_hearts(&HeartTexture, sf::Vector2u(4, 1), 100);

	sf::Texture AmnoTexture;
	AmnoTexture.loadFromFile("Amno.png");
	sf::Sprite Amno;
	Amno.setTexture(AmnoTexture);
	Amno.setScale(2.f, 2.f);
	vector<sf::Sprite> Amnos;
	Animation animation_amno(&AmnoTexture, sf::Vector2u(3, 1), 100);

	// GameOver
	sf::Font font;
	font.loadFromFile("Font.ttf");
	sf::Text GameOver;
	GameOver.setFont(font);
	GameOver.setString("Game Over");
	GameOver.setCharacterSize(30);
	GameOver.setPosition(window.getSize().x / 2 - 80, window.getSize().y / 2 - 150);
	GameOver.setFillColor(sf::Color::White);
	GameOver.setOutlineThickness(2);
	GameOver.setOutlineColor(sf::Color::Red);

	//Score
	sf::Text Score;
	Score.setFont(TitleFont);
	Score.setString("SCORE");
	Score.setCharacterSize(MainScreen.getSize().y / 25.0);
	Score.setPosition(window.getSize().x - 245, 200);
	Score.setFillColor(sf::Color::White);
	Score.setOutlineThickness(3);
	Score.setOutlineColor(sf::Color::Blue);

	// Kill Count
	int killCount = 0;
	sf::Text Count;
	Count.setFont(TitleFont);
	Count.setString(to_string(killCount));
	Count.setCharacterSize(MainScreen.getSize().y / 25.0);
	Count.setPosition(window.getSize().x - 205.f, 250);
	Count.setFillColor(sf::Color::White);
	Count.setOutlineThickness(1);
	Count.setOutlineColor(sf::Color::Blue);


	int shootCounter = 0;
	int respawn = 0;
	int hitcount = 0;
	int hit = 0;
	float enemy_pos_x = 0.f, enemy_pos_y = 0.f;
	string Power = "1212121212333451";
	int powerCounter = 0;
	int kill;
	int dead1 = -1, dead2 = -1;
	int StarCount = 0;
	int Heart_Move = 0;
	int bullet_strength = 1;
	int is_dead[500];
	int pos = 0;
	for (int i = 0; i < 500; i++)
	{
		is_dead[i] = 0;
	}

	while (window.isOpen())
	{
		Pause.setFillColor(sf::Color::White);
		Pause.setOutlineColor(sf::Color::Blue);
		Restart.setFillColor(sf::Color::White);
		Restart.setOutlineColor(sf::Color::Blue);
		GameTitle.setFillColor(sf::Color::White);
		Start.setFillColor(sf::Color::White);
		Start.setOutlineColor(sf::Color::Blue);
		HighScores.setFillColor(sf::Color::White);
		HighScores.setOutlineColor(sf::Color::Blue);
		Quit.setFillColor(sf::Color::White);
		Quit.setOutlineColor(sf::Color::Blue);

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
			if (shootCounter < 12)
			{
				shootCounter++;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && shootCounter >= 12 && Is_Game_Start == 1)
			{
				playerShoot.SetBulletPosition(player.GetPlayerCentre().x - 56.0f, player.GetPlayerCentre().y - 20.0f);
				projectiles.push_back(Bullet(playerShoot));
				playerShoot.SetBulletPosition(player.GetPlayerCentre().x + 34.0f, player.GetPlayerCentre().y - 20.0f);
				projectiles.push_back(Bullet(playerShoot));

				Shoot.play();

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
			if (respawn < 90 - killCount / 20.f)
			{
				respawn++;
			}
			if (respawn + killCount / 20.f >= 90)
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
				else if (Power[powerCounter] == '4' && killCount >= 20 * player.GetHp())
				{
					enemy.setColor(sf::Color::Cyan);
				}
				else if (Power[powerCounter] == '5' && killCount >= 70 * bullet_strength)
				{
					enemy.setColor(sf::Color::Magenta);
				}
				powerCounter++;
				if (powerCounter >= Power.size() - 1)
				{
					powerCounter = 0;
				}
				if (Is_Game_Start == 1)
				{
					enemy.setPosition((rand() % (int)(window.getSize().x - EnemySize.x * 2 - 330)), 0.0f);
					enemies.push_back(sf::Sprite(enemy));
				}
			}
			for (int i = 0; i < stars.size(); i++)
			{
				stars[i].move(0.0f, 0.8f + float(killCount / 100.0f));
				if (stars[i].getPosition().y > window.getSize().y)
				{
					stars.erase(stars.begin() + i);
				}
			}
			for (int i = 0; i < enemies.size() && Is_Game_Start == 1; i++)
			{
				if (enemies[i].getColor() == sf::Color::Yellow)
				{
					enemies[i].move(0.0f, (0.7f + float(killCount / 150.0f)));
				}
				else if (enemies[i].getColor() == sf::Color::Green)
				{
					enemies[i].move(0.0f, (0.5f + float(killCount / 250.0f)));
				}
				else if (enemies[i].getColor() == sf::Color::Red)
				{
					enemies[i].move(0.0f, (0.3 + float(killCount / 350.0f)));
				}
				else if (enemies[i].getColor() == sf::Color::Cyan)
				{
					enemies[i].move(0.0f, (0.9 + float(killCount / 150.0f)));
				}
				else if (enemies[i].getColor() == sf::Color::Magenta)
				{
					enemies[i].move(0.0f, 0.9f + float(killCount / 150.0f));
				}
				if (enemies[i].getPosition().y <= 0)
				{
					enemies.erase(enemies.begin() + i);
				}
				if (enemies[i].getPosition().y + 50 > window.getSize().y)
				{
					enemies.erase(enemies.begin() + i);
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
						hitcount += bullet_strength;
						if (enemies[i].getColor() == sf::Color::Yellow)
						{
							hit = 2;
							kill = 1;
						}
						else if (enemies[i].getColor() == sf::Color::Green)
						{
							hit = 4;
							kill = 2;
						}
						else if (enemies[i].getColor() == sf::Color::Red)
						{
							hit = 7;
							kill = 4;
						}
						else if (enemies[i].getColor() == sf::Color::Cyan)
						{
							hit = 2;
							kill = 5;
						}
						else if (enemies[i].getColor() == sf::Color::Magenta)
						{
							hit = 2;
							kill = 5;
						}
						if (hitcount >= hit)
						{
							killCount += kill;
							hitcount = 0;
							if (enemies[i].getColor() == sf::Color::Cyan)
							{
								dead1++;
								Heart.setPosition(enemies[i].getPosition());
								enemies.erase(enemies.begin() + i);
							}
							else if (enemies[i].getColor() == sf::Color::Magenta)
							{
								dead2++;
								Amno.setPosition(enemies[i].getPosition());
								enemies.erase(enemies.begin() + i);
							}
							else
							{
								enemies.erase(enemies.begin() + i);
							}
						}
						if (hitcount >= hit)
						{
							killCount += kill;
							hitcount = 0;
							if (enemies[i].getColor() == sf::Color::Cyan)
							{
								dead1++;
								Heart.setPosition(enemies[i].getPosition());
							}
							else if (enemies[i].getColor() == sf::Color::Magenta)
							{
								dead2++;
								Amno.setPosition(enemies[i].getPosition());
							}
							is_dead[pos] = i;
							pos++;
						}

						projectiles.erase(projectiles.begin() + j);
						break;
					}
				}
			}
			if (dead1 != -1)
			{
				Hearts.push_back(sf::Sprite(Heart));
				dead1 = -1;
			}
			for (int i = 0; i < Hearts.size(); i++)
			{
				Hearts[i].move(0.0f, 0.9f + float(killCount / 100.f));
				if (player.GetGlobalBounds().intersects(Hearts[i].getGlobalBounds()))
				{
					Hearts.erase(Hearts.begin() + i);
					player.SetHP(player.GetMaxHp());
				}
			}
			if (dead2 != -1)
			{
				Amnos.push_back(sf::Sprite(Amno));
				dead2 = -1;
			}
			for (int i = 0; i < Amnos.size(); i++)
			{
				Amnos[i].move(0.0f, 0.9f + float(killCount / 100.f));
				if (player.GetGlobalBounds().intersects(Amnos[i].getGlobalBounds()))
				{
					bullet_strength++;
					Amnos.erase(Amnos.begin() + i);
				}
			}

			//animations
			animation_player.Update(0, deltaTime);
			animation_meteors.Update(0, deltaTime);
			animaion_hearts.Update(0, deltaTime);
			animation_amno.Update(0, deltaTime);
			animation_enemy.Update(0, deltaTime);
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
			player.SetTextureRect(animation_player.uvRect);
			player.Draw(window);
			window.draw(Score);

			for (int i = 0; i < Hearts.size(); i++)
			{
				Hearts[i].setTextureRect(animaion_hearts.uvRect);
				window.draw(Hearts[i]);
			}
			for (int i = 0; i < Amnos.size(); i++)
			{
				Amnos[i].setTextureRect(animation_amno.uvRect);
				window.draw(Amnos[i]);
			}
			window.draw(Count);
			for (int i = 0; i < projectiles.size(); i++)
			{
				projectiles[i].DrawBullets(window);
			}
			if (Is_Game_Start == 1)
			{
				for (int i = 0; i < enemies.size(); i++)
				{
					enemies[i].setTextureRect(animation_enemy.uvRect);
					window.draw(enemies[i]);
				}
			}
			player.DrawHp(window);
			if (player.GetHp() <= 0)
			{
				for (int i = 0; i < enemies.size(); i++)
				{
					enemies.erase(enemies.begin() + i);
				}
				for (int i = 0; i < projectiles.size(); i++)
				{
					projectiles.erase(projectiles.begin() + i);
				}
				for (int i = 0; i < stars.size(); i++)
				{
					stars.erase(stars.begin() + i);
				}

				// Writing New High Scores
				HighScoresFile.open("High Scores.txt", ios::out);
				if (!HighScoresFile)
				{
					cout << "Unable to open the High Scores file" << endl;
				}
				int something = killCount;
				for (int i = 0; i < countOfScores; i++)
				{
					if (something > HighScoresOfPlayers[i])
					{
						int* temp = new int;
						*temp = HighScoresOfPlayers[i];
						HighScoresOfPlayers[i] = something;
						something = *temp;
						delete temp;
					}
					else if (something == HighScoresOfPlayers[i])
					{
						break;
					}
				}

				for (int i = 0; i < countOfScores; i++)
				{
					HighScoresFile << HighScoresOfPlayers[i] << endl;
				}
				HighScoresFile.close();

				Count.setString(to_string(killCount));
				Score.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2);
				Count.setPosition(window.getSize().x / 2 - 25, window.getSize().y / 2 + 50);
				GameTitle.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0);
				Picture0.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2, MainScreen.getPosition().y + MainScreen.getSize().y / 2);
				Start.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0);
				Quit.setPosition(MainScreen.getSize().x / 2.f, MainScreen.getSize().y / 2 + 200);
				Restart.setPosition(MainScreen.getSize().x / 2.f, MainScreen.getSize().y / 2 + 150.f);

				if (!(Restart.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) || (Quit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))))
				{
					Select.play();
				}

				if (Restart.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					Restart.setFillColor(sf::Color::Blue);
					Restart.setOutlineColor(sf::Color::White);
					Restart.setPosition(Restart.getPosition().x, Restart.getPosition().y - 5);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						player.SetPlayer(window, &PlayerTexture, player.GetMaxHp());
						shootCounter = 0;
						respawn = 0;
						hitcount = 0;
						hit = 0;
						powerCounter = 0;
						kill = 0;
						dead1 = -1;
						dead2 = -1;
						StarCount = 0;
						bullet_strength = 1;
						Score.setPosition(window.getSize().x - 230, 200);
						Count.setPosition(window.getSize().x - 180, 250);
						player.SetPlayerInitialPosition(window, &PlayerTexture);
						killCount = 0;

						startGame = 0;
					}
				}


				if (Quit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					Quit.setFillColor(sf::Color::Blue);
					Quit.setOutlineColor(sf::Color::White);
					Quit.setPosition(Quit.getPosition().x, Quit.getPosition().y - 5);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						window.close();
					}
				}
				window.clear(sf::Color::Black);
				window.draw(GameOver);
				window.draw(Score);
				window.draw(Count);
				window.draw(Quit);
				window.draw(Restart);
			}
		}
		else if (HighScorePanel == 1)
		{
			int SpaceHaiYaarScoreKBachKa = 50;

			sf::Text* Back;
			Back = new sf::Text;
			Back->setString("BACK [Enter]");
			Back->setFont(TitleFont);
			Back->setCharacterSize(MainScreen.getSize().y / 40.0);
			Back->setOrigin(Back->getGlobalBounds().width / 2.0, Back->getGlobalBounds().height / 2.0);
			Back->setPosition(window.getSize().x / 2.0, window.getSize().y * 0.95);
			Back->setStyle(sf::Text::Bold);
			Back->setFillColor(sf::Color::White);
			Back->setOutlineColor(sf::Color::Blue);
			Back->setOutlineThickness(3);

			HighScoresScreen.setFillColor(sf::Color(255, 255, 0, 0));
			HighScores.setPosition(window.getSize().x / 2.0, window.getSize().y * 0.15);

			sf::Text* Temp;
			Temp = new sf::Text;
			Temp->setFont(TitleFont);
			Temp->setCharacterSize(MainScreen.getSize().y / 30.0);
			Temp->setOrigin(Temp->getGlobalBounds().width / 2.0, Temp->getGlobalBounds().height / 2.0);
			Temp->setStyle(sf::Text::Bold);
			Temp->setFillColor(sf::Color::White);
			Temp->setOutlineColor(sf::Color::Blue);
			Temp->setOutlineThickness(3);


			for (int i = 0; i < countOfScores; i++)
			{
				Temp->setString(to_string(HighScoresOfPlayers[i]));
				Temp->setPosition(window.getSize().x / 2.0, HighScores.getPosition().y + SpaceHaiYaarScoreKBachKa);
				window.draw(*Temp);
				SpaceHaiYaarScoreKBachKa += 50;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				Back->setFillColor(sf::Color::Blue);
				Back->setOutlineColor(sf::Color::White);
				HighScorePanel = 0;
				delete Back;
				delete Temp;
			}
			// It was creating problem if i delete it then tried to draw it.
			if (HighScorePanel == 1)
			{
				window.draw(*Back);
			}

			window.draw(HighScores);
			window.draw(HighScoresScreen);
		}
		else
		{
			//Intro.play();
			GameTitle.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0);
			Picture0.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2, MainScreen.getPosition().y + MainScreen.getSize().y / 2);
			Start.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0);
			HighScores.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0 + GameTitle.getGlobalBounds().height + Start.getGlobalBounds().height + HighScores.getGlobalBounds().height);
			Quit.setPosition(MainScreen.getPosition().x + MainScreen.getSize().x / 2.0, MainScreen.getPosition().y + MainScreen.getSize().y / 2.0 + GameTitle.getGlobalBounds().height + Start.getGlobalBounds().height + HighScores.getGlobalBounds().height + Quit.getGlobalBounds().height + 30);

			if (!(Start.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) || Quit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))) || HighScores.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))))
			{
				Select.play();
			}

			if (Start.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				
				Start.setFillColor(sf::Color::Blue);
				Start.setOutlineColor(sf::Color::White);
				Start.setPosition(Start.getPosition().x, Start.getPosition().y - 5);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					startGame = 1;
				}
			}
			else if (HighScores.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
			
				HighScores.setFillColor(sf::Color::Blue);
				HighScores.setOutlineColor(sf::Color::White);
				HighScores.setPosition(HighScores.getPosition().x, HighScores.getPosition().y - 5);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					HighScorePanel = 1;
				}
			}
			else if (Quit.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
		
				Quit.setFillColor(sf::Color::Blue);
				Quit.setOutlineColor(sf::Color::White);
				Quit.setPosition(Quit.getPosition().x, Quit.getPosition().y - 5);
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
			window.draw(HighScores);
			window.draw(Quit);
		}

		window.display();
	}
}
