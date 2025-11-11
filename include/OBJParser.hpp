#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <array>
#include "vertex.hpp"


struct Face {
    std::vector<std::array<int,2>> corners;
};

struct OBJ {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<Face> faces;
    std::vector<unsigned int> drawIndices;
};


class OBJParser
{
    private:
        std::map<std::string, std::vector<std::string>> _data;
        OBJ objData;
        std::vector<vertex> vertices;
        void convertToVectors();
        void createVertices();
        std::vector<std::string> split(const std::string& str, char delim);
    public:
        OBJParser(const std::string &filePath);
        ~OBJParser();

        OBJ &getObjData();
        const OBJ &getObjData() const;

        std::vector<vertex> &getVertices();
        const  std::vector<vertex> &getVertices() const;
};