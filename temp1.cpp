#include <SFML/Graphics.hpp>
#include<vector>
#include <iostream>
#include "Bullet.h"
#include "Player.h"
#include <cstdlib>
using namespace std;

class LeftEnemy
{
	bool turn;
	int value;
public:
	sf::Sprite sprite;
	int getTurn()
	{
		return turn;
	}
	int getValue()
	{
		return value;
	}void setTurn(int a)
	{
		turn = a;
	}
	void setValue(int a)
	{
		value = a;
	}

	LeftEnemy()
	{
		turn = 0;
		value = 0;
	}
};

int main()
{
	//Window
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(780, 780), "Game");
	window.setFramerateLimit(60);

	int NumberOfAlighEnemies = 2;
	// Enemies 
	sf::Texture EnemyTexture;
	sf::Vector2u EnemySize = EnemyTexture.getSize();
	EnemyTexture.loadFromFile("Enemy.png");

	LeftEnemy* enemy01;
	enemy01 = new LeftEnemy[NumberOfAlighEnemies];

	int turningPointLeft = 15;
	for (int i = 0; i < NumberOfAlighEnemies; i++)
	{
		enemy01[i].sprite.setTexture(EnemyTexture);
		enemy01[i].sprite.setPosition(0 *2 *i, 0*i*2);
	}

	//vector<sf::Sprite> enemies;

	while (window.isOpen())
	{


		for (int i = 0; i < NumberOfAlighEnemies; i++)
		{
			if (enemy01[i].getValue() <= turningPointLeft)
			{
				if (enemy01[i].getTurn() == 0)
				{
					enemy01[i].sprite.setPosition(enemy01[i].sprite.getPosition().x+10, enemy01[i].sprite.getPosition().y + 1);
				}
				else
				{
					enemy01[i].sprite.setPosition(enemy01[i].sprite.getPosition().x - 10, enemy01[i].sprite.getPosition().y + 1);
				}
				enemy01[i].setValue(enemy01[i].getValue() + 1);
			}
			else
			{
				enemy01[i].setValue(0);
				enemy01[i].setTurn((enemy01[i].getTurn() == 1) ? 0 : 1);
				i--;
				continue;
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
		window.clear(sf::Color::Black);

		for (int i = 0; i < NumberOfAlighEnemies; i++)
		{
			window.draw(enemy01[i].sprite);

		}
		window.display();

	}
}
