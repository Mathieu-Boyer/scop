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

    LinearAlgebra::vec3 v = {1,2,3};
    LinearAlgebra::vec3 v2 = {1,2,3};
    // LinearAlgebra::mat4 m = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
    LinearAlgebra::vec3 res = v + v2;

    std::cout << res.x << " " << res.y << " " << res.z << "\n";

}