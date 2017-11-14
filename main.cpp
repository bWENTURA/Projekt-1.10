#include "header.hpp"
#include "complex_set_class.hpp"
#include "functions.hpp"

//using namespace std;

int main(){
  bool exit = false;
  char operation;
  while(exit != true){
    std::cout << "Wprowadź numer odpowiadający wybranej operacji lub 'q' aby wyjść.\n" << "1. AUTO TEST\n" << "2. MANUAL TEST" << std::endl;
    operation = correct_character_input('2', 'q');
    switch(operation){
      case '1':
        autotest();
        break;
      case '2':
        manutest();
        break;
      case 'q':
        exit = true;
        break;
    }
  }
  return 0;
}
