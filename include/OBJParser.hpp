#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <vector>
#include <map>
#include <string>

class OBJParser
{
    private:
        std::map<std::string, std::vector<std::string>> _data;
    public:
        OBJParser(const std::string &filePath);
        ~OBJParser();
};