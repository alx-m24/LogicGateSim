#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.hpp"
#include "Node.hpp"
#include "Wire.hpp"
#include "Input.hpp"

extern sf::RenderWindow* window;
extern sf::Font arial;
extern std::vector<Object*> objects;
extern std::vector<Node*> nodes;
extern std::vector<Wire*> wires;
extern bool left;
extern bool lastleft;
extern bool right;
extern bool lastright;
extern bool middle;
extern bool lastmiddle;
extern std::string currKey;