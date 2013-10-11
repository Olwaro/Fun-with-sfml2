#include <iostream>
#include <list>
#include <vector>
#include <memory>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	// Window initialization
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Fun with SFML2", 7U, cs);
	window.setFramerateLimit(60);

	// Some utilities
	sf::Clock clk;
	list<unique_ptr<sf::CircleShape>> circles;
	vector<sf::Color> colours; // List initializer not supported yet by VS2012 :'(
		colours.push_back(sf::Color::Blue); 
		colours.push_back(sf::Color::Green);
		colours.push_back(sf::Color::Magenta);
		colours.push_back(sf::Color::Cyan);
		colours.push_back(sf::Color::Red);
	int ci = 0;
	float maxRadius = 400;

	// Main loop
    while (window.isOpen())
    {
		// Event processing
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (event.type == sf::Event::MouseMoved)
			{
				if (clk.getElapsedTime().asMilliseconds() > 45) // Limit circle creation frequency
				{
					// Create a circle with a random colour under mouse cursor
					unique_ptr<sf::CircleShape> tmp(new sf::CircleShape(10));
					tmp->setFillColor(sf::Color::Transparent);
					tmp->setOutlineThickness(1);
					tmp->setOutlineColor(colours[(ci++)%colours.size()]);
					tmp->setPointCount(100);
					tmp->setOrigin(tmp->getRadius(), tmp->getRadius());
					tmp->setPosition((float)event.mouseMove.x, (float)event.mouseMove.y);

					// Use move sementic "to give circle's ownership" to the container
					circles.push_back(move(tmp));

					clk.restart();
				}
			}

			if (event.type == sf::Event::Closed)
                window.close();
        }

		// Get rid of circles over a given radius
		circles.remove_if([maxRadius](unique_ptr<sf::CircleShape>& c) { return c->getRadius() > maxRadius; });
		
        window.clear();

		// Update radius et draw each circle
		for(auto &circle : circles)
		{
			circle->setRadius(circle->getRadius()+2);
			circle->setOrigin(circle->getRadius(), circle->getRadius());
			
			sf::Color c = sf::Color(circle->getOutlineColor());
			c.a = (sf::Uint8) (255 * (1 - circle->getRadius()/(maxRadius+2)));

			circle->setOutlineColor(c);

			window.draw(*circle);
		}

		// Display the whole picture on screen
        window.display();
    }

    return 0;
}