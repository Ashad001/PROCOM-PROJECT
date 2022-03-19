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
	player.setPosition(-50.0f, i_window.getSize().y - player_texture->getSize().y / 2 - 100);
	
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

void Player::MovePLayer(sf::RenderWindow &i_window)
{
	SetPlayerPosition(sf::Mouse::getPosition(i_window).x, player.getPosition().y);
	if (player.getPosition().x + 40 < 0)
	{
		SetPlayerPosition(-50.0f, i_window.getSize().y - player_texture->getSize().y / 2 - 100);
	}
	if (player.getPosition().x + player_texture->getSize().x + 350 >= i_window.getSize().x)
	{
		SetPlayerPosition(i_window.getSize().x - player_texture->getSize().x - 350, i_window.getSize().y - player_texture->getSize().y / 2 - 100);
	}
	SetHpBar(i_window);
}


void Player::SetHpBar(sf::RenderWindow &i_window)
{
	HPBar.setPosition(sf::Mouse::getPosition(i_window).x + 35, player.getPosition().y + 80);
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

