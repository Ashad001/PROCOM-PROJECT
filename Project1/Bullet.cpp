#include <SFML/Graphics.hpp>
#include "Bullet.h"

Bullet::Bullet(float x, float y)
{
	SetBulletSize(x, y);
}
void Bullet::SetBulletSize(float x, float y)
{
	bullet1.setSize(sf::Vector2f(x, y));
}
void Bullet::SetBulletColor(sf::Color color)
{
	bullet1.setFillColor(color);
}
void Bullet::SetBulletPosition(float x, float y)
{
	bullet1.setPosition(sf::Vector2f(x, y));
}
sf::Vector2f Bullet::BulletPosition()
{
	return bullet1.getPosition();
}
void Bullet::MoveBullets(float x, float y)
{
	bullet1.move(sf::Vector2f(x, y));
}
sf::FloatRect Bullet::BulletGlobalBounds()
{
	return bullet1.getGlobalBounds();
}
void Bullet::DrawBullets(sf::RenderWindow& i_window)
{
	i_window.draw(bullet1);
}
