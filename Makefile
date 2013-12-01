all:
	clear
	gcc main.cpp enemiesManager.cpp objClasses.cpp -o delderscrolls -lGLU -lGL -lglut -lstdc++ -lm