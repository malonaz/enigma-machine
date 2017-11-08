// -*- C++ -*-
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
  entry_disk =  new EntryDisk();
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


ErrorReport EnigmaMachine:: check_args(int argc, char** argv){
  
  if (argc < MIN_ENIGMA_ARGS){
    return ErrorReport(INSUFFICIENT_NUMBER_OF_PARAMETERS);
  }
  
  
  
  ErrorReport plugboard_report = Plugboard::check_arg(*argv++);

  if (plugboard_report.get_code())
    return plugboard_report;
  
  
  ErrorReport reflector_report = Reflector::check_arg(*argv++);
  if (reflector_report.get_code())
    return reflector_report;


  ErrorReport* error_report_ptr;
  for (int i = MIN_ENIGMA_ARGS; i < argc-1; i++){
    error_report_ptr =new ErrorReport(Rotor::check_arg(*argv++));
    if (error_report_ptr->get_code()){
      ErrorReport error_report = *error_report_ptr;
      delete error_report_ptr;
      return error_report;
    }
    delete error_report_ptr;
  }
  
  
  // check file openings?
  return ErrorReport(NO_ERROR);
}


ErrorReport EnigmaMachine::change_rotor_pos(char *config){
  std::ifstream input(config);
  if (!input.is_open())
    return ErrorReport(ERROR_OPENING_CONFIGURATION_FILE,config);
  
  int digit, count = 0;
  while(input >> digit){
    if (digit <0 || digit>25)
      return ErrorReport(INVALID_INDEX,config);
    
    if (count < num_rotors)
      rotors[count]->set_offset(digit);
    count++;
  }
  if (!input.eof())
    return ErrorReport(NON_NUMERIC_CHARACTER, config);
 
  if (count != num_rotors) 
    return ErrorReport(NO_ROTOR_STARTING_POSITION,config);
  
  return ErrorReport(NO_ERROR, config);
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
  }
  return true;
}

bool EnigmaMachine::transduce(const char *filename){
  std::ifstream inputs(filename);
  char input;
  int output;
  Instruction instr(0,NO_MSG);
  while(inputs >> input){
   
    if (input <'A' || input > 'Z'){
      return false;
    }
    
    instr.value = convert_char(input);
    output = step(instr).value;
    
    std::cout << convert_int(output);
  }
  return true;
}


