PROG:= enigma
CXX := g++
CXXFLAGS := -Wall -g

ROTOR_POS:= inputs/rotors/null.pos


enigma: src/main.o src/rotors.o src/sm.o src/enigma.o
	g++ -Wall -g -o enigma src/main.o src/rotors.o src/sm.o src/enigma.o

src/main.o: src/main.cpp include/rotors.h include/enigma.h
	g++ -Wall -g -c src/main.cpp -o src/main.o

src/rotors.o: src/rotors.cpp include/rotors.h include/sm.h 
	g++ -Wall -g -c src/rotors.cpp -o src/rotors.o 

src/sm.o: src/sm.cpp include/sm.h include/errors.h
	g++ -Wall -g -c src/sm.cpp -o src/sm.o

src/enigma.o: src/enigma.cpp include/enigma.h include/rotors.h 
	g++ -Wall -g -c src/enigma.cpp -o src/enigma.o

clean:
	rm -f enigma src/*.o

test:
	make
	./enigma inputs/plugboards/I.pb inputs/reflectors/II.rf inputs/rotors/I.rot inputs/rotors/II.rot inputs/rotors/III.rot $(ROTOR_POS)

debug:
	gdb --args enigma inputs/plugboards/I.pb inputs/reflectors/II.rf inputs/rotors/I.rot inputs/rotors/II.rot inputs/rotors/III.rot inputs/rotors/II.pos

