#include "Ball.hpp"

Ball::Ball(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;
	m_Shape.setRadius(10);
	m_Shape.setPosition(m_Position);
}
FloatRect Ball::getPositon()
{
	return m_Shape.getGlobalBounds();
}

CircleShape Ball::getShape()
{
	return m_Shape;
}
void Ball::reboundSides()
{
	m_DirectionX = -m_DirectionX;
}

void Ball::reboundBatOrTop()
{
	m_DirectionY = -m_DirectionY;
}

void Ball::reboundBottom()
{
	m_Position.y = 11;
	m_Position.x = 500;

}

void Ball::update(Time dt)
{
	m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();
	m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
	m_Shape.setPosition(m_Position);
}