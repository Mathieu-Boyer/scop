#include "OBJParser.hpp"
#include <iostream>
#include <sstream>
#include <charconv>

////// move to utils later ///


int count(char toCount, const std::string& src){
    int counter = 0;
    for (auto &c : src)
        if (c == toCount) counter++;

    return counter;
}

static void facesTriangulation ( std::map<std::string, std::vector<std::string>> &_data, const std::string_view &value) {
    unsigned int v1 = 0, v2 = 1, v3 = 2;
    size_t j = 0;
    std::vector<std::string_view> indices;

    while (j < value.size()) {
        while (j < value.size() && value[j] == ' ') j++;
        size_t wordStart = j;
        while (j < value.size() && value[j] != ' ') j++;

        if (wordStart < j)
            indices.push_back(value.substr(wordStart, j - wordStart));
    }

    while (v3 < indices.size()) {
        std::string faceLine =
            std::string(indices[v1]) + " " +
            std::string(indices[v2]) + " " +
            std::string(indices[v3]);
        v2++;
        v3++;
        _data["f"].push_back(std::move(faceLine));
    }
}


OBJParser::OBJParser(const std::string &filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file)
        throw std::runtime_error("Failed to open file.");

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string buffer(size, '\0');
    file.read(buffer.data(), size);
    file.close();

    size_t lineStart = 0;
    for (size_t pos = 0; pos <= buffer.size(); ++pos) {
        if (pos == buffer.size() || buffer[pos] == '\n' || buffer[pos] == '\r') {
            if (pos == lineStart) {
                lineStart = pos + 1;
                continue;
            }
            std::string_view line(&buffer[lineStart], pos - lineStart);
            lineStart = pos + 1;
            size_t cursor = 0;
            while (cursor < line.size() && line[cursor] == ' ')
                cursor++;
            if (cursor >= line.size() || line[cursor] == '#')
                continue;
            size_t keyStart = cursor;
            while (cursor < line.size() && line[cursor] != ' ')
                cursor++;
            std::string_view key = line.substr(keyStart, cursor - keyStart);
            while (cursor < line.size() && line[cursor] == ' ')
                cursor++;

            std::string_view value = (cursor < line.size()) ? line.substr(cursor) : std::string_view();
            if (key == "f")
                facesTriangulation(_data, value);
            else
                _data[std::string(key)].push_back(std::string(value));
        }
    }
    convertToVectors();
    createVertices();
}

void OBJParser::handlePositions(){
    auto &verts = _data["v"];
    objData.positions.reserve(verts.size());

    for (const auto &line : verts) {
        std::string_view sv(line);
        float xyz[3];
        int wordCounter = 0;
        size_t i = 0;

        while (i < sv.size() && wordCounter < 3) {
            while (i < sv.size() && sv[i] == ' ')
                i++;
            if (i >= sv.size())
                break;
            size_t start = i;
            while (i < sv.size() && sv[i] != ' ')
                i++;
            xyz[wordCounter++] = std::strtof(sv.substr(start, i - start).data(), nullptr);
        }

        if (wordCounter != 3)
            throw std::runtime_error("Invalid vertex line: expected 3 floats.");

        Xmin = std::min(Xmin, xyz[0]);
        Xmax = std::max(Xmax, xyz[0]);
        Ymin = std::min(Ymin, xyz[1]);
        Ymax = std::max(Ymax, xyz[1]);
        Zmin = std::min(Zmin, xyz[2]);
        Zmax = std::max(Zmax, xyz[2]);

        objData.positions.emplace_back(xyz[0], xyz[1], xyz[2]);
    }

    LinearAlgebra::vec3 offset((Xmin + Xmax) * 0.5f,
                     (Ymin + Ymax) * 0.5f,
                     (Zmin + Zmax) * 0.5f);

    for (auto &pos : objData.positions)
        pos = pos - offset;
}

void OBJParser::handleNormals(){
    auto &vn = _data["vn"];
    objData.normals.reserve(vn.size());

    for (const auto &line : vn) {
        std::string_view sv(line);
        float xyz[3];
        int wordCounter = 0;
        size_t i = 0;

        while (i < sv.size() && wordCounter < 3) {
            while (i < sv.size() && sv[i] == ' ')
                i++;
            if (i >= sv.size())
                break;
            size_t start = i;
            while (i < sv.size() && sv[i] != ' ')
                i++;
            xyz[wordCounter++] = std::strtof(sv.substr(start, i - start).data(), nullptr);
        }

        if (wordCounter != 3)
            throw std::runtime_error("Invalid normal line: expected 3 floats.");

        objData.normals.emplace_back(xyz[0], xyz[1], xyz[2]);
    }
}

