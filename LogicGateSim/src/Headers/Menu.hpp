#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gates.hpp"
#include "Common.hpp"
#include "Node.hpp"

class Menu {
private:
	sf::Sprite addItem;
	sf::Texture addItemTex;
	sf::Vector2f thisSize;

	sf::CircleShape inNode;
	sf::Text nodeText;
	sf::CircleShape outNode;
	sf::Text outnodeText;
	sf::RectangleShape andGate;
	AndGate temp = AndGate(sf::Vector2f(0, 0));
	sf::Text andGateText;
	sf::RectangleShape orgate;
	OrGate tempOr = OrGate(sf::Vector2f(0, 0));
	sf::Text orGateText;
	sf::RectangleShape notGate;
	NotGate tempnot = NotGate(sf::Vector2f(0, 0));
	sf::Text notGateText;

	void resetAddItemPos();
	void displayAddMenu();
	void menuObjs();
public:
	Menu();
	void updateMenu();
	void display();
	void resetMenu();

	bool isAdding = false;
	sf::Vector2f bgPos;
};