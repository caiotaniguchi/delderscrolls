all:
	clear
	gcc main.cpp objClasses.cpp -o delderscrolls -lGLU -lGL -lglut -lstdc++ -lm