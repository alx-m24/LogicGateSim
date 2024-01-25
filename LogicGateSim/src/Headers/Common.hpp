#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.hpp"
#include "Node.hpp"
#include "Wire.hpp"

extern sf::RenderWindow* window;
extern sf::Font arial;
extern std::vector<Object*> objects;
extern std::vector<Node*> nodes;
extern std::vector<Wire*> wires;