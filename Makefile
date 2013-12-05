all:
	clear
	gcc -o delderscrolls main.cpp dinamicObjManager.cpp objClasses.cpp loadObj.cpp util.cpp terrain.cpp -lGLU -lGL -lglut -lstdc++ -lm 

	#gcc -o loadOBJ loadObj.cpp -lGLU -lGL -lglut -lstdc++ -lm 