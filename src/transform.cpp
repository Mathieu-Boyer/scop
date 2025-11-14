#include "transform.hpp"

transform::transform() : rotation(0.0f), translation(0.0f), scale(1.f){}

LinearAlgebra::mat4 transform::getModelMatrix() const{
    LinearAlgebra::mat4 model = LinearAlgebra::mat4(1.0f);
    model = LinearAlgebra::scale(model, scale);
    model = LinearAlgebra::rotate(model, degToRad(rotation.x), LinearAlgebra::vec3(1,0,0));
    model = LinearAlgebra::rotate(model, degToRad(rotation.y), LinearAlgebra::vec3(0,1,0));
    model = LinearAlgebra::rotate(model, degToRad(rotation.z), LinearAlgebra::vec3(0,0,1));
    model = LinearAlgebra::translate(model, translation);
    return model;
}