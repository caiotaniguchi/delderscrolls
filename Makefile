all:
	clear
	gcc main.cpp camera.cpp objClasses.cpp -o game -lGLU -lGL -lglut -lstdc++ -lm