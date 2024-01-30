#pragma once
#include <SFML/Graphics.hpp>
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
	Menu* menu;

	Save* save;
	
	void loadWireTextures();
	void updateObjs();
	void updateNodes();
	void moveConnectors(Object* obj);
public:
	// contruct
	Loop(Save* Saver);

	void Input();
	void Update();
	void Render();
};