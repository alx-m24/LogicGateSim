#include "Node.hpp"

Node::Node(sf::Vector2f pos, Type NodeType)
{
	tex.loadFromFile(".\\Resources\\Node.png");
	tex.generateMipmap();
	tex.setSmooth(true);

	this->setTexture(tex);
	this->setOrigin(sf::Vector2f(tex.getSize()) / 2.0f);
	this->setScale(0.09f, 0.09f);
	this->setPosition(pos);

	input = false;
	state = false;
	type = NodeType;
}

void Node::updateNode()
{
	if (state) this->setColor(sf::Color::Red);
	else this->setColor(sf::Color::White);
}
