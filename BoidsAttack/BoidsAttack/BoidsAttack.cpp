#include <SFML/Graphics.hpp>

#include "BoidsManager.h"

sf::Clock _clock;

// La premiere est bien mieux 1.4 sec au lieux de 6 sec 
//#define AMOUNT 50000000
//float rdm1[AMOUNT];
//sf::Vector2f results1[AMOUNT];
//sf::Vector2f rdm2[AMOUNT];
//float results2[AMOUNT];
//
//void TestPerf() {
//    for (size_t i = 0; i < AMOUNT; i++)
//    {
//        rdm1[i] = rand() % 360;
//    }
//    _clock.restart();
//
//    for (size_t i = 0; i < AMOUNT; i++)
//    {
//        float theta = rdm1[i] * PI/180;
//        results1[i] = sf::Vector2f(std::cos(theta), std::sin(theta));
//    }
//    std::cout << "First Time :" << _clock.getElapsedTime().asSeconds() << std::endl;
//    _clock.restart();
//    for (size_t i = 0; i < AMOUNT; i++)
//    {
//        
//        rdm2[i] = sf::Vector2f(rand()%1, rand() % 1);
//    }
//    for (size_t i = 0; i < AMOUNT; i++)
//    {
//        results2[i] = std::atan2(std::sin(rdm2[i].y), std::cosl(rdm2[i].x));
//    }
//    std::cout << "Second Time :" << _clock.getElapsedTime().asSeconds() << std::endl;
//
//
//}

int main()
{

    float screenScale = 30;
    sf::Vector2f screenSize(16 * screenScale, 9 * screenScale);

    sf::RenderWindow window(sf::VideoMode(screenSize.x, screenSize.y), "SFML works!");

    BoidsManager bm(screenSize, 500);
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) 
                window.close();
        }
        window.clear();

        sf::Time eTime = _clock.getElapsedTime();
        _clock.restart();

        //ALL Update
        bm.Update(eTime.asMicroseconds());

        std::cout << "Update in " << eTime.asSeconds() << "s" << std::endl;
        //ALL Display
        bm.Display(window);

        window.display();
    }

    return 0;
}