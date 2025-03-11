#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include "Gates.hpp"
#include "Common.hpp"
#include "Node.hpp"
#include "Save.hpp"
#include "Useful.hpp"

class Menu {
private:
	InputField* i;

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

	sf::RectangleShape SaveBg;
	sf::RectangleShape saveAsObject;
	sf::Text saveAsObjText;
	sf::RectangleShape saveAsTemplate;
	sf::Text saveAsTempText;
	sf::Sprite save;
	sf::Texture saveTex;

	sf::RectangleShape Loadbg;
	sf::RectangleShape LoadAsObject;
	sf::Text LoadAsObjText;
	sf::RectangleShape LoadAsTemplate;
	sf::Text LoadAsTempText;
	sf::Sprite Load;
	sf::Texture LoadTex;
	sf::Vector2f bgPos;

	Saver* mysave;

	void resetAddItemPos();
	void displayAddMenu();
	void menuObjs();
	void displaySaveMenu();
	void displayLoadMenu();
	void displayLoadTemp();
	// setups
	void setupSaveMenu();
	void setupLoadMenu();
public:
	// Construct
	Menu(Saver* Mysave);
	// Functions
	void updateMenu();
	void display();
	void resetMenu();

	bool isAdding = false;
	bool isLoading = false;
	bool isSaving = false, istemplate = false, loadTemp = false;
};