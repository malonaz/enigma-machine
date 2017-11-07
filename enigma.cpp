#include <fstream>
#include "enigma.h"
#include "errors.h"

EnigmaMachine:: EnigmaMachine(int argc, char** argv)
  :num_rotors(argc-MIN_ENIGMA_ARGS){
  if (num_rotors  !=0)
    num_rotors--; //must include a rotor_pos_config
  // Instantiating components on the heap
  plugboard =  new Plugboard(*argv++);
  reflector = new Reflector(*argv++);
  entry_disk =  new Disk();
  rotors = new Rotor*[num_rotors];
  for (int i =0; i< num_rotors; i++)
    rotors[i] = new Rotor(*argv++);

  
  
  // Pushing components onto cascade
  sm_ptrs.push_back(plugboard);
  sm_ptrs.push_back(entry_disk);
  for (int i = num_rotors-1; i >=0; i--)
    sm_ptrs.push_back(rotors[i]);  
  sm_ptrs.push_back(reflector);
  for (int i =0; i<num_rotors;i++)
    sm_ptrs.push_back(rotors[i]);
  sm_ptrs.push_back(plugboard);
}


int EnigmaMachine:: check_args(int argc, char** argv){
  if (argc < MIN_ENIGMA_ARGS){
    print_error(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  int error_code;
  error_code = Plugboard::check_arg(*argv++);
  if (error_code){
    print_error(error_code);
    return error_code;
  }
  error_code = Reflector::check_arg(*argv++);
  if (error_code){
     print_error(error_code);
    return error_code;
  }
  for (int i = 2; i !=argc-1; i++){
    error_code = Rotor::check_arg(*argv++);
    if (error_code){
       print_error(error_code);
      return error_code;
    }
  }
  
  // check file openings?
  return NO_ERROR;
}

int EnigmaMachine::change_rotor_pos(char *config){
  std::ifstream input(config);
  if (!input.is_open()){
     print_error(ERROR_OPENING_CONFIGURATION_FILE);
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int digit, count = 0;
  while(input >> digit){
    if (digit <0 || digit>25){
      print_error(INVALID_INDEX);
      return INVALID_INDEX;
    }
    if (count < num_rotors)
      rotors[count]->set_offset(digit);
    count++;
  }
  if (!input.eof()){
    print_error(NON_NUMERIC_CHARACTER);
    return NON_NUMERIC_CHARACTER;
  }
  if (count != num_rotors){
    print_error(NO_ROTOR_STARTING_POSITION);
    return NO_ROTOR_STARTING_POSITION;
  }
  return NO_ERROR;
}

EnigmaMachine:: ~EnigmaMachine(){
  
  delete plugboard;
  delete entry_disk;
  delete reflector;
  for (int i =0; i<num_rotors;i++)
    delete rotors[i];
  delete []rotors;

}


bool EnigmaMachine::testLab(bool debug){
  if (debug)
    std::cout << "Enter a char, then press enter\n";
  char input;
  int output;
  Instruction instr(0,NO_MSG);
  while(std::cin >> input){
    if (input <'A' || input > 'Z'){
      return false;
    }
    
    instr.value = convert_char(input);
    output = step(instr,debug).value;
    if (debug)
      std::cout << input << " maps to ";
    std::cout << convert_int(output);
    //    std::cout << '\n';
  }
  return true;
}
