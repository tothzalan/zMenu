#pragma once
#include <iostream>
#include <string.h>
#include <vector>

class ItemModel
{
public:
    ItemModel(std::string Name, std::string Executable);
    std::string Name;
    std::string Executable;
};

std::vector<ItemModel> ReadInConfig(std::string path);