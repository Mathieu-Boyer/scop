#include "OBJParser.hpp"
#include <iostream>
#include <sstream>

OBJParser::OBJParser(const std::string &filePath)
{

    std::ifstream file (filePath, std::ios::binary);

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        std::istringstream word(line);
        std::string key;
        word >> key;
        if (line[0] == '#')
            continue;
        std::string value = line.substr(key.size());
        if (!value.empty() && value[0] == ' ')
            value.erase(0, 1);

        _data[key].push_back(value);
    }

    if (file.fail())
        throw std::runtime_error("Read failed for another reason.\n");

}

OBJParser::~OBJParser()
{
}
