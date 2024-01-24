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

sf::RenderWindow* window;
std::vector<Object*> objects;
std::vector<Node*> nodes;
std::vector<Wire*> wires;

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

	// Gates
	NotGate notgate(sf::Vector2f(400, 300));
	objects.push_back(&notgate);
	AndGate andGate(sf::Vector2f(200, 300));
	objects.push_back(&andGate);
	NotGate notGate2(sf::Vector2f(600, 300));
	objects.push_back(&notGate2);
	
	// Nodes
	Node testNode(sf::Vector2f(25, 300), Node::Input);
	nodes.push_back(&testNode);
	Node testNode2(sf::Vector2f(500, 300), Node::Input);
	nodes.push_back(&testNode2);
	Node testNode3(sf::Vector2f(700, 300), Node::Input);
	nodes.push_back(&testNode3);

	sf::Font arial;
	arial.loadFromFile("C:/Windows/Fonts/arial.ttf");
	sf::Text fpsText;
	fpsText.setFont(arial);
	fpsText.setFillColor(sf::Color::Red);
	fpsText.setCharacterSize(24);

	sf::Clock FPSclock;
	unsigned int FPS = 0, Frame = 0;
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
