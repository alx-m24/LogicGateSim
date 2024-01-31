#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Gates.hpp"
#include "Common.hpp"
#include "Node.hpp"
#include "Save.hpp"

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

	sf::Sprite save;
	sf::Texture saveTex;

	Save* mysave;

	void resetAddItemPos();
	void displayAddMenu();
	void menuObjs();
	void displaySaveMenu();
public:
	Menu(Save* Mysave);
	void updateMenu();
	void display();
	void resetMenu();

	bool isAdding = false;
	bool isSaving = false;
	sf::Vector2f bgPos;
};