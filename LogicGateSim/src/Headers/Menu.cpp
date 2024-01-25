#include "Menu.hpp"

Menu::Menu()
{
	sf::Vector2u winSize = window->getSize();

	addItemTex.loadFromFile("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\AddItem.png");
	addItemTex.setSmooth(true);

	sf::Vector2f texSize = sf::Vector2f(addItemTex.getSize());

	addItem.setTexture(addItemTex);
	addItem.setOrigin(texSize / 2.0f);
	addItem.scale(0.25f, 0.25f);
	
	sf::Vector2f thisScale = addItem.getScale();
	sf::Vector2f thisSize = { texSize.x * thisScale.x, texSize.y * thisScale.y };
	addItem.setPosition(winSize.x - (thisSize.x / 2), winSize.y - (thisSize.y / 2));
}

void Menu::resetAddItemPos()
{
	sf::Vector2f thisScale = addItem.getScale();
	sf::Vector2f texSize = sf::Vector2f(addItemTex.getSize());
	sf::Vector2u winSize = window->getSize();

	sf::Vector2f thisSize = { texSize.x * thisScale.x, texSize.y * thisScale.y };
	addItem.setPosition(winSize.x - (thisSize.x / 2), thisSize.y / 2);
}

void Menu::displayAddMenu()
{
	std::cout << "Add" << std::endl;
}

void Menu::updateMenu()
{
	resetAddItemPos();

	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
	bool hover = addItem.getGlobalBounds().contains(mousePos);
	bool left = sf::Mouse::isButtonPressed(sf::Mouse::Left);
	
	if (left && !lastleft) {
		if (hover) {
			isAdding = !isAdding;
			addItem.setColor(sf::Color(126, 127, 145));
		}
		else isAdding = false;
	}
	else {
		if (!left && lastleft) addItem.setColor(sf::Color::White);
	}

	lastleft = left;
}

void Menu::display()
{
	window->draw(addItem);
	if (isAdding) displayAddMenu();
}
