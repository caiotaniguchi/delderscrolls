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

/*
 * use: objModel[face][vertex].coordinate
 * To draw a model, make:
 * for (int i = 0; i < objModel.size(); i++)
 *   for (int j = 0; j < objModel[i].size(); j++)
 *     glVertex3f(objModel[i][j].x, objModel[i][j].y, objModel[i][j].z)
 */
vector<vector<vertex> > objModel;

// Converts a string to type T
template <class T>
T fromStr(std::string s){
   std::istringstream st(s);
   T result;
   st >> result;
   return result;
}

 
// Reads a .obj file. Saves all the vertex and face in objModel
int import_model (string fileName) {
	ifstream objFile(fileName.c_str());
	if(!objFile.is_open()) // Returns if file can't be read.
		return 1;
	
	vector<vertex> vertexList;

	// Reads the file until the EOF
	while(!objFile.eof()) {
		string line;
		int linePos;
 
		getline(objFile, line);
		// Searches for the first vertex
		while (line.find("v ") == string::npos)
			getline(objFile, line);
		
		// Adds all vertex to the vertex list 
		while (line.find('v') != string::npos) {
			vertex newVertex;
			line = line.substr(2, line.size());
			linePos = line.find(' ');
			newVertex.x = fromStr<float>(line.substr(0, linePos));
			line = line.substr(linePos+1);
			linePos = line.find(' ');
			newVertex.y = fromStr<float>(line.substr(0, linePos));
			line = line.substr(linePos+1);
			newVertex.z = fromStr<float>(line);
			vertexList.push_back(newVertex);
			getline(objFile, line);
		}
      
		// Skips all lines until it finds the first face
		while (line.find("f ") == string::npos) 
			getline(objFile, line);
		
		// Adds all faces to the objModel
		while (line.find('f') != string::npos) {
			vector<vertex> newFace;
			unsigned index;

			// Skips "f "
			line = line.substr(2, line.size());
			linePos = line.find(' ');
						
			// Adds a new face to the objModel
			while (linePos != string::npos) {
				index = fromStr<int>(line.substr(0, linePos));
				newFace.push_back(vertexList[index-1]);
				line = line.substr(linePos+1);
				linePos = line.find(' ');
			}
			index = fromStr<int>(line.substr(0, line.size()));
			newFace.push_back(vertexList[index-1]);
			line = line.substr(linePos+1);
			
			objModel.push_back(newFace);
			getline(objFile, line);
		}
	}
	objFile.close();
	return 0;
}



int main (void) {
	int error;
	error = import_model ("cube.obj");
	if (error != 0)
		return error;
	
	for (unsigned i = 0; i < objModel.size(); i++) {
		for (unsigned j = 0; j < objModel[i].size(); j++)
			cout << objModel[i][j].x << " " << objModel[i][j].y << " " << objModel[i][j].z << endl;
		cout << endl;
	}
	return 0;
}
