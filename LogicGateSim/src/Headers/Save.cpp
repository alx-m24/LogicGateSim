#include "Save.hpp"

void Save::closeFile()
{
    if (f != 0) fclose(f);
}

void Save::read()
{
    if (f != 0) {
        char readBuffer[128];
        rapidjson::FileReadStream reader(f, readBuffer, sizeof(readBuffer));
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
            nodes.push_back(new Node(sf::Vector2f(node["posX"].GetFloat(), node["posY"].GetFloat()), Node::Input));
        }
        else if (type == "output") {
            nodes.push_back(new Node(sf::Vector2f(node["posX"].GetFloat(), node["posY"].GetFloat()), Node::Output));
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

        int inNIdx = w["inputNodeIdx"].GetInt();
        int outNIdx = w["outputNodeIdx"].GetInt();
        int inOIdx = w["inputObjIdx"].GetInt();
        int outOIdx = w["outputObjIdx"].GetInt();

        if (inNIdx > -1 && outNIdx > -1) wires.push_back(new Wire(nodes[inNIdx], nodes[outNIdx]));
        else if (inNIdx > -1 && outOIdx > -1) wires.push_back(new Wire(nodes[inNIdx], objects[outOIdx]));
        else if (inOIdx > -1 && outOIdx > -1) wires.push_back(new Wire(objects[inOIdx], objects[outOIdx]));
        else if (inOIdx > -1 && outNIdx > -1) wires.push_back(new Wire(objects[inOIdx], nodes[outNIdx]));

        wires[wires.size() - 1]->inputIndex = w["inputIndex"].GetInt();
        wires[wires.size() - 1]->outputIndex = w["outputIndex"].GetInt();
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
            objects.push_back(new AndGate(sf::Vector2f(obj["posX"].GetFloat(), obj["posY"].GetFloat())));
        }
        else if (name == "notGate") {
            objects.push_back(new NotGate(sf::Vector2f(obj["posX"].GetFloat(), obj["posY"].GetFloat())));
        }
        else if (name == "orGate") {
            objects.push_back(new OrGate(sf::Vector2f(obj["posX"].GetFloat(), obj["posY"].GetFloat())));
        }
    }
}

void Save::saveNodes()
{
    rapidjson::Value& nodeNum = d["NodeNum"];
    int n = nodes.size();
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
        nS.AddMember("posX", (float)n->getPosition().x, d.GetAllocator());
        nS.AddMember("posY", (float)n->getPosition().y, d.GetAllocator());

        Nodes.PushBack(nS, d.GetAllocator());
    }
}

void Save::saveWires()
{
    rapidjson::Value& s = d["WireNum"];
    int n = wires.size();
    s.SetInt(n);

    rapidjson::Value& wS = d["wires"];
    wS.Clear();

    for (int i = 0; i < n; ++i)
    {
        Wire* wire = wires[i];

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
    rapidjson::Value& s = d["Objnum"];
    int n = objects.size();
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
        oS.AddMember("posX", (float)o->getPosition().x, d.GetAllocator());
        oS.AddMember("posY", (float)o->getPosition().y, d.GetAllocator());

        objs.PushBack(oS, d.GetAllocator());
    }
}

Save::Save()
{
    fopen_s(&f, "C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Saves\\saves.json", "r");
    
    read();

    closeFile();
}

Save::~Save()
{
    closeFile();
}

void Save::load()
{
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
}

void Save::save()
{
    // Modify the JSON data 
    saveObjs();
    saveNodes();
    saveWires();

    fopen_s(&f, "C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Saves\\saves.json", "w");

    char writeBuffer[128];
    rapidjson::FileWriteStream os(f, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    d.Accept(writer);

    closeFile();

    std::cout << "State Saved" << std::endl;
}
