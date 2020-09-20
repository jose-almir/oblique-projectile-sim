all:
	g++ -o main main.cpp geometry.cpp graphics.cpp physics.cpp -lGL -lGLU -lglut -lm
run:
	./main
