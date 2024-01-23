#pragma once
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Common.hpp"

class Loop {
private:
public:
	// contruct
	Loop() = default;

	void Input();
	void Update();
	void Render();
};