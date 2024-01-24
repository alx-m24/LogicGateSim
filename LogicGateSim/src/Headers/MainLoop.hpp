#pragma once
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Node.hpp"
#include "Common.hpp"

class Loop {
private:
	bool addWire = false, lastAdd = false;
	bool left = false;
	bool right = false;
	bool mid = false;
	sf::Texture addWireTex;
	sf::Sprite addWireSprite;
	sf::Vector2f mousePos;
	
	void loadWireTextures();
	void updateObjs();
	void updateNodes();
public:
	// contruct
	Loop();

	void Input();
	void Update();
	void Render();
};