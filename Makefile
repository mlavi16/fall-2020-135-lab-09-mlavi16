
main: main.o 3d-space.o
	g++ -o main main.o 3d-space.o

tests: tests.o 3d-space.o
	g++ -o tests tests.o 3d-space.o

main.o: main.cpp 3d-space.h coord3d.h Particle.h

tests.o: tests.cpp doctest.h 3d-space.h coord3d.h Particle.h

3d-space.o: 3d-space.cpp 3d-space.h coord3d.h Particle.h

clean:
	rm -f main.o tests.o 3d-space.o

help:
	@echo  make main : make executable named main
	@echo make tests : make test suite named tests