#include "Input.hpp"

void InputField::textIn()
{
	if (!currKey.empty() && !rejected.count(currKey)) {
		if (currKey == "Shift") {
			toUp = true;
			return;
		}

		if (currKey.size() <= 1) {
			const char c = currKey[0];
			if (!toUp) {
				//text.append((char)std::tolower(c), 1);
				text += (char)std::tolower((char)c);
			}
			else {
				text += (char)c;
				toUp = false;
			}
		}
		else if (currKey == "Space") text += " ";
		else if (currKey == "Backspace" && !text.empty()) text.pop_back();

		input.setString(text);

		//std::cout << name << std::endl;
	}
}

InputField::InputField(bool* isSaving, bool* isTemp)
{
	acceptButtonTex.loadFromFile(".\\Resources\\Accept.png");
	acceptButtonTex.setSmooth(true);
	acceptButtonTex.generateMipmap();

	cancelButtonTex.loadFromFile(".\\Resources\\Cancel.png");
	cancelButtonTex.setSmooth(true);
	cancelButtonTex.generateMipmap();

	acceptButton.setTexture(acceptButtonTex);
	acceptButton.setScale(0.2f, 0.2f);
	acceptButton.setPosition(sf::Vector2f((window->getSize().x / 2) - 250, (window->getSize().y / 2) + 100));
	cancelButton.setTexture(cancelButtonTex);
	cancelButton.setScale(0.2f, 0.2f);;
	cancelButton.setPosition(sf::Vector2f((window->getSize().x / 2) + 50,  (window->getSize().y / 2) + 100));

	inputFieldTex.loadFromFile(".\\Resources\\InputField.png");
	inputFieldTex.setSmooth(true);
	inputfield.setTexture(inputFieldTex);
	inputfield.setOrigin(sf::Vector2f(inputFieldTex.getSize()) / 2.0f);
	inputfield.setPosition(sf::Vector2f(window->getSize()) / 2.0f);
	inputfield.setScale(0.9f, 0.4f);
	input.setCharacterSize(100);
	input.setFont(arial);
	input.setFillColor(sf::Color::White);
	input.setPosition(inputfield.getPosition().x - 375, inputfield.getPosition().y - 60);

	input.setLetterSpacing(input.getLineSpacing());

	text = "";

	//mysave = saver;
	IsSaving = isSaving;
	istemp = isTemp;
}

std::string InputField::update()
{
	const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
	if (lastleft && !left)
	{
		if (acceptButton.getGlobalBounds().contains(mousePos)) {
			acceptButton.setColor(sf::Color::White);
			if (!text.empty()) {
				//mysave->save(std::string(text));
				*IsSaving = false;
				*istemp = false;
				return text;
			}
		}
		else if (cancelButton.getGlobalBounds().contains(mousePos)) {
			cancelButton.setColor(sf::Color::White);
			*IsSaving = false;
			*istemp = false;
			return "";
		}
	}
	if (left) {
		if (cancelButton.getGlobalBounds().contains(mousePos)) cancelButton.setColor(sf::Color(52, 64, 58));
		if (acceptButton.getGlobalBounds().contains(mousePos)) acceptButton.setColor(sf::Color(52, 64, 58));
	}
	textIn();

	return "";
}

void InputField::draw()
{
	window->draw(inputfield);
	window->draw(input);
	window->draw(acceptButton);
	window->draw(cancelButton);
}

void InputField::scale()
{
	acceptButton.setPosition(sf::Vector2f((window->getSize().x / 2) - 250, (window->getSize().y / 2) + 100));
	cancelButton.setPosition(sf::Vector2f((window->getSize().x / 2) + 50, (window->getSize().y / 2) + 100));

	inputfield.setOrigin(sf::Vector2f(inputFieldTex.getSize()) / 2.0f);
	inputfield.setPosition(sf::Vector2f(window->getSize()) / 2.0f);
	inputfield.setScale(0.9f, 0.4f);
	input.setCharacterSize(100);
	input.setFont(arial);
	input.setFillColor(sf::Color::White);
	input.setPosition(inputfield.getPosition().x - 375, inputfield.getPosition().y - 60);
}
