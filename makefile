PROG:= enigma
CXX := g++
CXXFLAGS := -Wall -g

enigma: src/main.o src/rotors.o 
	g++ -Wall -g -o enigma src/main.o src/rotors.o

src/main.o: src/main.cpp include/rotors.h 
	g++ -Wall -g -c src/main.cpp -o src/main.o

src/rotors.o: src/rotors.cpp include/sm.h include/rotors.h
	g++ -Wall -g -c src/rotors.cpp -o src/rotors.o

clean:
	rm -f enigma src/*.o

