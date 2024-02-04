// SFML
#include <SFML/Graphics.hpp>
// My headers
#include "Headers/MainLoop.hpp"
#include "Headers/Common.hpp"
#include "Headers/Object.hpp"
#include "Headers/Gates.hpp"
#include "Headers/Node.hpp"
#include "Headers/Wire.hpp"
#include "Headers/Save.hpp"
#include "Headers/Useful.hpp"

sf::RenderWindow* window;
sf::Font arial;
std::string currKey;
std::vector<Object*> objects;
std::vector<Node*> nodes;
std::vector<Wire*> wires;
bool left;
bool lastleft;
bool right;
bool lastright;
bool middle;
bool lastmiddle;

int main() {
	Saver save;

	// window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// creating window
	sf::RenderWindow Mainwindow(sf::VideoMode(800, 600), "Logic Gate Sim", sf::Style::Default, settings);
	window = &Mainwindow;
	setupWindow();
	hideConsole();
	// my main loop class
	Loop loop(&save);

	sf::Text fpsText;
	setupfps(&fpsText);

	sf::Clock FPSclock;
	unsigned int Frame = 0;
	// main loop
	while (Mainwindow.isOpen())
	{
		fps(&fpsText, &FPSclock, &Frame);

		// processing inputs(pointer to snake object)
		loop.Input();

		// updating window
		loop.Update();

		// rendering all objects
		window->draw(fpsText);
		loop.Render();
	}

	return EXIT_SUCCESS;
}
