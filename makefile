PROG:= enigma
CXX := g++
CXXFLAGS := -Wall -g

ROTOR_POS:= rotors/null.pos


enigma: main.o sm.o reflector.o rotors.o enigma.o errors.o
	g++ -Wall -g -o enigma main.o sm.o reflector.o rotors.o enigma.o errors.o

main.o: main.cpp enigma.h errors.h
	g++ -Wall -g -c main.cpp 

sm.o: sm.cpp sm.h errors.h
	g++ -Wall -g -c sm.cpp

reflector.o: reflector.cpp reflector.h sm.h errors.h
	g++ -Wall -g -c reflector.cpp

rotors.o: rotors.cpp rotors.h sm.h errors.h
	g++ -Wall -g -c rotors.cpp 

enigma.o: enigma.cpp enigma.h reflector.h rotors.h errors.h
	g++ -Wall -g -c enigma.cpp 

errors.o: errors.cpp errors.h
	g++ -Wall -g -c errors.cpp 




clean:
	rm -f enigma *.o

tester:	test.o sm.o rotors.o reflector.o enigma.o errors.o
	g++ -Wall -g -o tester test.o sm.o rotors.o reflector.o enigma.o errors.o

test.o: test.cpp enigma.h errors.h
	g++ -Wall -g -c test.cpp

test: tester
	make tester
	clear	
	./tester
