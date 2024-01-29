#pragma once
#include <rapidjson/document.h> 
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/Writer.h>
#include <iostream>
#include "Common.hpp"
#include "Gates.hpp"
#include "Node.hpp"

class Save {
private:
	FILE* f;
	rapidjson::Document d;

	void closeFile();
	void read();
public:
	Save();
	~Save();

	void load();
	void save();
};