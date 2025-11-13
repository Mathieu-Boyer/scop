#include "main.hpp"
#include "OBJParser.hpp"
#include "LinearAlgebra.hpp"

int main (){
    try {
        // GLApp app(800, 800, "Scop");
        // app.render();

        /// tests go under there ///
        
    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }

    LinearAlgebra::mat4 lhs(1);
    LinearAlgebra::vec3 sf = {2,3,1};

    LinearAlgebra::mat4 scaled = LinearAlgebra::scale(lhs, sf);

    for (unsigned i = 0; i < 4; i++){
        for (unsigned j = 0; j < 4; j++)
            std::cout << scaled.data[(4 * i) + j] << " ";
        std::cout << "\n";
    }


}