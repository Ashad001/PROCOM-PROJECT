#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
#include "Bullet.h"
using namespace std;

Player::Player(sf::RenderWindow& i_window, sf::Texture* tex, int MaxHp = 10)
{
	this->player_texture = tex;
	this->player.setTexture(*tex);
	this->MaxHP = MaxHp;
	this->HP = this->MaxHP;
	HPBar.setFillColor(sf::Color::Blue);
	HPBar.setSize(sf::Vector2f(HP * 5.0f, 7.0f));
	HPBar.setPosition(player.getPosition().x + 50, player.getPosition().y + 90);
	player.setPosition(i_window.getSize().x / 3, i_window.getSize().y - player_texture->getSize().y / 2 - 100);
}

sf::Vector2u Player::GetPlayerSize()
{
	return player_texture->getSize();
}

sf::Vector2f Player::GetPlayerCentre()
{
	return sf::Vector2f(player.getPosition().x + 75.0f, player.getPosition().y + 30);
}

void Player::SetPlayerPosition(float x, float y)
{
	player.setPosition(sf::Vector2f(x, y));
}

sf::Vector2f Player::GetPlayerPosition()
{
	return player.getPosition();
}

void Player::MovePLayer(sf::RenderWindow &i_window , float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.move(0.0f, -0.4f * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.move(0.0f, 0.4f * deltaTime);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player.move(- 0.4f * deltaTime, 0.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player.move(0.4f * deltaTime, 0.0f);
	}
	if (player.getPosition().x < 0)
	{
		player.setPosition(0.0f, player.getPosition().y);
	}
	if (player.getPosition().x + 470 > i_window.getSize().x)
	{
		player.setPosition(i_window.getSize().x - 470, player.getPosition().y );
	}
	if (player.getPosition().y - 250 < 0)
	{
		player.setPosition(player.getPosition().x , 250);
	}
	if (player.getPosition().y + 150 > i_window.getSize().y)
	{
		player.setPosition(player.getPosition().x,i_window.getSize().y - 150);
	}
	


	SetHpBar(i_window);
	SetHpBarSize();
}


void Player::SetHpBar(sf::RenderWindow &i_window)
{
	HPBar.setPosition(player.getPosition().x  + player.getGlobalBounds().width / 4.0f, player.getPosition().y + player.getGlobalBounds().height / 0.9f);
	if (HPBar.getPosition().x < 0)
	{
		HPBar.setPosition(0.0f, HPBar.getPosition().y);
	}
	if (HPBar.getPosition().x + HPBar.getSize().x - 230 > i_window.getSize().y)
	{
		HPBar.setPosition(i_window.getSize().x - HPBar.getSize().x - 370, HPBar.getPosition().y);
	}
}

sf::FloatRect Player::GetGlobalBounds()
{
	return player.getGlobalBounds();
}


void Player::SetHpBarSize()
{
	HPBar.setSize(sf::Vector2f(HP * 5.0f, 7.0f));
}


void Player::Draw(sf::RenderWindow& i_window)
{
	i_window.draw(player);
}


void Player::DrawHp(sf::RenderWindow& i_window)
{
	i_window.draw(HPBar);
}


int Player::GetHp()
{
	return HP;
}


void Player::SetHP(int x)
{
	this->HP = x;
}

