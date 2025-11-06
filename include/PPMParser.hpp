#pragma once
#include <string>
#include <memory>
#include <fstream>

class PPMParser
{
private:
    int height;
    int width;
    int chanMaxValue;
    int chanNum = 3;
    std::unique_ptr<unsigned char[]> pixelData;

public:
    unsigned char * getData();
    const unsigned char * getData() const;
    int getHeight();
    int getWidth();
    int getChanNum();
    PPMParser(const std::string &texturePath);
    ~PPMParser() = default;
};


