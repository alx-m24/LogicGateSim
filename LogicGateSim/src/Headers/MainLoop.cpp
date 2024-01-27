#include "MainLoop.hpp"

Loop::Loop()
{
	menu = new Menu;

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
			if (left) {
				obj->setPosition(mousePos);
				moveConnectors(obj);
				obj->setColor(sf::Color(167, 167, 167));
			}
			else obj->setColor(sf::Color::White);
			if (mid && !obj->lastMid) {
				if (addWire) {
					for (int i = 0; i < obj->Inconnectors.size(); ++i)
					{
						if (obj->Inconnectors[i]->getGlobalBounds().contains(mousePos))
						{
							Wire* w = wires[wires.size() - 1];
							w->outputObj = obj;
							w->inputIndex = i;
						}
					}
				}
				else {
					for (int i = 0; i < obj->Outconnectors.size(); ++i)
					{
						if (obj->Outconnectors[i]->getGlobalBounds().contains(mousePos))
						{
							Wire* w = new Wire;
							(*w)[0].position = obj->Outconnectors[i]->getPosition();
							(*w)[1].position = obj->Outconnectors[i]->getPosition();
							w->inputObj = obj;
							w->outputIndex = i;
							wires.push_back(w);
						}
					}
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

void Loop::moveConnectors(Object* obj)
{
	int InputNum = obj->inputs.size(), OutputNum = obj->outputs.size();
	float objSizeX = obj->getTexture()->getSize().x * obj->getScale().x;

	if (InputNum <= 1) obj->Inconnectors[0]->setPosition(sf::Vector2f(mousePos.x - (objSizeX * 0.46f), mousePos.y));
	else {
		float initialY = mousePos.y - (InputNum * 10);
		for (int i = 0; i < InputNum; ++i)
		{
			sf::Vector2f newPos = sf::Vector2f(mousePos.x - (objSizeX * 0.46), initialY + (i * InputNum * 20));
			obj->Inconnectors[i]->setPosition(newPos);
		}
	}
	if (OutputNum <= 1) obj->Outconnectors[0]->setPosition(sf::Vector2f(mousePos.x + (objSizeX * 0.46f), mousePos.y));
	else {
		float initialY = mousePos.y - (OutputNum * 10);
		for (int i = 0; i < OutputNum; ++i)
		{
			sf::Vector2f newPos = sf::Vector2f(mousePos.x + (objSizeX * 0.46f), initialY + (i * InputNum * 20));
			obj->Outconnectors[i]->setPosition(newPos);
		}
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
			if (event.mouseButton.button != sf::Mouse::Left) menu->isAdding = false;
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

	menu->updateMenu();
}

void Loop::Render()
{
	for (Wire* w : wires) window->draw(*w);
	for (Object* obj : objects) {
		window->draw(*obj);
		for (Connector* c : obj->Inconnectors) window->draw(*c);
		for (Connector* c : obj->Outconnectors) window->draw(*c);
	}
	for (Node* n : nodes) window->draw(*n);
	if (addWire) window->draw(addWireSprite);

	menu->display();

	window->display();
}