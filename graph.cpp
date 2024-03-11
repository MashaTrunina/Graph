#include "graph.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <random>

const int MAX_VERTICES = 500;
const double K = 0.1; // коэффициент отталкивания
const double L= 100.0; // расстояние м/д вершинами
const double EPS = 1e-5; // сравнение с погрешностью


