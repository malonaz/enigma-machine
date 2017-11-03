#include "../include/enigma.h"

EnigmaMachine:: EnigmaMachine(int argc, char** argv)
  :num_rotors(argc-MIN_ARGS){
  
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
  if (argc -1 < 3)
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;

  int error_code;
  error_code = Plugboard::check_arg(*argv++);
  if (error_code)
    return error_code;
  
    
  // check file openings?
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


