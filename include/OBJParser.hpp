#pragma once
#include "LinearAlgebra.hpp"


#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <array>
#include "vertex.hpp"


struct Face {
    std::vector<std::array<int,3>> corners;
};

struct OBJ {
    std::vector<LinearAlgebra::vec3> positions;
    std::vector<LinearAlgebra::vec3> normals;
    std::vector<LinearAlgebra::vec2> textureCoordinates;
    std::vector<Face> faces;
    std::vector<unsigned int> drawIndices;
};


class OBJParser
{
    private:
        float Xmin = +INFINITY;
        float Xmax = -INFINITY;

        float Ymin = +INFINITY;
        float Ymax = -INFINITY;

        float Zmin = +INFINITY;
        float Zmax = -INFINITY;

        std::map<std::string, std::vector<std::string>> _data;
        OBJ objData;
        std::vector<vertex> vertices;
        void convertToVectors();
        void createVertices();

        void handlePositions();
        void handleNormals();
        void handleFaces();
        void handleTextureCoordinates();
    public:
        OBJParser(const std::string &filePath);
        ~OBJParser();

        OBJ &getObjData();
        const OBJ &getObjData() const;

        std::vector<vertex> &getVertices();
        const  std::vector<vertex> &getVertices() const;
        const LinearAlgebra::vec3 scalingVector() const;
};