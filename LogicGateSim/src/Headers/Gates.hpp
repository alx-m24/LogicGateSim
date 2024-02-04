#pragma once
#include <SFML/Graphics.hpp>
#include "Object.hpp"

class NotGate : public Object {
public:
	NotGate(sf::Vector2f pos) : Object(".\\Resources\\Not.png", pos, 1, 1, "notGate") {};

	void logic();
};

class AndGate : public Object {
public:
	AndGate(sf::Vector2f pos) : Object(".\\Resources\\AND.png", pos, 2, 1, "andGate") {};

	void logic();
};

class OrGate : public Object {
public:
	OrGate(sf::Vector2f pos) : Object(".\\Resources\\OR.png", pos, 2, 1, "orGate") {};

	void logic();
};