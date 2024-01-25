#include "MainLoop.hpp"

Loop::Loop()
{
	loadWireTextures();
}

void Loop::loadWireTextures()
{
	addWireTex.loadFromFile("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\AddWire.png");
	addWireTex.generateMipmap();
	addWireTex.setSmooth(true);

	addWireSprite.setTexture(addWireTex);
	addWireSprite.setOrigin(sf::Vector2f(addWireTex.getSize()) / 2.0f);
	addWireSprite.setScale(0.2f, 0.2f);
	addWireSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y * 2 / 3);
}

void Loop::updateObjs()
{
	for (Object* obj : objects)
	{
		bool hover = obj->getGlobalBounds().contains(mousePos);
		if (hover)
		{
			if (left) obj->setPosition(mousePos);
			if (mid && !obj->lastMid) {
				if (addWire) {
					Wire* w = wires[wires.size() - 1];
					w->outputObj = obj;
				}
				else {
					Wire* w = new Wire;
					(*w)[0].position = obj->getPosition();
					(*w)[1].position = obj->getPosition();
					w->inputObj = obj;
					wires.push_back(w);
				}
				addWire = !addWire;
			}
		}
		obj->lastMid = mid;
	}
}

void Loop::updateNodes()
{
	for (Node* n : nodes)
	{
		bool hover = n->getGlobalBounds().contains(mousePos);

		if (hover) {
			if (left) {
				n->setPosition(mousePos);
				addWire = false;
			}
			if (right && !n->lastRight && n->type == Node::Input) {
				n->state = !n->state;
				addWire = false;
			}
			if (mid && !n->lastMid) {
				if (addWire) {
					Wire* w = wires[wires.size() - 1];
					if (n->type == Node::Output) w->outputNode = n;
					else {
						auto it = std::find(wires.begin(), wires.end(), w);
						if (it != wires.end()) wires.erase(it);
						delete w;
					}
				}
				else {
					if (n->type == Node::Input) {
						Wire* w = new Wire;
						(*w)[0].position = n->getPosition();
						(*w)[1].position = n->getPosition();
						w->inputNode = n;
						wires.push_back(w);
					}
					else addWire = true;
				}
				addWire = !addWire;
			}
		}

		n->lastMid = mid;
		n->lastRight = right;
	}
}

void Loop::Input() {
	mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

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
			addWireSprite.setPosition(window->getSize().x / 2.0f, window->getSize().y * 2 / 3);
			break;
		}
		case sf::Event::MouseButtonPressed: {
			if (event.mouseButton.button != sf::Mouse::Middle) addWire = false;
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

	left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	right = sf::Mouse::isButtonPressed(sf::Mouse::Right);
	mid = sf::Mouse::isButtonPressed(sf::Mouse::Middle);

	updateObjs();
	updateNodes();

	lastAdd = addWire;
}

void Loop::Update()
{
	window->clear(sf::Color::Black);

	for (Wire* w : wires) {
		bool hover = w->getBounds().contains(mousePos);
		bool mid = sf::Mouse::isButtonPressed(sf::Mouse::Middle);

		if (hover && mid && !w->lastMid) {
			auto it = std::find(wires.begin(), wires.end(), w);
			if (it != wires.end()) wires.erase(it);
			delete w;
		}
		else {
			w->updateWire();
			w->lastMid = mid;
		}
	}
	for (Object* obj : objects) obj->updateObj();
	for (Node* n : nodes) n->updateNode();
}

void Loop::Render()
{
	for (Wire* w : wires) window->draw(*w);
	for (Object* obj : objects) window->draw(*obj);
	for (Node* n : nodes) window->draw(*n);
	if (addWire) window->draw(addWireSprite);

	window->display();
}