CXX = g++
CXXFLAGS = -g -Wall -MMD

################################### MAIN ###################################mv 
EXE = bin/enigma
SRC_DIR = src/
OBJS = $(addprefix $(SRC_DIR), main.o stateMachine.o plugboard.o reflector.o rotor.o enigma.o helpers.o errors.o)

$(EXE): $(OBJS)
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(OBJS:.o=.d)



################################### TESTER ################################
TEST = bin/test
TEST_DIR = test/
TEST_OBJS = $(addprefix $(TEST_DIR), test.o plugboard_test.o reflector_test.o rotor_test.o)

test: $(TEST)

$(TEST): $(TEST_OBJS) $(filter-out $(SRC_DIR)main.o, $(OBJS))
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


-include $(TEST_OBJS:.o=.d)


################################### PHONY #################################
.PHONY: clean clean_dep

clean:
	rm -rf $(EXE) $(OBJS) $(OBJS:.o=.d)
	rm -rf $(TEST) $(TEST_OBJS) $(TEST_OBJS:.o=.d)
