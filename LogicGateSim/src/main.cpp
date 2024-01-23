// SFML
#include <SFML/Graphics.hpp>
// Other
#include <iostream>
// My headers
#include "Headers/MainLoop.hpp"
#include "Headers/Common.hpp"

sf::RenderWindow* window;

int main() {
	// window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;

	// creating window
	sf::RenderWindow Mainwindow(sf::VideoMode(800, 600), "Logic Gate Sim", sf::Style::Default, settings);
	Mainwindow.setPosition(Mainwindow.getPosition() - sf::Vector2i(0, 50));
	Mainwindow.setVerticalSyncEnabled(true);
	window = &Mainwindow;
	// my main loop class
	Loop loop;

	srand(time(0));

	// main loop
	while (Mainwindow.isOpen())
	{
		// processing inputs(pointer to snake object)
		loop.Input();

		// updating window
		loop.Update();

		// rendering all objects
		loop.Render();
	}

	return EXIT_SUCCESS;

}
