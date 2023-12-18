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
	float cohesionRange = 150;
	float alignRange = 80;
	float separationRange = 40;


	sf::Vector2f windowSize;

	std::list<sf::Sprite*> sprites;
	std::list<sf::Vector2f> positions;
	std::list<float> rotation;

	sf::Texture boidTexture;
};

