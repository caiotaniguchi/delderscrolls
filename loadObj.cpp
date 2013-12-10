#include <string>
#include <vector>
#include <fstream>
#include <sstream>

// Soh usado para testes
#include <iostream>
#include "loadObj.h"

using namespace std;

/*
 * use: objModel[triangle][vertex].coordinate
 * To draw a model, make:
 * for (int i = 0; i < objModel.size(); i++)
 *   for (int j = 0; j < objModel[i].size(); j++)
 *     glVertex3f(objModel[i][j].x, objModel[i][j].y, objModel[i][j].z)
 */

/*
 * use: objModel[part][triangle][vertex].coordinate
 * To draw a model, make:
 * for (int i = 0; i < objModel.size(); i++)
 *   for (int j = 0; j < objModel[i].size(); j++)
 *     for (int k = 0; k < objModel[i][j].size(); k++)
 *       glVertex3f(objModel[i][j][k].x, objModel[i][j][k].y, objModel[i][j][k].z);
 */



// Converts a strging to type T
template <class T>
T fromStr(std::string s){
   std::istringstream st(s);
   T result;
   st >> result;
   return result;
}

vector<vector<vector<vertex> > > objModel;
vector <vector<vertex> > rockModel;

// Reads a list of .obj file. Saves all the parts' vertex and triangles in objModel
int import_model (vector<string> files) {
	for (int fileNum = 0; fileNum < files.size(); fileNum++) {
		ifstream objFile(files[fileNum].c_str());
		if(!objFile.is_open()) // Returns if file can't be read.
			return 1;

		// Reads the file until the EOF
		while(!objFile.eof()) {
			string line;
			int linePos;
			vector<vector<vertex> > objPart;
			vector<vertex> vertexList;

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

			// Skips all lines until it finds the first triangle
			while (line.find("f ") == string::npos)
				getline(objFile, line);

			// Adds all triangles to the objPart
			while (line.find('f') != string::npos) {
				vector<vertex> newTriangle;
				vertex tempVertex;
				unsigned index;

				// Skips "f "
				line = line.substr(2, line.size());
				linePos = line.find(' ');

				// Adds a new triangle to the objPart
				while (linePos != string::npos) {
					index = fromStr<int>(line.substr(0, linePos));
					newTriangle.push_back(vertexList[index-1]);
					line = line.substr(linePos+1);
					linePos = line.find(' ');
				}
				index = fromStr<int>(line.substr(0, line.size()));
				newTriangle.push_back(vertexList[index-1]);
				line = line.substr(linePos+1);
				tempVertex = newTriangle[0];
				newTriangle[0] = newTriangle[2];
				newTriangle[2] = tempVertex;

				objPart.push_back(newTriangle);
				getline(objFile, line);
			}
            objModel.push_back(objPart);
		}
		objFile.close();
	}

	return 0;
}

//int main (void) {

//    return 0;
//}

