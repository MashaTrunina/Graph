#include <fstream>
#include <cmath>
#include "BMPGenerator.h"

BMPGenerator::BMPGenerator(int width, int height, const std::vector<Vertex>& vertices, const std::vector<Edge>& edges)
    : m_width(width), m_height(height), m_vertices(vertices), m_edges(edges) {}

void BMPGenerator::generate(const std::string& filename) {
 std::ofstream file(filename, std::ios::binary);
 writeHeader(file);
 writeImageData(file);
 file.close();
}
