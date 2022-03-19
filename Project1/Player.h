#pragma once
class Player
{
private:	
	sf::Sprite player;
	sf::Texture *player_texture;
	sf::RectangleShape HPBar;
	int HP;
	int MaxHP;
public:
	Player(sf::RenderWindow &i_window,sf::Texture *tex , int Maxhp);
	sf::Vector2u GetPlayerSize();
	sf::Vector2f GetPlayerCentre();
	sf::Vector2f GetPlayerPosition();
	sf::FloatRect GetGlobalBounds();
	void SetPlayerPosition(float x, float y);
	void MovePLayer(sf::RenderWindow &i_window);
	void SetHpBar(sf::RenderWindow &i_window);
	void Shoot(sf::RenderWindow& i_window);
	void SetHpBarSize();
	void Draw(sf::RenderWindow &i_window);
	void DrawHp(sf::RenderWindow& i_window);
	int GetHp();
	void SetHP(int x);
	

};

