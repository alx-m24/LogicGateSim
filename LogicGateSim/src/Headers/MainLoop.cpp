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
}

void Loop::Update()
{
	window->clear(sf::Color::Black);
}

void Loop::Render()
{
	window->display();
}