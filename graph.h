#ifndef GRAPH_H
#define Graph_H

#include <vector>
#include <string>

struct Vertex {
double x, y;
std:: vector <int> pair;
};

void readGraph(std::string filename, std::vector<Vertex>& vertices);
void saveBMP(const std::vector<Vertex>& vertices, const std::string& filename);

#endif // GRAPH_H
