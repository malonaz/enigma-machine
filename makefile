PROG:= enigma
CXX := g++
CXXFLAGS := -Wall -g

ROTOR_POS:= inputs/rotors/null.pos


enigma: main.o rotors.o sm.o enigma.o
	g++ -Wall -g -o enigma main.o rotors.o sm.o enigma.o

main.o: main.cpp rotors.h enigma.h
	g++ -Wall -g -c main.cpp -o main.o

rotors.o: rotors.cpp rotors.h sm.h 
	g++ -Wall -g -c rotors.cpp -o rotors.o 

sm.o: sm.cpp sm.h errors.h
	g++ -Wall -g -c sm.cpp -o sm.o

enigma.o: enigma.cpp enigma.h rotors.h 
	g++ -Wall -g -c enigma.cpp -o enigma.o

clean:
	rm -f enigma *.o

test:
	make
	./enigma inputs/plugboards/I.pb inputs/reflectors/II.rf inputs/rotors/I.rot inputs/rotors/II.rot inputs/rotors/III.rot $(ROTOR_POS)

debug:
	gdb --args enigma inputs/plugboards/I.pb inputs/reflectors/II.rf inputs/rotors/I.rot inputs/rotors/II.rot inputs/rotors/III.rot inputs/rotors/II.pos

