#include "main.hpp"
#include "OBJParser.hpp"
#include "LinearAlgebra.hpp"

int main (){
    try {
        GLApp app(800, 800, "Scop", "models/plant.obj", "textures/plant.ppm");
        app.render();
    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }
}