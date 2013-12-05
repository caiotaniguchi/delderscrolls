all:
	clear
	gcc -o delderscrolls main.cpp dinamicObjManager.cpp objClasses.cpp util.cpp terrain.cpp -lGLU -lGL -lglut -lstdc++ -lm 