#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Common.hpp"
#include "Node.hpp"

class Menu {
private:
	sf::Sprite addItem;
	sf::Texture addItemTex;

	bool lastleft = false;

	void resetAddItemPos();
	void displayAddMenu();
public:
	Menu();
	void updateMenu();
	void display();

	bool isAdding = false;
};