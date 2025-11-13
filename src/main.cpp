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

    LinearAlgebra::vec4 v = {1,2,3,4};
    LinearAlgebra::mat4 m = {1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4};
    LinearAlgebra::vec4 res = LinearAlgebra::dot(m, v);

    std::cout << res.x << " " << res.y << " " << res.z << " " << res.w  << "\n";

}