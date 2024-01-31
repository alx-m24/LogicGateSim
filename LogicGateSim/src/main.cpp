// SFML
#include <SFML/Graphics.hpp>
// Other
#include <iostream>
// My headers
#include "Headers/MainLoop.hpp"
#include "Headers/Common.hpp"
#include "Headers/Object.hpp"
#include "Headers/Gates.hpp"
#include "Headers/Node.hpp"
#include "Headers/Wire.hpp"
#include "Headers/Save.hpp"

sf::RenderWindow* window;
sf::Font arial;
std::vector<Object*> objects;
std::vector<Node*> nodes;
std::vector<Wire*> wires;
bool left;
bool lastleft;
bool right;
bool lastright;
bool middle;
bool lastmiddle;
std::string currKey;

void fps(sf::Text* fpsText) {
	fpsText->setFont(arial);
	fpsText->setFillColor(sf::Color::Red);
	fpsText->setCharacterSize(24);
}

int main() {
	Save save;

	// window settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// creating window
	sf::RenderWindow Mainwindow(sf::VideoMode(800, 600), "Logic Gate Sim", sf::Style::Default, settings);
	Mainwindow.setPosition(Mainwindow.getPosition() - sf::Vector2i(0, 50));
	Mainwindow.setVerticalSyncEnabled(true);

	sf::Image icon;
	icon.loadFromFile("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\Icon.png");
	Mainwindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	window = &Mainwindow;
	// my main loop class
	Loop loop(&save);

	arial.loadFromFile("C:/Windows/Fonts/arial.ttf");
	sf::Text fpsText;
	fps(&fpsText);

	sf::Clock FPSclock;
	uint8_t FPS = 0, Frame = 0;
	// main loop
	while (Mainwindow.isOpen())
	{
		if (FPSclock.getElapsedTime().asSeconds() >= 1.f)
		{
			FPS = Frame;
			Frame = 0;
			FPSclock.restart();

			fpsText.setString("FPS: " + std::to_string(FPS));
		}

		// processing inputs(pointer to snake object)
		loop.Input();

		// updating window
		loop.Update();

		// rendering all objects
		window->draw(fpsText);
		loop.Render();

		++Frame;
	}

	return EXIT_SUCCESS;
}
