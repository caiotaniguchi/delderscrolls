#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// Soh usado para testes
#include <iostream>

using namespace std;

struct vertex {
	float x;
	float y;
	float z;
};

int import_model (string fileName);