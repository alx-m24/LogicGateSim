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
	void initialize();
	bool collide(sf::Vector2f pos);

	Object* inputObj = nullptr;
	Object* outputObj = nullptr;
	Node* inputNode = nullptr;
	Node* outputNode = nullptr;

	bool state = false;
	bool lastMid = false;

	int inputIndex = -1;
	int outputIndex = -1;

	int inNodeIdx = -1, outNodeIdx = -1;
	int inObjIdx = -1, outObjIdx = -1;
};