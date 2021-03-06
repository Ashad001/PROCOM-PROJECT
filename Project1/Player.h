#pragma once
class Player
{
private:	
	sf::Sprite player;
	sf::Texture *player_texture;
	sf::RectangleShape HPBar;
	int HP;
	int MaxHP;
	sf::RectangleShape bullet_in;
public:
	Player(sf::RenderWindow &i_window,sf::Texture *tex , int Maxhp);
	void SetPlayer(sf::RenderWindow& i_window, sf::Texture* tex, int max);
	sf::Vector2u GetPlayerSize();
	sf::Vector2f GetPlayerCentre();
	sf::Vector2f GetPlayerPosition();
	sf::FloatRect GetGlobalBounds();
	void SetPlayerPosition(float x, float y);
	void SetPlayerInitialPosition(sf::RenderWindow& i_window, sf::Texture* tex);
	void MovePLayer(sf::RenderWindow &i_window, float deltaTime);
	void SetHpBar(sf::RenderWindow &i_window);
	void Shoot(sf::RenderWindow& i_window);
	void SetHpBarSize();
	void Draw(sf::RenderWindow &i_window);
	void DrawHp(sf::RenderWindow& i_window);
	int GetHp();
	void SetHP(int x);
	int GetMaxHp();
	void SetTextureRect(sf::IntRect &i_body);

};

