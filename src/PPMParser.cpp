#include "PPMParser.hpp"
#include "iostream"


PPMParser::PPMParser(const std::string &texturePath){
    std::ifstream file (texturePath, std::ios::binary);
    if (!file)
        throw std::runtime_error("Texture : " + texturePath + " not found.");

    std::string fileType;
    file >> fileType;

    if (fileType != "P6")
        throw std::runtime_error(fileType + " not supported.");
    
    file >> width >> height >> chanMaxValue;

    if (chanMaxValue != 255)
        throw std::runtime_error("chanelMaxValue not supported.");

    file.get();
    size_t dataSize = (static_cast<size_t>(width) * height * chanNum);
    pixelData = std::make_unique<unsigned char[]>(dataSize);
    file.read(reinterpret_cast<char *>(pixelData.get()), dataSize);
}

unsigned char * PPMParser::getData(){
    return pixelData.get();
}
const unsigned char * PPMParser::getData() const{
    return pixelData.get();
}

int PPMParser::getHeight(){
    return height;
}
int PPMParser::getWidth(){
    return width;
}
int PPMParser::getChanNum(){
    return chanNum;
}


    