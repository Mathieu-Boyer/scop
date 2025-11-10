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

    file.close();
    // if (file.fail())
    //     throw std::runtime_error("Read failed for another reason.\n");

    convertToVectors();

    createVertices();


}

std::vector<std::string> OBJParser::split(const std::string& str, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string buffer;

    while (std::getline(ss, buffer, delim)) {
        result.push_back(buffer);
    }

    return result;
}

void OBJParser::convertToVectors(){
    for (auto &str : _data["f"]){
        Face face;
        // int wordCounter = 0;
        std::string current;

        std::istringstream word(str);

        while (word >> current){
            std::vector<std::string> position_textureCoordinates (split(current, '/'));
            std::array<int, 2> faceVertex;

            faceVertex[0] = std::stoi(position_textureCoordinates[0] )- 1 ;
            faceVertex[1] = std::stoi(position_textureCoordinates[1] )- 1;
            face.corners.push_back(faceVertex);
            objData.drawIndices.push_back(faceVertex[0]);
        }

        objData.faces.push_back(face);
        // // if (word.eof() && wordCounter != 3)
        // //     throw std::runtime_error("Not enough coordinates given for vertex position.");
        // objData.faces.push_back(xyz[0] - 1);
        // objData.faces.push_back(xyz[1] - 1);
        // objData.faces.push_back(xyz[2] - 1);
    }

    for (auto &str : _data["v"]){
        float xyz[3];
        int wordCounter = 0;
        float current;
        std::istringstream word(str);

        while (word >> current && wordCounter < 3){
            xyz[wordCounter] = current;
            wordCounter++;
        }

        if (word.eof() && wordCounter != 3)
            throw std::runtime_error("Not enough coordinates given for vertex position.");
        objData.positions.push_back(glm::vec3(xyz[0],xyz[1],xyz[2]));
    }

    for (auto &str : _data["vt"]){
        float xy[2];
        int wordCounter = 0;
        float current;
        std::istringstream word(str);

        while (word >> current && wordCounter < 2){
            xy[wordCounter] = current;
            wordCounter++;
        }

        if (word.eof() && wordCounter != 2)
            throw std::runtime_error("Not enough coordinates given for vertex position.");
        objData.textureCoordinates.push_back(glm::vec2(xy[0],xy[1]));
    }


    // for (auto &face : objData.faces){
    //     for (auto &corner : face.corners)
    //         for (auto &index : corner)
    //             std::cout << index << " ";

    //     std::cout << "\n";
    // }
        
    for (auto &vpos :  objData.positions)
        std::cout << vpos.x << " " << vpos.y << " " << vpos.z << "\n";
    for (auto &vpos :  objData.textureCoordinates)
        std::cout << vpos.x << " " << vpos.y << "\n";
}


void OBJParser::createVertices(){
    for (auto &face : objData.faces){
        for (auto &corner : face.corners){
            vertex v;
            v.position = objData.positions[corner[0]];
            v.textureCoordinates = objData.textureCoordinates[corner[1]];
            vertices.push_back(v);
        }
    }
}


OBJ &OBJParser::getObjData(){
    return objData;
}
const OBJ &OBJParser::getObjData() const{
    return objData;
}


std::vector<vertex> &OBJParser::getVertices(){
    return vertices;
}
const std::vector<vertex> &OBJParser::getVertices() const{
    return vertices;
}

OBJParser::~OBJParser()
{
}
