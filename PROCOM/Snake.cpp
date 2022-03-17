/*
#include "Snake.h"
#include <SFML/Graphics.hpp>

Snake::Snake(int l_blocksize)
{
	m_size = l_blocksize;
	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	Reset();
}
Snake::~Snake()
{}

void Snake::Reset()
{
	m_snakeBody.clear();
	
	m_snakeBody.push_back(SnakeSegment(5, 7));
	m_snakeBody.push_back(SnakeSegment(5, 6));
	m_snakeBody.push_back(SnakeSegment(5, 5));

	SetDirection(Direction::None);
	m_speed = 15;
	m_lives = 3;
	m_score = 0;
	m_lost = false;
}
void Snake::SetDirection(Direction l_dir)
{
	m_dir = l_dir;
}
Direction Snake::GetDirection()
{
	return m_dir;
}
int Snake::GetSpeed() 
{ 
	return m_speed;
}

sf::Vector2i Snake::GetPosition()
{

}
int Snake::GetLives() 
{ 
	return m_lives;
}
int Snake::GetScore() 
{
	return m_score; 
}
void Snake::IncreaseScore() 
{
	m_score += 10; 
}
bool Snake::HasLost()
{
	return m_lost; 
}
void Snake::Lose() 
{
	m_lost = true; 
}
void Snake::ToggleLost()
{
	m_lost = !m_lost;
}
*/