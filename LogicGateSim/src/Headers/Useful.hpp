#pragma once
#include <SFML/Graphics.hpp>
#include <filesystem>
#include <Windows.h>
#include "Common.hpp"

// Set up FPS display
void setupfps(sf::Text* fpsText);
// Updates the fps text and frame number
void fps(sf::Text* fpsText, sf::Clock* clock, unsigned int* Frame);
// Setup Window
void setupWindow();
// Returns the path of all files in the directory
std::vector<std::string> getFiles(std::string path);
// Converts a path to the file name
std::string nameFromPath(std::string path, std::string fileExtension);
// Show cmd window
void showConsole();
// Hide cmd window
void hideConsole();