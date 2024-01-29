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
    int n = d["num"].GetInt();
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
    
    n = d["NodeNum"].GetInt();
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

    std::cout << "Finished loading" << std::endl;
}

void Save::save()
{
    // Modify the JSON data 
    rapidjson::Value& s = d["num"];
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
        oS.AddMember("posX", (int)o->getPosition().x, d.GetAllocator());
        oS.AddMember("posY", (int)o->getPosition().y, d.GetAllocator());

        objs.PushBack(oS, d.GetAllocator());
    }

    
    rapidjson::Value& nodeNum = d["NodeNum"];
    n = nodes.size();
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

    fopen_s(&f, "C:\\Users\\alexa\\Coding\\C++\\LogicGateSim\\LogicGateSim\\Saves\\saves.json", "w");

    char writeBuffer[128];
    rapidjson::FileWriteStream os(f, writeBuffer, sizeof(writeBuffer));
    rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
    d.Accept(writer);

    closeFile();
    std::cout << "State Saved" << std::endl;
}
