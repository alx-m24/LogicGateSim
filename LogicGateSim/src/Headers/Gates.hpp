#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Object.hpp"

class NotGate : public Object {
public:
	NotGate(sf::Vector2f pos) : Object("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\Not.png", pos, 1, 1) {};

	void logic();
};

class AndGate : public Object {
public:
	AndGate(sf::Vector2f pos) : Object("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\AND.png", pos, 2, 1) {};

	void logic();
};
