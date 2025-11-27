#include "main.hpp"
#include "OBJParser.hpp"
#include "LinearAlgebra.hpp"

int main (){
    try {


        const std::string model("models/42.obj");
        const std::string texture("textures/wood.ppm");
        const std::string windowName("Scop");
        GLApp app(800, 800, model, texture);
        app.render();
    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }
}