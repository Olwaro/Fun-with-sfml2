#include <iostream>
#include <list>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Fun with SFML2", 7U, cs);
	window.setFramerateLimit(60);

	sf::Clock clk;
	list<sf::CircleShape*> circles;
	vector<sf::Color> colours;
		colours.push_back(sf::Color::Blue); 
		colours.push_back(sf::Color::Green);
		colours.push_back(sf::Color::Magenta);
		colours.push_back(sf::Color::Cyan);
		colours.push_back(sf::Color::Red);
	int ci = 0;
	float maxRadius = 400;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			if (event.type == sf::Event::MouseMoved)
			{
				if (clk.getElapsedTime().asMilliseconds() > 45)
				{
					sf::CircleShape *tmp = new sf::CircleShape(10);
					tmp->setFillColor(sf::Color::Transparent);
					tmp->setOutlineThickness(1);
					tmp->setOutlineColor(colours[(ci++)%colours.size()]);
					tmp->setPointCount(100);
					tmp->setOrigin(tmp->getRadius(), tmp->getRadius());
					tmp->setPosition((float)event.mouseMove.x, (float)event.mouseMove.y);

					circles.push_back(tmp);

					//cout << "x:" << event.mouseMove.x << " y:" << event.mouseMove.y << endl;
					clk.restart();
				}
			}
			if (event.type == sf::Event::Closed)
                window.close();
        }

		circles.remove_if([maxRadius](sf::CircleShape* c) { return c->getRadius() > maxRadius; });
		

        window.clear();
		for(auto i = circles.begin(); i != circles.end(); ++i)
		{
			(*i)->setRadius((*i)->getRadius()+2);
			(*i)->setOrigin((*i)->getRadius(), (*i)->getRadius());
			
			sf::Color c = sf::Color((*i)->getOutlineColor());
			c.a = 255 * (1 - (*i)->getRadius()/(maxRadius+2));

			(*i)->setOutlineColor(c);

			window.draw(**i);
		}
        window.display();
    }

    return 0;
}