#include "Mesh.hpp"

Mesh::Mesh(const std::vector<vertex> &vertices, OBJ objData) : vertexCount(vertices.size()), objData(objData){
    // std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    // for (auto &v : vertices){
    //     std::cout << v.position.x << " " << v.position.y << " " << v.position.z <<  "            " << v.textureCoordinates.x << " " << v.textureCoordinates.y << "\n";

    // }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VEO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * vertexCount, &vertices[0], GL_STATIC_DRAW);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * objData.drawIndices.size(), &objData.drawIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, textureCoordinates));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void *)offsetof(vertex, normal));
    glEnableVertexAttribArray(3);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    // std::cout << objData.positions.size() << "\n";
    glDrawArrays(GL_TRIANGLES, 0, objData.drawIndices.size());

    // glDrawElements(GL_TRIANGLES, objData.drawIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

Mesh::~Mesh(){
    if (VBO) glDeleteBuffers(1, &VBO);
    if (VAO) glDeleteVertexArrays(1, &VAO);
}