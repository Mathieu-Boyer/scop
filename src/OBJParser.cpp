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

        if (key == "f"){
            // _data[key].push_back(value);
            unsigned int i = 0;
            unsigned int j = 1;
            unsigned int k = 2;

            std::vector<std::string> indices = split(value, ' ');

            while (k < indices.size()){
                _data[key].push_back(indices[i] + " " + indices[j] + " " + indices[k]);
                j++;
                k++;
            }
        }
        else
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

        Xmin = std::min(Xmin, xyz[0]);
        Xmax = std::max(Xmax, xyz[0]);
        Ymin = std::min(Ymin, xyz[1]);
        Ymax = std::max(Ymax, xyz[1]);
        Zmin = std::min(Zmin, xyz[2]);
        Zmax = std::max(Zmax, xyz[2]);


        objData.positions.push_back(glm::vec3(xyz[0],xyz[1] ,xyz[2]));
    }


    for (unsigned int i = 0; i < objData.positions.size(); i++){
        objData.positions[i].x -= ((Xmin + Xmax) * .5f);
        objData.positions[i].y -= ((Ymin + Ymax) * .5f);
        objData.positions[i].z -= ((Zmin + Zmax) * .5f);
    }
    std::cout << Xmin << " " << Xmax << " " << Ymin << " " << Ymax << "\n";
    for (auto &str : _data["f"]){
        Face face;
        // int wordCounter = 0;
        std::string current;

        std::istringstream word(str);

        while (word >> current){
            std::vector<std::string> position_textureCoordinates (split(current, '/'));
            std::array<int, 2> faceVertex {-1,-1};


            faceVertex[0] = std::stoi(position_textureCoordinates[0] )- 1 ;

            if (position_textureCoordinates.size() == 2)
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
        
    // for (auto &vpos :  objData.positions)
    //     std::cout << vpos.x << " " << vpos.y << " " << vpos.z << "\n";
    // for (auto &vpos :  objData.textureCoordinates)
    //     std::cout << vpos.x << " " << vpos.y << "\n";
}


void OBJParser::createVertices(){
    for (auto &face : objData.faces){
        for (auto &corner : face.corners){
            vertex vert;

            
            vert.position = objData.positions[corner[0]];
            // std::cout << "meow" << corner[1] <<  std::endl;
            if (corner.at(1) > -1)
                vert.textureCoordinates = objData.textureCoordinates[corner[1]];
            else {
                float u = (vert.position.x - Xmin) / (Xmax - Xmin); 
                float v = (vert.position.y - Ymin) / (Ymax - Ymin);
                vert.textureCoordinates = glm::vec2(u,v);
            }
            vertices.push_back(vert);
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
