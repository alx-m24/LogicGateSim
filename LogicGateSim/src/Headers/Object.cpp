#include "Object.hpp"

Object::Object(std::string pathToTex, sf::Vector2f pos, unsigned int InputNum, unsigned int OutputNum)
{
	tex.loadFromFile(pathToTex);
	tex.generateMipmap();
	tex.setSmooth(true);

	this->setTexture(tex);
	this->setPosition(pos);
	this->setOrigin(sf::Vector2f(tex.getSize()) / 2.0f);
	this->scale(0.2f, 0.2f);

	inputs.resize(InputNum);
	outputs.resize(OutputNum);
}

void Object::updateObj()
{
	logic();
}
