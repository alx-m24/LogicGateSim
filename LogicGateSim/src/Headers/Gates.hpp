#pragma once
#include <SFML/Graphics.hpp>
#include "Object.hpp"

class NotGate : public Object {
public:
	NotGate(sf::Vector2f pos) : Object("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\Not.png", pos, 1, 1, "notGate") {};

	void logic();
};

class AndGate : public Object {
public:
	AndGate(sf::Vector2f pos) : Object("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\AND.png", pos, 2, 1, "andGate") {};

	void logic();
};

class OrGate : public Object {
public:
	OrGate(sf::Vector2f pos) : Object("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\OR.png", pos, 2, 1, "orGate") {};

	void logic();
};

class TestGate : public Object {
public:
	TestGate(sf::Vector2f pos) : Object(" ", pos, 4, 1, "testGate") {};

	void logic();
};
