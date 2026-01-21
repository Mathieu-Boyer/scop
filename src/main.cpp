#include "main.hpp"
#include "OBJParser.hpp"
#include "LinearAlgebra.hpp"

int main (int argc, char *argv[]){

    try {

        if (argc <= 1)
            throw std::runtime_error("You must at least provide a 3D model.");

        const std::string model(argv[1]);
        std::string texture("textures/kitty.ppm");

        if (argc == 3)
            texture = argv[2];

        if (model.empty() || texture.empty())
            throw std::runtime_error("Arguments can't be empty.");

        std::string modelFileExtension = model.substr(model.size() - 4);
        std::string textureFileExtension = texture.substr(texture.size() - 4);
    
        if (modelFileExtension != ".obj" || textureFileExtension != ".ppm")
            throw std::runtime_error("File Extension not accepted.");

        GLApp app(1080, 1080 , model, texture);
        app.render();

    } catch (std::exception &err){

        std::cerr << err.what() << "\n";
        return 1;
    }
}