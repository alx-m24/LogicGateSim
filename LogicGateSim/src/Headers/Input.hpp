#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <iostream>
#include "Common.hpp"
#include "Save.hpp"

class InputField {
private:
	bool* IsSaving;
	bool* istemp;
	bool* IsObj;
	bool toUp = false;

	sf::Sprite acceptButton;
	sf::Sprite cancelButton;
	sf::Sprite inputfield;
	sf::Texture acceptButtonTex;
	sf::Texture cancelButtonTex;
	sf::Texture inputFieldTex;
	sf::Text input;

	std::string text;
	//const std::unordered_set<char> rejected = { '!','@','#','$','%','^','&','*','(',')','~','`' };
	std::unordered_set<std::string> rejected = { "!","@","#","$","%","^","&","*","(",")","~","`","", "[", "]" };

	void textIn();
public:
	//InputField(Save* Saver, bool* isSaving);
	InputField(bool* isSaving, bool* isTemp, bool* isObj);

	std::string update();
	void draw();
	void scale();
};