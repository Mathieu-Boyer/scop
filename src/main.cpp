#include "main.hpp"
#include "OBJParser.hpp"

int main (){
    try {
        OBJParser ("models/basic.obj");
        // GLApp app(800, 800, "Scop");
        // app.render();

    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }
}