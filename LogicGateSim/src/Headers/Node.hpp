#pragma once
#include <SFML/Graphics.hpp>

class Node : public sf::Sprite {
private:
	sf::Texture tex;
public:
	enum Type {
		Input,
		Output
	};

	Node(sf::Vector2f pos, Type NodeType);
	void updateNode();

	Type type;
	bool state;
	bool input;
	bool lastRight = false, lastMid = false, moving = false;
};