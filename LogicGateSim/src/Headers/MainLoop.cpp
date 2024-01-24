#include "MainLoop.hpp"

void Loop::Input() {
	sf::Event event;
	// processing sfml events
	while (window->pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed: {
			window->close();
			break;
		}
		case sf::Event::Resized: {
			sf::View view(sf::FloatRect(0, 0, event.size.width, event.size.height));
			window->setView(view);
			break;
		}
		case sf::Event::KeyPressed: {
			switch (event.key.scancode)
			{
			case sf::Keyboard::Scancode::Escape: {
				window->close();
				break;
			}
			default:
				break;
			}
		}
		default:
			break;
		}
	}
	for (Object* obj : objects)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
			if (obj->getGlobalBounds().contains(mousePos)) obj->setPosition(mousePos);
		}
	}
	for (Node* n : nodes)
	{
		sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
		bool hover = n->getGlobalBounds().contains(mousePos);
		bool left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		bool right = sf::Mouse::isButtonPressed(sf::Mouse::Right);

		if (hover) {
			if (left) {
				n->setPosition(mousePos);
			}
			if (right && !n->lastRight && n->type == Node::Input) {
				n->state = !n->state;
			}
		}
		n->lastRight = right;
	}
}

void Loop::Update()
{
	window->clear(sf::Color::Black);
	for (Object* obj : objects)
	{
		obj->updateObj();
	}
	for (Node* n : nodes)
	{
		n->updateNode();
	}
}

void Loop::Render()
{
	for (Object* obj : objects)
	{
		window->draw(*obj);
	}
	for (Node* n : nodes)
	{
		window->draw(*n);
	}
	window->display();
}