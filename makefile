

enigma: main.o stateMachine.o plugboard.o reflector.o rotors.o enigma.o errors.o helpers.o test.o plugboard_test.o
	g++ -Wall -g -o enigma $^

main.o: main.cpp enigma.h errors.h test.h
	g++ -Wall -g -c main.cpp

stateMachine.o: stateMachine.cpp stateMachine.h helpers.h errors.h
	g++ -Wall -g -c stateMachine.cpp

plugboard.o: plugboard.cpp plugboard.h stateMachine.h helpers.h errors.h
	g++ -Wall -g -c plugboard.cpp

reflector.o: reflector.cpp reflector.h stateMachine.h helpers.h errors.h
	g++ -Wall -g -c reflector.cpp

rotors.o: rotors.cpp rotors.h stateMachine.h helpers.h errors.h
	g++ -Wall -g -c rotors.cpp

enigma.o: enigma.cpp enigma.h stateMachine.h plugboard.h reflector.h rotors.h errors.h
	g++ -Wall -g -c enigma.cpp

helpers.o: helpers.cpp helpers.h
	g++ -Wall -g -c helpers.cpp

errors.o: errors.cpp errors.h
	g++ -Wall -g -c errors.cpp


test.o: test.cpp test.h plugboard.h reflector.h rotors.h enigma.h
	g++ -Wall -g -c test.cpp

plugboard_test.o: plugboard_test.cpp plugboard_test.h errors.h helpers.h
	g++ -Wall -g -c plugboard_test.cpp

clean:
	rm *.o enigma


test:
	./enigma tests/test00/plugboard.pb tests/test00/reflector.rf tests/test00/rotor.rot tests/test00/rotor2.rot tests/test00/rotor3.rot tests/test00/rotor.pos

#./enigma tests/test04/plugboard.pb tests/test04/reflector.rf tests/test04/rotor.rot tests/test04/rotor2.rot tests/test04/rotor.pos
