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
	if (InputNum <= 1) Inconnectors.push_back(new Connector(sf::Vector2f(pos.x - ((this->getScale().x * tex.getSize().x) * 0.46f), pos.y)));
	else {
		float initialY = pos.y - (InputNum * 10);
		for (int i = 0; i < InputNum; ++i)
		{
			sf::Vector2f newPos = sf::Vector2f(pos.x - ((this->getScale().x * tex.getSize().x) * 0.46f), initialY + (i * InputNum * 20));
			Inconnectors.push_back(new Connector(newPos));
		}
	}
	if (OutputNum <= 1) Outconnectors.push_back(new Connector(sf::Vector2f(pos.x + ((this->getScale().x * tex.getSize().x) * 0.46f), pos.y)));
	else {
		float initialY = pos.y - (OutputNum * 10);
		for (int i = 0; i < OutputNum; ++i)
		{
			sf::Vector2f newPos = sf::Vector2f(pos.x + ((this->getScale().x * tex.getSize().x) * 0.46f), initialY + (i * InputNum * 20));
			Outconnectors.push_back(new Connector(newPos));
		}
	}
}

void Object::updateObj()
{
	logic();
}

Connector::Connector(sf::Vector2f pos)
{
	this->setPosition(pos);
	this->setRadius(9.0f);
	this->setOrigin(this->getRadius(), this->getRadius());
	this->setFillColor(sf::Color::White);
	this->update();
}
