#pragma once
#include <rapidjson/document.h> 
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/Writer.h>
#include <iostream>
#include "Common.hpp"
#include "Gates.hpp"
#include "Node.hpp"

class Saver {
private:
	FILE* f = nullptr;
	rapidjson::Document d;

	void closeFile(FILE* f);
	void read();

	void loadNodes();
	void loadWires();
	void loadObjs();
	void saveNodes();
	void saveWires();
	void saveObjs();
	void loadTemplate();
public:
	Saver() = default;
	~Saver();

	void load(std::string Name);
	void save(std::string Name);
	void clearAll();
};