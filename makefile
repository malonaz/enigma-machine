PROG:= enigma
CXX := g++
CXXFLAGS := -Wall -g

ROTOR_POS:= rotors/null.pos


enigma: main.o rotors.o sm.o enigma.o errors.o
	g++ -Wall -g -o enigma main.o rotors.o sm.o enigma.o errors.o

main.o: main.cpp rotors.h enigma.h
	g++ -Wall -g -c main.cpp 

rotors.o: rotors.cpp rotors.h sm.h errors.h
	g++ -Wall -g -c rotors.cpp 

sm.o: sm.cpp sm.h errors.h
	g++ -Wall -g -c sm.cpp

enigma.o: enigma.cpp enigma.h rotors.h errors.h
	g++ -Wall -g -c enigma.cpp 

errors.o: errors.cpp errors.h
	g++ -Wall -g -c errors.cpp 

clean:
	rm -f enigma *.o

test:
	make
	./enigma plugboards/I.pb reflectors/II.rf rotors/I.rot rotors/II.rot rotors/III.rot $(ROTOR_POS)

debug:
	gdb --args enigma plugboards/I.pb reflectors/II.rf rotors/I.rot rotors/II.rot rotors/III.rot rotors/II.pos

