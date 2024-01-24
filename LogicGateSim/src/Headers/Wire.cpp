#include "Wire.hpp"
#include <iostream>

Wire::Wire()
{
	this->setPrimitiveType(sf::Lines);
	this->resize(2);
}

void Wire::updateWire()
{
	if (inputObj != nullptr) {
		(*this)[0].position = inputObj->getPosition();
		this->state = inputObj->outputs[0];
	}
	if (inputNode != nullptr) {
		(*this)[0].position = inputNode->getPosition();
		this->state = inputNode->state;
	}
	if (outputObj != nullptr) {
		(*this)[1].position = outputObj->getPosition();
		outputObj->inputs[0] = this->state;
	}
	if (outputNode != nullptr) {
		(*this)[1].position = outputNode->getPosition();
		outputNode->state = this->state;
	}

	if (state) {
		(*this)[0].color = sf::Color::Red;
		(*this)[1].color = sf::Color::Red;
	}
	else {
		(*this)[0].color = sf::Color::White;
		(*this)[1].color = sf::Color::White;
	}
}
