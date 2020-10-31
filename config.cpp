#include "config.h"
#include <fstream>
#include <string>
#include <sstream>

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }
    return result;
}

ItemModel::ItemModel(std::string Name, std::string Executable)
{
    this->Name = Name;
    this->Executable = Executable;
}

std::vector<ItemModel> ReadInConfig(std::string path)
{
    std::vector<ItemModel> models;
    std::ifstream infile(path);
    std::string line;
    for (std::string line; getline(infile, line);)
    {
        std::vector<std::string> data = split(line, ';');
        models.push_back(ItemModel(data[0], data[1]));
    }
    return models;
}