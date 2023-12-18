#pragma once

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

class BoidsManager
{
public :

	BoidsManager(sf::Vector2f screenSize);

	BoidsManager(sf::Vector2f screenSize,unsigned int boidAmount);

	void Update(double eTime);
	void Display(sf::RenderWindow& window);

	void AddBoid();
private :
	float cohesionRange = 100;
	float alignRange = 50;
	float separationRange = 40;


	sf::Vector2f windowSize;

	std::list<sf::Sprite*> sprites;
	std::list<sf::Vector2f> positions;
	std::list<float> rotation;

	sf::Texture boidTexture;

	void AddBoid(sf::Color col);
};

