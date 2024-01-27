#include "Wire.hpp"

Wire::Wire()
{
	this->setPrimitiveType(sf::Lines);
	this->resize(2);
}

void Wire::changeColor()
{
	if (state) {
		(*this)[0].color = sf::Color::Red;
		(*this)[1].color = sf::Color::Red;
	}
	else {
		(*this)[0].color = sf::Color::White;
		(*this)[1].color = sf::Color::White;
	}
}

void Wire::logic()
{
	if (inputObj != nullptr) {
		(*this)[0].position = inputObj->Outconnectors[outputIndex]->getPosition();
		this->state = inputObj->outputs[outputIndex];
	}
	if (inputNode != nullptr) {
		(*this)[0].position = inputNode->getPosition();
		this->state = inputNode->state;
	}
	if (outputObj != nullptr) {
		(*this)[1].position = outputObj->Inconnectors[inputIndex]->getPosition();
		outputObj->inputs[inputIndex] = this->state;
	}
	if (outputNode != nullptr) {
		(*this)[1].position = outputNode->getPosition();
		outputNode->state = this->state;
	}
}

void Wire::updateWire()
{
	logic();
	changeColor();
}