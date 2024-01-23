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
}

void Loop::Update()
{
	window->clear(sf::Color::Black);
	for (Object* obj : objects)
	{
		obj->updateObj();
	}
}

void Loop::Render()
{
	for (Object* obj : objects)
	{
		window->draw(*obj);
	}
	window->display();
}