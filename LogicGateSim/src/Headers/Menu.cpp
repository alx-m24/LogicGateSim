#include "Menu.hpp"

Menu::Menu(Saver* Mysave) : mysave(Mysave)
{
	//i = new InputField(Mysave, &isSaving);
	i = new InputField(&isSaving, &istemplate);

	sf::Vector2u winSize = window->getSize();

	addItemTex.loadFromFile(".\\Resources\\AddItem.png");
	addItemTex.setSmooth(true);

	sf::Vector2f texSize = sf::Vector2f(addItemTex.getSize());

	addItem.setTexture(addItemTex);
	addItem.setOrigin(texSize / 2.0f);
	addItem.scale(0.25f, 0.25f);

	sf::Vector2f thisScale = addItem.getScale();
	thisSize = { texSize.x * thisScale.x, texSize.y * thisScale.y };
	addItem.setPosition(winSize.x - (thisSize.x / 2), winSize.y - (thisSize.y / 2));

	saveTex.loadFromFile(".\\Resources\\save.png");
	saveTex.setSmooth(true);
	save.setTexture(saveTex);
	save.setPosition(0, winSize.y - save.getTexture()->getSize().y * save.getScale().y);
	save.scale(0.15f, 0.15f);

	LoadTex.loadFromFile(".\\Resources\\Load.png");
	LoadTex.setSmooth(true);
	Load.setTexture(LoadTex);
	Load.setPosition(128, winSize.y - Load.getTexture()->getSize().y * Load.getScale().y - 1);
	Load.scale(0.125f, 0.125f);

	resetAddItemPos();
	menuObjs();
	setupSaveMenu();
	setupLoadMenu();
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
	Load.setPosition(128, winSize.y - Load.getTexture()->getSize().y * Load.getScale().y - 1);

	i->scale();
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
	const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

	saveAsObject.setFillColor(sf::Color(4, 232, 36));
	saveAsTemplate.setFillColor(sf::Color(4, 232, 36));

	if (!SaveBg.getGlobalBounds().contains(mousePos)) {
		isSaving = false;
	}
	else {
		if (saveAsObject.getGlobalBounds().contains(mousePos)) {
			if (left) {
				saveAsObject.setFillColor(sf::Color(52, 64, 58));
				if (!lastleft) std::cout << "Save as obj" << std::endl;
			}
		}
		else if (saveAsTemplate.getGlobalBounds().contains(mousePos)) {
			if (left) {
				saveAsTemplate.setFillColor(sf::Color(52, 64, 58));
			}
			else if (lastleft) istemplate = true;
		}
	}

	window->draw(SaveBg);
	window->draw(saveAsObject);
	window->draw(saveAsObjText);
	window->draw(saveAsTemplate);
	window->draw(saveAsTempText);
}

void Menu::displayLoadMenu()
{
	const sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(*window));

	LoadAsObject.setFillColor(sf::Color(34, 0, 124));
	LoadAsTemplate.setFillColor(sf::Color(34, 0, 124));

	if (!Loadbg.getGlobalBounds().contains(mousePos)) {
		isLoading = false;
	}
	else {
		if (LoadAsObject.getGlobalBounds().contains(mousePos)) {
			if (left) {
				LoadAsObject.setFillColor(sf::Color(52, 64, 58));
				if (!lastleft) std::cout << "Load as obj" << std::endl;
			}
		}
		else if (LoadAsTemplate.getGlobalBounds().contains(mousePos)) {
			if (left) {
				LoadAsTemplate.setFillColor(sf::Color(52, 64, 58));
			}
			else if (lastleft) loadTemp = true;
		}
	}

	window->draw(Loadbg);
	window->draw(LoadAsObject);
	window->draw(LoadAsObjText);
	window->draw(LoadAsTemplate);
	window->draw(LoadAsTempText);
}

void Menu::displayLoadTemp()
{
	std::vector<std::string> files = getFiles(".\\Saves");
	sf::Vector2f size = { 200, 80 };
	sf::Vector2f pos = { (size.x / 2) + 4, window->getSize().y - 4 - (size.y / 2) };

	for (std::string s : files) {
		std::string name = nameFromPath(s, ".json");

		sf::RectangleShape Option(size);
		
		Option.setFillColor(sf::Color(0, 52, 207));
		Option.setOutlineThickness(4);
		Option.setOutlineColor(sf::Color(0, 24, 94));
		Option.setOrigin(sf::Vector2f(Option.getSize()) / 2.0f);
		Option.setPosition(pos);

		sf::Text optiontext;
		optiontext.setFont(arial);
		optiontext.setPosition(pos.x - (name.length() * 12), pos.y - 25);
		optiontext.setFillColor(sf::Color::Black);
		optiontext.setCharacterSize(48);
		optiontext.setString(name);

		if (Option.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(*window)))) {
			if (left) {
				Option.setFillColor(sf::Color(35, 47, 84));
				Option.setOutlineColor(sf::Color(23, 29, 46));
			}
			else if (lastleft) {
				this->loadTemp = false;
				this->isAdding = false;
				this->isLoading = false;
				this->istemplate = false;

				Saver saver;
				saver.clearAll();
				saver.load(name);
			}
		}

		window->draw(Option);
		window->draw(optiontext);
		pos.y -= size.y;
		if (pos.y < window->getSize().y / 4) {
			pos.y = window->getSize().y - 4 - (size.y / 2);
			pos.x += size.x + 4;
		}
	}
}

