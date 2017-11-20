

enigma: main.o stateMachine.o plugboard.o reflector.o rotor.o enigma.o errors.o helpers.o test.o plugboard_test.o reflector_test.o rotor_test.o
	g++ -Wall -g -o enigma $^

main.o: main.cpp enigma.h errors.h test.h
	g++ -Wall -g -c main.cpp

stateMachine.o: stateMachine.cpp stateMachine.h helpers.h errors.h
	g++ -Wall -g -c stateMachine.cpp

plugboard.o: plugboard.cpp plugboard.h stateMachine.h helpers.h errors.h
	g++ -Wall -g -c plugboard.cpp

reflector.o: reflector.cpp reflector.h stateMachine.h helpers.h errors.h
	g++ -Wall -g -c reflector.cpp

rotor.o: rotor.cpp rotor.h stateMachine.h helpers.h errors.h
	g++ -Wall -g -c rotor.cpp

enigma.o: enigma.cpp enigma.h stateMachine.h plugboard.h reflector.h rotor.h errors.h
	g++ -Wall -g -c enigma.cpp

helpers.o: helpers.cpp helpers.h
	g++ -Wall -g -c helpers.cpp

errors.o: errors.cpp errors.h
	g++ -Wall -g -c errors.cpp

test.o: test.cpp test.h plugboard_test.o reflector_test.o rotor_test.o
	g++ -Wall -g -c test.cpp

plugboard_test.o: plugboard_test.cpp plugboard_test.h plugboard.h errors.h helpers.h
	g++ -Wall -g -c plugboard_test.cpp

reflector_test.o: reflector_test.cpp reflector_test.h reflector.h errors.h helpers.h
clean:
	rm *.o enigma

rotor_test.o: rotor_test.cpp rotor_test.h rotor.h errors.h helpers.h
	g++ -Wall -g -c rotor_test.cpp
test:
	./enigma tests/test00/plugboard.pb tests/test00/reflector.rf tests/test00/rotor.rot tests/test00/rotor2.rot tests/test00/rotor3.rot tests/test00/rotor.pos

#./enigma tests/test04/plugboard.pb tests/test04/reflector.rf tests/test04/rotor.rot tests/test04/rotor2.rot tests/test04/rotor.pos
