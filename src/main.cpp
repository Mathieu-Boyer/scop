#include "main.hpp"
#include "OBJParser.hpp"
#include "LinearAlgebra.hpp"

int main (int argc, char *argv[]){
    if (argc <= 1){
        std::cerr << "Arguments can't be empty.\n";
        return 1;
    }
    std::string texture("textures/wood.ppm");
    if (argc == 3)
        texture = argv[2];
    
    const std::string model(argv[1]);
    try {
        GLApp app(1080, 1080 , model, texture);
        app.render();
    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }
}