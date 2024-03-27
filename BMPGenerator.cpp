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
void BMPGenerator::writeHeader(std::ofstream& file) {
    int imageDataSize = m_width * m_height * 3;


    file.put('B').put('M');
    writeInt(file, 14 + 40 + imageDataSize);
    writeInt(file, 0);
    writeInt(file, 14 + 40);


    writeInt(file, 40);
    writeInt(file, m_width);
    writeInt(file, m_height);
    writeShort(file, 1);
    writeShort(file, 24);
    writeInt(file, 0);
    writeInt(file, imageDataSize);
    writeInt(file, 2835);
    writeInt(file, 2835);
    writeInt(file, 0);
    writeInt(file, 0);
}

void BMPGenerator::writeImageData(std::ofstream& file) {
    std::vector<std::vector<bool>> bitmap(m_height, std::vector<bool>(m_width, false));

    for (const auto& edge : m_edges) {
        drawLine(bitmap, m_vertices[edge.vertex1].x, m_vertices[edge.vertex1].y,
            m_vertices[edge.vertex2].x, m_vertices[edge.vertex2].y);
    }

    for (size_t i = 0; i < m_vertices.size(); ++i) {
        drawCircle(bitmap, m_vertices[i].x, m_vertices[i].y);
    }

    for (int y = m_height - 1; y >= 0; --y) {
        for (int x = 0; x < m_width; ++x) {

            file.put(bitmap[y][x] ? static_cast<char>(0) : static_cast<char>(255))
                .put(bitmap[y][x] ? static_cast<char>(0) : static_cast<char>(255))
                .put(bitmap[y][x] ? static_cast<char>(0) : static_cast<char>(255));
        }
    }
}

void BMPGenerator::drawLine(std::vector<std::vector<bool>>& bitmap, int x0, int y0, int x1, int y1) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;

    while (x0 != x1 || y0 != y1) {
        if (x0 >= 0 && x0 < m_width && y0 >= 0 && y0 < m_height) {
            bitmap[y0][x0] = true;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void BMPGenerator::drawCircle(std::vector<std::vector<bool>>& bitmap, int xc, int yc) {
    for (int y = yc - 5; y <= yc + 5; ++y) {
        for (int x = xc - 5; x <= xc + 5; ++x) {
            if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
                double distance = std::sqrt((x - xc) * (x - xc) + (y - yc) * (y - yc));
                if (distance <= 5) {
                    bitmap[y][x] = true;
                }
            }
        }
    }
}

void BMPGenerator::writeInt(std::ofstream& file, int value) {
    file.put(static_cast<char>(value & 0xFF))
        .put(static_cast<char>((value >> 8) & 0xFF))
        .put(static_cast<char>((value >> 16) & 0xFF))
        .put(static_cast<char>((value >> 24) & 0xFF));
}

void BMPGenerator::writeShort(std::ofstream& file, short value) {
    file.put(static_cast<char>(value & 0xFF))
        .put(static_cast<char>((value >> 8) & 0xFF));
}

