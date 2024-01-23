#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Object : public sf::Sprite{
private:
	sf::Texture tex;
public:
	Object(std::string pathToTex, sf::Vector2f pos, unsigned int InputNum, unsigned int OutputNum);
	void updateObj();
	virtual void logic() {};

	std::vector<bool> inputs;
	std::vector<bool> outputs;
};