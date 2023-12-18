#include "BoidsManager.h"

#define PI 3.14159265359

float GetDistance(sf::Vector2f v1, sf::Vector2f v2) 
{
	return std::sqrt(v1.x * v2.x + v1.y * v2.y);
}

float GetMagnitude(sf::Vector2f v) 
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

BoidsManager::BoidsManager(sf::Vector2f screenSize)
{
	boidTexture.loadFromFile("assets/img/boid.png");
	windowSize = screenSize;
}

BoidsManager::BoidsManager(sf::Vector2f screenSize,unsigned int boidAmount) : BoidsManager(screenSize)
{
	for (size_t i = 0; i < boidAmount; i++)
	{
		AddBoid();
	}
}

void BoidsManager::Update(double eTime)
{
	std::list<float>::iterator rotationIt = rotation.begin();
	for (std::list<sf::Vector2f>::iterator it = positions.begin(); it != positions.end(); it++,rotationIt++)
	{
		float theta = *rotationIt * PI / 180;
		sf::Vector2f pos = *it;
		sf::Vector2f offset(0,0);
		for (std::list<sf::Vector2f>::iterator neighboorIt = positions.begin(); neighboorIt != positions.end(); neighboorIt++)
		{
			sf::Vector2f dir = *neighboorIt - *it;
			float dist = GetMagnitude(dir);
			dir /= dist;
			if (dist > cohesionRange)continue;
			if (dist > alignRange) {

			}
		}
		pos += sf::Vector2f(std::cos(theta), std::sin(theta))*(float)(eTime*0.0001f);
		if (pos.x > windowSize.x)pos.x -= windowSize.x;
		if (pos.y > windowSize.y)pos.y -= windowSize.y;
		if (pos.x < 0) pos.x += windowSize.x;
		if (pos.y < 0) pos.y += windowSize.y;
		*it = pos;
	}
}

void BoidsManager::Display(sf::RenderWindow& window)
{
	std::list<sf::Vector2f>::iterator positionIt = positions.begin();
	std::list<float>::iterator rotationIt = rotation.begin();
	for (sf::Sprite* sprite:sprites)
	{
		sprite->setPosition(*positionIt);
		sprite->setRotation(*rotationIt);
		window.draw(*sprite);
		positionIt++,rotationIt++;
	}
}

void BoidsManager::AddBoid()
{
	positions.push_back(sf::Vector2f((rand()%(int)windowSize.x), rand()%(int)windowSize.y));
	rotation.push_back(rand() % 360);
	sf::Sprite *_sprite = new sf::Sprite();
	_sprite->setTexture(boidTexture);
	_sprite->setScale(0.005f, 0.005f);
	float offsetX = boidTexture.getSize().x / 2;
	float offsetY = boidTexture.getSize().y / 2;
	_sprite->setOrigin(offsetX, offsetY);
	sprites.push_back(_sprite);
}
