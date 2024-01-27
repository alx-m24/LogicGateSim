#pragma once
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Node.hpp"
#include "Common.hpp"
#include "Menu.hpp"

class Loop {
private:
	bool addWire = false, lastAdd = false;
	bool left = false;
	bool right = false;
	bool mid = false;
	sf::Texture addWireTex;
	sf::Sprite addWireSprite;
	sf::Vector2f mousePos;
	Menu* menu;
	
	void loadWireTextures();
	void updateObjs();
	void updateNodes();
	void moveConnectors(Object* obj);
public:
	// contruct
	Loop();

	void Input();
	void Update();
	void Render();
};