#include "TXTReader.h"

#include <iostream>
#include <fstream>

void readInputFromFile(const std::string& filename, int& numVertices, int& width, int& height, std::vector<Edge>& edges) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> numVertices >> width >> height;
        int vertex1, vertex2;
        while (file >> vertex1 >> vertex2) {
            edges.push_back({ static_cast<size_t>(vertex1), static_cast<size_t>(vertex2) });
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}





