#pragma once
class Bullet
{
private:
	sf::RectangleShape bullet1;
	float size_x, size_y;
	float pos_x, pos_y;
public:
	Bullet(float x, float y);
	void SetBulletSize(float x, float y);
	void SetBulletColor(sf::Color color);
	void SetBulletPosition(float x, float y);
	sf::Vector2f BulletPosition();
	void MoveBullets(float x, float y);
	sf::FloatRect BulletGlobalBounds();
	void DrawBullets(sf::RenderWindow& i_window);
};