void Menu::setupSaveMenu()
{
	SaveBg.setSize(sf::Vector2f(235, 130));
	SaveBg.setOrigin(0, SaveBg.getSize().y);
	SaveBg.setFillColor(sf::Color(19, 138, 54));
	bgPos = sf::Vector2f(0, window->getSize().y);
	SaveBg.setPosition(bgPos);

	saveAsObject.setSize(sf::Vector2f(215, 50));
	saveAsObject.setFillColor(sf::Color(4, 232, 36));
	saveAsObject.setPosition(sf::Vector2f(SaveBg.getPosition() + sf::Vector2f(10, -60)));
	
	saveAsObjText.setFont(arial);
	saveAsObjText.setFillColor(sf::Color::Black);
	saveAsObjText.setCharacterSize(24);
	saveAsObjText.setString("Save as new object");
	saveAsObjText.setPosition(saveAsObject.getPosition() + sf::Vector2f(0, 10));

	
	saveAsTemplate.setSize(sf::Vector2f(215, 50));
	saveAsTemplate.setFillColor(sf::Color(4, 232, 36));
	saveAsTemplate.setPosition(sf::Vector2f(SaveBg.getPosition() + sf::Vector2f(10, -120)));
	
	saveAsTempText.setFont(arial);
	saveAsTempText.setFillColor(sf::Color::Black);
	saveAsTempText.setCharacterSize(24);
	saveAsTempText.setString("Save as template");
	saveAsTempText.setPosition(saveAsTemplate.getPosition() + sf::Vector2f(15, 10));
}

void Menu::setupLoadMenu()
{
	Loadbg.setSize(sf::Vector2f(235, 130));
	Loadbg.setOrigin(0, Loadbg.getSize().y);
	Loadbg.setFillColor(sf::Color(4, 5, 46));
	bgPos = sf::Vector2f(0, window->getSize().y);
	Loadbg.setPosition(bgPos);

	LoadAsObject.setSize(sf::Vector2f(215, 50));
	LoadAsObject.setFillColor(sf::Color(13, 0, 164));
	LoadAsObject.setPosition(sf::Vector2f(Loadbg.getPosition() + sf::Vector2f(10, -60)));

	LoadAsObjText.setFont(arial);
	LoadAsObjText.setFillColor(sf::Color::Black);
	LoadAsObjText.setCharacterSize(24);
	LoadAsObjText.setString("Load as object");
	LoadAsObjText.setPosition(LoadAsObject.getPosition() + sf::Vector2f(25, 10));

	LoadAsTemplate.setSize(sf::Vector2f(215, 50));
	LoadAsTemplate.setFillColor(sf::Color(13, 0, 164));
	LoadAsTemplate.setPosition(sf::Vector2f(Loadbg.getPosition() + sf::Vector2f(10, -120)));

	LoadAsTempText.setFont(arial);
	LoadAsTempText.setFillColor(sf::Color::Black);
	LoadAsTempText.setCharacterSize(24);
	LoadAsTempText.setString("Load as template");
	LoadAsTempText.setPosition(LoadAsTemplate.getPosition() + sf::Vector2f(15, 10));
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
		if (Load.getGlobalBounds().contains(mousePos)) isLoading = true;
		addItem.setColor(sf::Color::White);
		save.setColor(sf::Color::White);
		Load.setColor(sf::Color::White);
	}
	else {
		if (left && hover) addItem.setColor(sf::Color(126, 127, 145, 255));
		else if (left && save.getGlobalBounds().contains(mousePos)) save.setColor(sf::Color(126, 127, 145, 255));
		else if (left && Load.getGlobalBounds().contains(mousePos)) Load.setColor(sf::Color(126, 127, 145, 255));
	}
}

void Menu::display()
{
	window->draw(addItem);
	window->draw(save);
	window->draw(Load);
	
	if (isLoading && !loadTemp) displayLoadMenu();
	else if (loadTemp) {
		displayLoadTemp();
	}
	else if (isAdding) displayAddMenu();
	else if (isSaving && !istemplate) {
		displaySaveMenu();
	}
	if (istemplate) {
		std::string name = i->update();
		if (!name.empty()) {
			mysave->save(name);
			return;
		}
		i->draw();
	}
}

void Menu::resetMenu()
{
	resetAddItemPos();
	setupSaveMenu();
	setupLoadMenu();
}
