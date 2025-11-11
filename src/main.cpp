#include "main.hpp"
#include "OBJParser.hpp"

int main (){
    try {

        GLApp app(800, 800, "Scop");
        app.render();

    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }
}