void OBJParser::handleFaces(){
    auto &faces = _data["f"];
    objData.faces.reserve(faces.size());
    for (const auto &line : faces) {
        Face face;
        face.corners.reserve(3);

        std::string_view sv(line);
        size_t i = 0;

        while (i < sv.size()) {
            while (i < sv.size() && sv[i] == ' ')
                i++;
            if (i >= sv.size())
                break;

            size_t start = i;
            while (i < sv.size() && sv[i] != ' ')
                i++;

            std::string_view token = sv.substr(start, i - start);
            if (token.empty())
                continue;

            std::array<int, 3> vert{-1, -1, -1};
            int part = 0;
            size_t p = 0;
            while (p < token.size() && part < 3) {
                size_t slash = token.find('/', p);
                if (slash == std::string_view::npos) slash = token.size();

                if (slash > p) {
                    int idx = std::atoi(token.substr(p, slash - p).data());
                    vert[part] = idx - 1;
                }
                p = slash + 1;
                part++;
            }

            if (vert[0] == -1)
                throw std::runtime_error("Invalid face: missing vertex index.");

            face.corners.push_back(vert);
            objData.drawIndices.push_back(vert[0]);
        }
        objData.faces.push_back(std::move(face));
    }
}

void OBJParser::handleTextureCoordinates(){
    auto &tex   = _data["vt"];
    objData.textureCoordinates.reserve(tex.size());
    for (const auto &line : tex) {
        std::string_view sv(line);
        float uv[2];
        int count = 0;
        size_t i = 0;

        while (i < sv.size() && count < 2) {
            while (i < sv.size() && sv[i] == ' ')
                i++;
            if (i >= sv.size())
                break;

            size_t start = i;
            while (i < sv.size() && sv[i] != ' ')
                i++;

            uv[count++] = std::strtof(sv.substr(start, i - start).data(), nullptr);
        }

        if (count != 2)
            throw std::runtime_error("Invalid texture coordinate line.");

        objData.textureCoordinates.emplace_back(uv[0], uv[1]);
    }
}

const LinearAlgebra::vec3 OBJParser::scalingVector() const{
    float sizeX = Xmax - Xmin ;
    float sizeY = Ymax - Ymin ;
    float sizeZ = Zmax - Zmin ;
    float target = 2.0f;
    float largetDim = std::max(std::max(sizeX, sizeY), sizeZ);

    return {target/largetDim, target/largetDim, target/largetDim};
}

void OBJParser::convertToVectors() {
    handlePositions();
    handleNormals();
    handleFaces();
    handleTextureCoordinates();
}

void OBJParser::createVertices() {
    vertices.reserve(objData.faces.size() * 3);

    float dx = Xmax - Xmin;
    float dy = Ymax - Ymin;

    unsigned int faceIndex = 0;
    for (const auto &face : objData.faces) {
        float faceBaseColor = 0.3f + (static_cast<float>(faceIndex % 50) / 100.0f);
        unsigned int cornerIndex = 0;
        // unsigned int faceStart = 0;
        for (const auto &corner : face.corners) {
            vertex vert;
            float vertexColor = faceBaseColor + ((cornerIndex / 10.0f) - 0.1f);
            vert.position = objData.positions[corner[0]];

            if (corner[1] >= 0 && corner[1] < static_cast<int>(objData.textureCoordinates.size()))
                vert.textureCoordinates = objData.textureCoordinates[corner[1]];
            else {
                float u = (vert.position.x - Xmin) / dx;
                float v = (vert.position.y - Ymin) / dy;
                vert.textureCoordinates = LinearAlgebra::vec2(u, v);
            }

            if (corner[2] >= 0 && corner[2] < static_cast<int>(objData.normals.size()))
                vert.normal = objData.normals[corner[2]];



            vert.color = LinearAlgebra::vec3(vertexColor, vertexColor, vertexColor);
            vertices.push_back(vert);

            // std::cout << cornerIndex << "\n";

            if (cornerIndex == 2){
                auto &v0 = vertices[vertices.size()-1 - 2];
                auto &v1 = vertices[vertices.size()-1 - 1];
                auto &v2 = vertices[vertices.size()-1 - 0];

                auto e1 = v1.position - v0.position;
                auto e2 = v2.position - v0.position;

                auto faceNormal = LinearAlgebra::normalize(LinearAlgebra::cross(e1, e2));

                v0.normal = faceNormal;
                v1.normal = faceNormal;
                v2.normal = faceNormal;
            }

            ++cornerIndex;
        }

        ++faceIndex;
    }
}


OBJ &OBJParser::getObjData(){
    return objData;
}
const OBJ &OBJParser::getObjData() const{
    return objData;
}


std::vector<vertex> &OBJParser::getVertices(){
    return vertices;
}
const std::vector<vertex> &OBJParser::getVertices() const{
    return vertices;
}

OBJParser::~OBJParser()
{
}
