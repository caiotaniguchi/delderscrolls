all:
	clear
	gcc main.cpp enemiesManager.cpp objClasses.cpp terrain.cpp -o delderscrolls -lGLU -lGL -lglut -lstdc++ -lm