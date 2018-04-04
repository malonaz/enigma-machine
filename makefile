CXX = g++
CXXFLAGS = -g -Wall -MMD

################################### MAIN ###################################mv 
EXE = enigma
OBJS = main.o stateMachine.o plugboard.o reflector.o rotor.o enigma.o helpers.o errors.o

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(OBJS:.o=.d)



################################### TESTER ################################
TEST = tester
TEST_OBJS = test.o plugboard_test.o reflector_test.o rotor_test.o

$(TEST): $(TEST_OBJS) $(filter-out main.o, $(OBJS))
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(TEST_OBJS:.o=.d)


################################### PHONY #################################
.PHONY: clean clean_dep

clean:
	rm -rf $(OBJS) $(EXE)

clean_dep:
	rm -rf $(OBJS:.o=.d)
