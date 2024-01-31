#include "Menu.hpp"

Menu::Menu(Save* Mysave) : mysave(Mysave)
{
	sf::Vector2u winSize = window->getSize();

	addItemTex.loadFromFile("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\AddItem.png");
	addItemTex.setSmooth(true);

	sf::Vector2f texSize = sf::Vector2f(addItemTex.getSize());

	addItem.setTexture(addItemTex);
	addItem.setOrigin(texSize / 2.0f);
	addItem.scale(0.25f, 0.25f);

	sf::Vector2f thisScale = addItem.getScale();
	thisSize = { texSize.x * thisScale.x, texSize.y * thisScale.y };
	addItem.setPosition(winSize.x - (thisSize.x / 2), winSize.y - (thisSize.y / 2));

	saveTex.loadFromFile("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\save.png");
	saveTex.setSmooth(true);
	save.setTexture(saveTex);
	save.setPosition(0, winSize.y - save.getTexture()->getSize().y * save.getScale().y);
	save.scale(0.15f, 0.15f);

	resetAddItemPos();
	menuObjs();
}

void Menu::resetAddItemPos()
{
	sf::Vector2f thisScale = addItem.getScale();
	sf::Vector2f texSize = sf::Vector2f(addItemTex.getSize());
	sf::Vector2u winSize = window->getSize();

	thisSize = { texSize.x * thisScale.x, texSize.y * thisScale.y };
	addItem.setPosition(winSize.x - (thisSize.x / 2), thisSize.y / 2);
	bgPos = { this->addItem.getPosition().x + (thisSize.x / 2), this->addItem.getPosition().y - (thisSize.y / 2) };

	save.setPosition(0, winSize.y - save.getTexture()->getSize().y * save.getScale().y);
}

void Menu::displayAddMenu()
{
	sf::RectangleShape Bg;
	Bg.setSize(sf::Vector2f(400, 400));
	Bg.setOrigin(400, 0);
	Bg.setFillColor(sf::Color(7, 11, 43, 255));
	bgPos = { this->addItem.getPosition().x + (thisSize.x / 2), this->addItem.getPosition().y - (thisSize.y / 2) };
	Bg.setPosition(bgPos);

	const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

	if (!Bg.getGlobalBounds().contains(mousePos)) {
		isAdding = false;
		return;
	}

	if (left && !lastleft)
	{
		if (inNode.getGlobalBounds().contains(mousePos))
		{
			nodes.push_back(new Node(mousePos, Node::Input));
			goto end;
		}
		if (outNode.getGlobalBounds().contains(mousePos))
		{
			nodes.push_back(new Node(mousePos, Node::Output));
			goto end;
		}
		if (andGate.getGlobalBounds().contains(mousePos))
		{
			objects.push_back(new AndGate(mousePos));
			goto end;
		}
		if (orgate.getGlobalBounds().contains(mousePos))
		{
			objects.push_back(new OrGate(mousePos));
			goto end;
		}
		if (notGate.getGlobalBounds().contains(mousePos))
		{
			objects.push_back(new NotGate(mousePos));
			goto end;
		}
	}

end:
	window->draw(Bg);
	window->draw(inNode);
	window->draw(nodeText);
	window->draw(outNode);
	window->draw(outnodeText);
	window->draw(andGate);
	window->draw(andGateText);
	window->draw(orgate);
	window->draw(orGateText);
	window->draw(notGate);
	window->draw(notGateText);
}

void Menu::menuObjs()
{
	const int alpha = 255;
	sf::Color transRed = { 255, 0, 0, alpha };
	sf::Color transWhite = { 255, 255, 255, alpha };

	inNode.setRadius(25);
	inNode.setOrigin(25, 25);
	inNode.setPosition(bgPos + sf::Vector2f(-100, 30));
	inNode.setFillColor(transWhite);

	nodeText.setFont(arial);
	nodeText.setCharacterSize(30);
	nodeText.setPosition(inNode.getPosition() + sf::Vector2f(-75, 25));
	nodeText.setFillColor(transRed);
	nodeText.setString("Input Node");


	outNode.setRadius(25);
	outNode.setOrigin(25, 25);
	outNode.setPosition(bgPos + sf::Vector2f(-285, 30));
	outNode.setFillColor(transWhite);

	outnodeText.setFont(arial);
	outnodeText.setCharacterSize(30);
	outnodeText.setPosition(outNode.getPosition() + sf::Vector2f(-80, 25));
	outnodeText.setFillColor(transRed);
	outnodeText.setString("Output Node");

	andGate.setTexture(temp.getTexture());
	andGate.setSize(sf::Vector2f(andGate.getTexture()->getSize().x * temp.getScale().x, andGate.getTexture()->getSize().y * temp.getScale().y));
	andGate.setOrigin(50, 25);
	andGate.setPosition(bgPos + sf::Vector2f(-130, 150));
	andGate.setFillColor(sf::Color(andGate.getFillColor().r, andGate.getFillColor().g, andGate.getFillColor().b, alpha));

	andGateText.setFont(arial);
	andGateText.setCharacterSize(30);
	andGateText.setPosition(andGate.getPosition() + sf::Vector2f(-25, 50));
	andGateText.setFillColor(transRed);
	andGateText.setString("And Gate");


	orgate.setTexture(tempOr.getTexture());
	orgate.setSize(sf::Vector2f(orgate.getTexture()->getSize().x * tempOr.getScale().x, orgate.getTexture()->getSize().y * tempOr.getScale().y));
	orgate.setOrigin(50, 25);
	orgate.setPosition(bgPos + sf::Vector2f(-330, 150));
	orgate.setFillColor(sf::Color(orgate.getFillColor().r, orgate.getFillColor().g, orgate.getFillColor().b, alpha));

	orGateText.setFont(arial);
	orGateText.setCharacterSize(30);
	orGateText.setPosition(orgate.getPosition() + sf::Vector2f(-15, 50));
	orGateText.setFillColor(transRed);
	orGateText.setString("Or Gate");

	notGate.setTexture(tempnot.getTexture());
	notGate.setSize(sf::Vector2f(notGate.getTexture()->getSize().x * tempnot.getScale().x, notGate.getTexture()->getSize().y * tempnot.getScale().y));
	notGate.setOrigin(50, 25);
	notGate.setPosition(bgPos + sf::Vector2f(-300, 275));
	notGate.setFillColor(sf::Color(notGate.getFillColor().r, notGate.getFillColor().g, notGate.getFillColor().b, alpha));

	notGateText.setFont(arial);
	notGateText.setCharacterSize(30);
	notGateText.setPosition(notGate.getPosition() + sf::Vector2f(-50, 40));
	notGateText.setFillColor(transRed);
	notGateText.setString("Not Gate");
}

