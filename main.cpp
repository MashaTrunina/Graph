#include <iostream>
#include "BMPCreate.h"
#include "TXTReader.h"

template<typename T>
std::string to_string(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}
int main() {
    int numVertices, width, height;
    std::vector<Edge> edges;
    readInputFromFile("input.txt", numVertices, width, height, edges);

    std::vector<Vertex> vertices;

    srand(time(NULL));
    for (int i = 0; i < numVertices; ++i) {
        vertices.push_back({ rand() % width, rand() % height, to_string(i) });
    }

    BMPGenerator bmpGenerator(width, height, vertices, edges);
    bmpGenerator.generate("graph.bmp");

    return 0;
}
    
