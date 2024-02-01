#include "Useful.hpp"

void setupfps(sf::Text* fpsText) {
	fpsText->setFont(arial);
	fpsText->setFillColor(sf::Color::Red);
	fpsText->setCharacterSize(24);
}
void fps(sf::Text* fpsText, sf::Clock* clock, unsigned int* Frame)
{
	if (clock->getElapsedTime().asSeconds() >= 1.f)
	{
		int FPS = *Frame;
		*Frame = 0;
		clock->restart();

		fpsText->setString("FPS: " + std::to_string(FPS));
	}
	++ *Frame;
}

void setupWindow()
{
	window->setPosition(window->getPosition() - sf::Vector2i(0, 50));
	window->setVerticalSyncEnabled(true);

	sf::Image icon;
	icon.loadFromFile("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Resources\\Icon.png");
	window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	arial.loadFromFile("C:/Windows/Fonts/arial.ttf");
}

std::vector<std::string> getFiles(std::string path) {
	std::vector<std::string> ans;

	// This structure would distinguish a file from a
	// directory
	struct stat sb;

	// Looping until all the items of the directory are
	// exhausted
	try {
		for (const auto& entry : std::filesystem::directory_iterator(path)) {

			// Converting the path to const char * in the
			// subsequent lines
			std::filesystem::path outfilename = entry.path();
			std::string outfilename_str = outfilename.string();
			const char* path = outfilename_str.c_str();

			// Testing whether the path points to a
			// non-directory or not If it does, displays path
			if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
				ans.push_back(path);
		}
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return ans;
}

std::string nameFromPath(std::string path, std::string fileExtension) {
	path.erase(path.end() - fileExtension.length(), path.end());
	return path.substr(path.find_last_of("/\\.") + 1);
}