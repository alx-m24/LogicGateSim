#include "Save.hpp"

void Save::closeFile(FILE* f)
{
	if (f != 0) fclose(f);
}

void Save::read()
{
	if (f != 0) {
		char readBuffer[128];
		rapidjson::FileReadStream reader(f, readBuffer, sizeof(readBuffer));
		d.SetObject();
		d.ParseStream(reader);
	}
}

void Save::loadNodes()
{
	int n = d["NodeNum"].GetInt();
	rapidjson::Value& Nodes = d["nodes"];
	for (int i = 0; i < n; ++i)
	{
		rapidjson::Value& node = Nodes[i];
		std::string type = node["type"].GetString();
		if (type == "input") {
			nodes.push_back(new Node(sf::Vector2f(node["posX"].GetInt(), node["posY"].GetInt()), Node::Input));
		}
		else if (type == "output") {
			nodes.push_back(new Node(sf::Vector2f(node["posX"].GetInt(), node["posY"].GetInt()), Node::Output));
		}
	}
}

void Save::loadWires()
{
	int n = d["WireNum"].GetInt();
	rapidjson::Value& JSONwires = d["wires"];
	for (int i = 0; i < n; ++i)
	{
		rapidjson::Value& w = JSONwires[i];

		Wire* newWire = new Wire();

		newWire->inNodeIdx = w["inputNodeIdx"].GetInt();
		newWire->outNodeIdx = w["outputNodeIdx"].GetInt();
		newWire->inObjIdx = w["inputObjIdx"].GetInt();
		newWire->outObjIdx = w["outputObjIdx"].GetInt();
		newWire->inputIndex = w["inputIndex"].GetInt();
		newWire->outputIndex = w["outputIndex"].GetInt();

		if (newWire->inNodeIdx > -1) newWire->inputNode = nodes[newWire->inNodeIdx];
		if (newWire->outNodeIdx > -1) newWire->outputNode = nodes[newWire->outNodeIdx];
		if (newWire->inObjIdx > -1) newWire->inputObj = objects[newWire->inObjIdx];
		if (newWire->outObjIdx > -1) newWire->outputObj = objects[newWire->outObjIdx];

		wires.push_back(newWire);
	}
}

void Save::loadObjs()
{
	int n = d["Objnum"].GetInt();
	rapidjson::Value& objs = d["objects"];
	for (int i = 0; i < n; ++i)
	{
		rapidjson::Value& obj = objs[i];
		std::string name = obj["name"].GetString();
		if (name == "andGate") {
			objects.push_back(new AndGate(sf::Vector2f(obj["posX"].GetInt(), obj["posY"].GetInt())));
		}
		else if (name == "notGate") {
			objects.push_back(new NotGate(sf::Vector2f(obj["posX"].GetInt(), obj["posY"].GetInt())));
		}
		else if (name == "orGate") {
			objects.push_back(new OrGate(sf::Vector2f(obj["posX"].GetInt(), obj["posY"].GetInt())));
		}
	}
}

void Save::saveNodes()
{
	int n = nodes.size();
	if (n < 0) return;

	rapidjson::Value& nodeNum = d["NodeNum"];
	nodeNum.SetInt(n);

	rapidjson::Value& Nodes = d["nodes"];
	Nodes.Clear();

	for (int i = 0; i < n; ++i)
	{
		Node* n = nodes[i];

		rapidjson::Value nS;
		nS.SetObject();

		if (n->type == Node::Input) nS.AddMember("type", "input", d.GetAllocator());
		else if (n->type == Node::Output) nS.AddMember("type", "output", d.GetAllocator());
		nS.AddMember("posX", (int)n->getPosition().x, d.GetAllocator());
		nS.AddMember("posY", (int)n->getPosition().y, d.GetAllocator());

		Nodes.PushBack(nS, d.GetAllocator());
	}
}

void Save::saveWires()
{
	int n = wires.size();
	if (n < 0) return;

	rapidjson::Value& s = d["WireNum"];
	s.SetInt(n);

	rapidjson::Value& wS = d["wires"];
	wS.Clear();

	for (Wire* wire : wires)
	{
		rapidjson::Value w;
		w.SetObject();

		w.AddMember("inputNodeIdx", wire->inNodeIdx, d.GetAllocator());
		w.AddMember("outputNodeIdx", wire->outNodeIdx, d.GetAllocator());
		w.AddMember("inputObjIdx", wire->inObjIdx, d.GetAllocator());
		w.AddMember("outputObjIdx", wire->outObjIdx, d.GetAllocator());
		w.AddMember("inputIndex", wire->inputIndex, d.GetAllocator());
		w.AddMember("outputIndex", wire->outputIndex, d.GetAllocator());

		wS.PushBack(w, d.GetAllocator());
	}
}

void Save::saveObjs()
{
	int n = objects.size();
	if (n < 0) return;

	rapidjson::Value& s = d["Objnum"];
	s.SetInt(n);

	rapidjson::Value& objs = d["objects"];
	objs.Clear();

	for (int i = 0; i < n; ++i)
	{
		Object* o = objects[i];
		std::string name = o->name;

		rapidjson::Value oS;
		oS.SetObject();

		if (name == "notGate") oS.AddMember("name", "notGate", d.GetAllocator());
		else if (name == "orGate") oS.AddMember("name", "orGate", d.GetAllocator());
		else if (name == "andGate") oS.AddMember("name", "andGate", d.GetAllocator());
		oS.AddMember("posX", (int)o->getPosition().x, d.GetAllocator());
		oS.AddMember("posY", (int)o->getPosition().y, d.GetAllocator());

		objs.PushBack(oS, d.GetAllocator());
	}
}

void Save::loadTemplate()
{
	d.AddMember("Objnum", 0, d.GetAllocator());
	d.AddMember("objects", rapidjson::kArrayType, d.GetAllocator());
	d.AddMember("NodeNum", 0, d.GetAllocator());
	d.AddMember("nodes", rapidjson::kArrayType, d.GetAllocator());
	d.AddMember("WireNum", 0, d.GetAllocator());
	d.AddMember("wires", rapidjson::kArrayType, d.GetAllocator());
}

Save::Save()
{
}

Save::~Save()
{
	save("recovery");
	closeFile(f);
}

void Save::load(std::string Name)
{
	std::string path = "C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Saves\\" + Name + ".json";

	closeFile(f);

	fopen_s(&f, path.c_str(), "r");
	read();

	for (Object* obj : objects) delete obj;
	objects.clear();
	for (Node* n : nodes) delete n;
	nodes.clear();
	for (Wire* w : wires) delete w;
	wires.clear();

	loadObjs();

	loadNodes();

	loadWires();

	std::cout << "Finished loading" << std::endl;

	closeFile(f);
}

void Save::save(std::string Name)
{
	fopen_s(&f, std::string("C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Saves\\" + Name + ".json").c_str(), "w");
	read();

	if (d.ObjectEmpty()) loadTemplate();

	// Modify the JSON data
	saveObjs();
	saveNodes();
	saveWires();

	char writeBuffer[128];
	rapidjson::FileWriteStream os(f, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	d.Accept(writer);

	closeFile(f);
	std::cout << "State Saved" << std::endl;
}