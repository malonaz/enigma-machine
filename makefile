PROG:= enigma
CXX := g++
CXXFLAGS := -Wall -g

enigma: src/main.o src/rotors.o src/sm.o src/enigma.o
	g++ -Wall -g -o enigma src/main.o src/rotors.o src/sm.o

src/main.o: src/main.cpp include/rotors.h 
	g++ -Wall -g -c src/main.cpp -o src/main.o

src/rotors.o: src/rotors.cpp include/rotors.h include/sm.h 
	g++ -Wall -g -c src/rotors.cpp -o src/rotors.o 

src/sm.o: src/sm.cpp include/sm.h 
	g++ -Wall -g -c src/sm.cpp -o src/sm.o

src/enigma.o: src/enigma.cpp include/enigma.h include/rotors.h

clean:
	rm -f enigma src/*.o

