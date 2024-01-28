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

	void resetAddItemPos();
	void displayAddMenu();
public:
	Menu();
	void updateMenu();
	void display();

	bool isAdding = false;
};