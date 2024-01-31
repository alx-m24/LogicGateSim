#include "Input.hpp"

InputField::InputField()
{
	/*
	//acceptButtonTex.loadFromFile("");
	acceptButtonTex.setSmooth(true);
	acceptButtonTex.generateMipmap();

	//cancelButtonTex.loadFromFile("");
	cancelButtonTex.setSmooth(true);
	cancelButtonTex.generateMipmap();


	acceptButton.setTexture(acceptButtonTex);
	cancelButton.setTexture(cancelButtonTex);*/
}

void InputField::update()
{
	if (rejected.find(currKey) == rejected.end()) std::cout << currKey << std::endl;
}

void InputField::draw()
{
}

void InputField::scale()
{
}
