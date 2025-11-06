#include "main.hpp"

int main (){
    try {
        GLApp app(800, 800, "Scop");
        app.setShaders(std::make_unique<Shaders>("shaders/default.vs", "shaders/default.fs"));
        app.render();
    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }
}