void Menu::displaySaveMenu()
{
	sf::RectangleShape Bg;
	Bg.setSize(sf::Vector2f(235, 130));
	Bg.setOrigin(0, Bg.getSize().y);
	Bg.setFillColor(sf::Color(19, 138, 54));
	bgPos = sf::Vector2f(0, window->getSize().y);
	Bg.setPosition(bgPos);

	sf::RectangleShape saveAsObject;
	saveAsObject.setSize(sf::Vector2f(215, 50));
	saveAsObject.setFillColor(sf::Color(4, 232, 36));
	saveAsObject.setPosition(sf::Vector2f(Bg.getPosition() + sf::Vector2f(10, -60)));
	sf::Text saveAsObjText;
	saveAsObjText.setFont(arial);
	saveAsObjText.setFillColor(sf::Color::Black);
	saveAsObjText.setCharacterSize(24);
	saveAsObjText.setString("Save as new object");
	saveAsObjText.setPosition(saveAsObject.getPosition() + sf::Vector2f(0, 10));

	sf::RectangleShape saveAsTemplate;
	saveAsTemplate.setSize(sf::Vector2f(215, 50));
	saveAsTemplate.setFillColor(sf::Color(4, 232, 36));
	saveAsTemplate.setPosition(sf::Vector2f(Bg.getPosition() + sf::Vector2f(10, -120)));
	sf::Text saveAsTempText;
	saveAsTempText.setFont(arial);
	saveAsTempText.setFillColor(sf::Color::Black);
	saveAsTempText.setCharacterSize(24);
	saveAsTempText.setString("Save as template");
	saveAsTempText.setPosition(saveAsTemplate.getPosition() + sf::Vector2f(15, 10));

	const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

	if (!Bg.getGlobalBounds().contains(mousePos)) {
		isSaving = false;
		return;
	}
	else {
		if (saveAsObject.getGlobalBounds().contains(mousePos)) {
			if (left) {
				saveAsObject.setFillColor(sf::Color(52, 64, 58));
			}
			else if (lastleft) std::cout << "Save as obj" << std::endl;
		}
		else if (saveAsTemplate.getGlobalBounds().contains(mousePos)) {
			if (left) {
				saveAsTemplate.setFillColor(sf::Color(52, 64, 58));
			}
			else if (lastleft) {
				sf::Text prompt;
				prompt.setFont(arial);
				prompt.setCharacterSize(48);
				prompt.setPosition(sf::Vector2f((window->getSize().x / 2.0f) - 300, (window->getSize().y / 2.0f) - 75.0f));
				prompt.setFillColor(sf::Color::Red);
				prompt.setString("Please enter a name for your\n\ttemplate in the console.");

				window->draw(prompt);
				window->display();

				std::cout << "Name of template: ";

				std::string name;
				std::cin >> name;

				mysave->save(name);
			}
		}
	}

	window->draw(Bg);
	window->draw(saveAsObject);
	window->draw(saveAsObjText);
	window->draw(saveAsTemplate);
	window->draw(saveAsTempText);
}

void Menu::updateMenu()
{
	resetAddItemPos();

	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));
	bool hover = addItem.getGlobalBounds().contains(mousePos);
	
	if (!left && lastleft) {
		if (hover) {
			isAdding = true;
		}
		if (save.getGlobalBounds().contains(mousePos)) isSaving = true;
		addItem.setColor(sf::Color::White);
		save.setColor(sf::Color::White);
	}
	else {
		if (left && hover) addItem.setColor(sf::Color(126, 127, 145, 255));
		else if (left && save.getGlobalBounds().contains(mousePos)) save.setColor(sf::Color(126, 127, 145, 255));
	}
}

void Menu::display()
{
	window->draw(addItem);
	window->draw(save);
	if (isAdding) displayAddMenu();
	else if (isSaving) displaySaveMenu();

	InputField i;
	i.update();
}

void Menu::resetMenu()
{
	resetAddItemPos();
	menuObjs();
}
