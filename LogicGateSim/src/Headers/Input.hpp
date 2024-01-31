#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <iostream>
#include "Common.hpp"

class InputField {
private:
	sf::Sprite acceptButton;
	sf::Sprite cancelButton;
	sf::Texture acceptButtonTex;
	sf::Texture cancelButtonTex;

	//const std::unordered_set<char> rejected = { '!','@','#','$','%','^','&','*','(',')','~','`' };
	const std::unordered_set<std::string> rejected = { "!","@","#","$","%","^","&","*","(",")","~","`","" };
public:
	InputField();

	void update();
	void draw();
	void scale();
};