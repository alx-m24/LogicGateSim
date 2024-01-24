#pragma once
#include <SFML/Graphics.hpp>
// My headers
#include "Node.hpp"
#include "Object.hpp"

class Wire : public sf::VertexArray {
private:
	void changeColor();
	void logic();
public:
	Wire();
	void updateWire();

	Object* inputObj = nullptr;
	Object* outputObj = nullptr;
	Node* inputNode = nullptr;
	Node* outputNode = nullptr;

	bool state = false;
};