#include "BoidsManager.h"

#include <math.h>

#define PI 3.14159265359

float GetDistance(sf::Vector2f v1, sf::Vector2f v2) 
{
	return std::sqrt(v1.x * v2.x + v1.y * v2.y);
}

float GetMagnitude(sf::Vector2f v) 
{
	return std::sqrt(v.x * v.x + v.y * v.y);
}

void Normalize(sf::Vector2f &v) {v = v/ std::sqrt(v.x * v.x + v.y * v.y);}

BoidsManager::BoidsManager(sf::Vector2f screenSize)
{
	boidTexture.loadFromFile("assets/img/boid.png");
	windowSize = screenSize;
}

BoidsManager::BoidsManager(sf::Vector2f screenSize,unsigned int boidAmount) : BoidsManager(screenSize)
{
	for (size_t i = 0; i < boidAmount; i++)
	{
		AddBoid(); //sf::Color((255 * i)/boidAmount,255, 255,255)
	}
}

void BoidsManager::Update(double eTime)
{
	std::list<float>::iterator rotationIt = rotation.begin();
	for (std::list<sf::Vector2f>::iterator it = positions.begin(); it != positions.end(); it++,rotationIt++)
	{
		bool first = it == positions.begin();
		sf::Vector2f pos = *it;
		sf::Vector2f offset(0,0);
		for (std::list<sf::Vector2f>::iterator neighboorIt = positions.begin(); neighboorIt != positions.end(); neighboorIt++)
		{
			if (*it == *neighboorIt )continue;
			sf::Vector2f dir = *neighboorIt - *it;
			float dist = GetMagnitude(dir);
			dir /= dist;
			if (dist > cohesionRange)continue;
			if (dist > alignRange) offset += dir;
			else if (dist < separationRange) 
				offset -= dir;

		}

		if (offset != sf::Vector2f(0, 0) && first) {
			float dot = offset.x * 0 + offset.y * 1; //Dot product : Ax*Bx + Ay*By
			float offsetAngle = std::acos(dot / std::abs(GetMagnitude(offset)*1)); // angle : cos 0 = A.B/|A|*|B| => 0 = acos("")
			//offsetAngle = std::acos(offset.x);
			offsetAngle = offsetAngle * 180 / PI; // Radian to Degrees
			float leftAngle = *rotationIt - offsetAngle ;
			if (leftAngle < 0)leftAngle += 360;

			offsetAngle = eTime * 0.0001f * (leftAngle < 180 ? -1 : 1);
			*rotationIt += offsetAngle;
		}
		

		float theta = *rotationIt * PI / 180;
		pos += sf::Vector2f(std::cos(theta), std::sin(theta))*(float)(eTime*0.00003f);
		if (pos.x > windowSize.x)pos.x -= windowSize.x;
		if (pos.y > windowSize.y)pos.y -= windowSize.y;
		if (pos.x < 0) pos.x += windowSize.x;
		if (pos.y < 0) pos.y += windowSize.y;
		*it = pos;
		*rotationIt = fmod(*rotationIt, 360);
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

void BoidsManager::AddBoid(sf::Color col) {
	positions.push_back(sf::Vector2f((rand() % (int)windowSize.x), rand() % (int)windowSize.y));
	rotation.push_back(rand() % 360);
	sf::Sprite* _sprite = new sf::Sprite();
	_sprite->setTexture(boidTexture);
	_sprite->setScale(0.005f, 0.005f);

	_sprite->setColor(col);

	float offsetX = boidTexture.getSize().x / 2;
	float offsetY = boidTexture.getSize().y / 2;
	_sprite->setOrigin(offsetX, offsetY);
	sprites.push_back(_sprite);
}

void BoidsManager::AddBoid()
{
	AddBoid(sf::Color::White);
}

