all:
	clear
	gcc main.cpp dinamicObjManager.cpp objClasses.cpp util.cpp terrain.cpp -o delderscrolls -lGLU -lGL -lglut -lstdc++ -lm 