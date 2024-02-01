#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "Object.hpp"
#include "Node.hpp"
#include "Common.hpp"
#include "Menu.hpp"
#include "Save.hpp"

class Loop {
private:
	bool addWire = false, lastAdd = false, moving = false;
	sf::Texture addWireTex;
	sf::Sprite addWireSprite;
	sf::Vector2f mousePos;
	
	std::set<int> wDelete;
	std::set<int> oDelete;
	std::set<int> nDelete;

	Menu* menu;

	Saver* save;
	
	void loadWireTextures();
	void updateObjs();
	void updateNodes();
	void moveConnectors(Object* obj);
public:
	// contruct
	Loop(Saver* Saver);

	void Input();
	void Update();
	void Render();
};