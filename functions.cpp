#include "header.hpp"
#include "complex_set_class.hpp"
#include "functions.hpp"

//Funkcja sprawdzająca czy został poprawnie wprowadzony pojedynczy znak
bool character_input(char *operation){
  std::string temp;
  getline(std::cin, temp);
  switch(temp.size()){
    case 1:
      (*operation) = temp[0];
      return true;
    case 0:
      std::cout << "Nie wprowadzono żadnego znaku." << std::endl;
      return false;
    default:
      std::cout << "Wprowadziłeś więcej niż jeden znak." << std::endl;
      return false;
  }
}

//Funkcja sprawdzająca czy wprowadzony poprawnie pojedynczy znak mieści się w wymaganym zakresie
//Funkcja używana wyłącznie do wyboru liczb z zakresu [1, maximum], ewentualnie pojedynczego znaku exception
//Funkcja mająca głównie zastosowanie w wyborze opcji z menu
char correct_character_input(char maximum, char exception){
  char sign;
  bool flag = character_input(&sign);
  while(!(flag && (sign == exception || (sign <= maximum && sign >= '1')))){
    if(flag) std::cout << "Wprowadziłeś znak z nieodpowiedniego zakresu znak." << std:: endl;
    flag = character_input(&sign);
  }
  return sign;
}

//Funkcja sprawdzająca czy ciąg znaków wprowadzony przez użytkownika może zostać przekształcony na typ double
bool double_input(double *number){
  std::string text;
  bool point = false;
  getline(std::cin, text);
  if(text.size()){
    for(unsigned int i = 0; i != text.size(); i++){
      if(text[i] == '.'){
        if(i == 0 || point == true || i == text.size() - 1){
          std::cout << "Wprowadziłeś niepoprawną liczbę." << std::endl;
          return false;
        }
        point = true;
      }
      else{
        if(!(isdigit(text[i]) || (i == 0 && text[i] == '-' ))){
          std::cout << "Wprowadziłeś niepoprawną liczbę." << std::endl;
          return false;
        }
      }
    }
    (*number) = stod(text);
  }
  else{
    std::cout << "Nie wprowadziłeś liczby." << std::endl;
    return false;
  }
  return true;
}

//Funkcja zwracająca poprawnie wprowadzoną liczbę typu double
double correct_double_input(){
  bool flag;
  double number;
  do{
    flag = double_input(&number);
  } while(!flag);
  return number;
}

//Funkcja sprawdzająca czy użytkownik wprowadził poprawną nazwę dla obiektu
bool correct_name(std::string *name, std::vector<complex_numbers_set*> set){
  getline(std::cin, *name);
  if((*name).size()){
    for(complex_numbers_set *iterator: set){
      std::string temp_name = iterator->get_name();
      if(temp_name == (*name)){
        std::cout << "Występuje już zbiór o takiej nazwie, spróbuj użyć innej." << std::endl;
        return false;
      }
      if(temp_name == "-----DEAFULT-----"){
        std::cout << "Jakimś cudem wprowadziłeś zakazaną nazwę, spróbuj ponownie." << std::endl;
        return false;
      }
    }
  }
  else{
    std::cout << "Nie wprowadziłeś żadnego znaku mogącego być nazwą." << std::endl;
    return false;
  }
  return true;
}

//Funkcja zwracająca poprawną nazwę wprowadzoną przez użytkownika
std::string correct_name_input(std::vector<complex_numbers_set*> set){
  bool flag;
  std::string name;
  do{
    flag = correct_name(&name, set);
  } while(!flag);
  return name;
}

char menu(){
  std::cout << "Wybierz operację lub wciśnij 'q' aby wyjść.\n" << "1. Stwórz zbiór.\n" << "2. Pokaż zawartość zbiorów.\n" << "3. Dodaj liczby do zbioru.\n" << "4. Wykonaj operacje na zbiorach.\n" << "5. Zwróć liczbę o największym module z wybranego zbioru."  << std::endl;
  char operation = correct_character_input('5', 'q');
  return operation;
}

char operation_menu(){
  std:: cout << "Wybierz numer operacji lub 'q' aby wyjść.\n" << "1. A += B\n" << "2. C = A + B\n" << "3. A *= B\n" << "4. C = A * B" << std::endl;
  char operation = correct_character_input('4', 'q');
  return operation;
}

//Funkcja drukująca zbiory razem z liczbami porządkowymi i zwracająca indeks ostatniego zbioru
int print_set_and_get_size(std::vector<complex_numbers_set*> set){
  int index = 0;
  for(complex_numbers_set *iterator: set){
    iterator->print(++index);
  }
  return index;
}

//Funkcja sprawdzająca poprawność działań na obiektach
void autotest(){
  std::vector<complex_numbers_set*> set;
  std::string input;
  std::cout << LINE << "\nAUTO TEST START\n" << LINE << "\nPrzejścia do następnego kroku proszę potwierdzać wciskając klawisz enter.\n" << LINE;
  getline(std::cin, input);
  std::cout << "Tworzę zbiory o nazwie \"Zbiór pierwszy\" i \"Zbiór drugi\".";
  getline(std::cin, input);
  complex_numbers_set *first = new complex_numbers_set("Zbiór pierwszy");
  complex_numbers_set *second = new complex_numbers_set("Zbiór drugi");
  std::cout << "Dodaję liczby 1 + 2j, 1.25 - 13j, 2.64 - 0.15j, 15 + 20j i 13.2006 + 1.00009j do \"Zbiór pierwszy\"";
  getline(std::cin, input);
  first->add_number(1, 2); first->add_number(1.25, -13); first->add_number(2.64, -0.15); first->add_number(15, 20); first->add_number(13.2006, 1.00009);
  std::cout << "Dodaję liczby 2.69 + 3.13j, 15 - 13.17j, 2.64 - 0.15j, 13.2006 + 1.00009j i 1 + 2j do \"Zbiór drugi\"";
  getline(std::cin, input);
  second->add_number(2.69, 3.13); second->add_number(15, -13.17); second->add_number(2.64, -0.15); second->add_number(13.2006, 1.00009); second->add_number(1, 2);
  set.push_back(first);
  set.push_back(second);
  std::cout << "Oto zbiory i ich zawartość:\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  std::cout << "Tworzę pusty zbiór o nazwie \"Zbiór trzeci\", do którego następnie dodam zbiór pierwszy.(Zbiór trzeci += Zbiór pierwszy)";
  getline(std::cin, input);
  complex_numbers_set *third = new complex_numbers_set("Zbiór trzeci");
  set.push_back(third);
  std::cout << "Oto zbiory i ich zawartość:\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  *third += *first;
  std::cout << "Oto zbiory po dodaniu.\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  std::cout << "Teraz stworzę nowy zbiór o nazwie \"Zbiór czwarty\", zawierający sumę zbioru trzeciego i drugiego.(Zbiór czwarty = Zbiór trzeci + Zbiór drugi)";
  getline(std::cin, input);
  complex_numbers_set * fourth = new complex_numbers_set("Zbiór czwarty");
  *fourth += *third + *second;
  set.push_back(fourth);
  std::cout << "Oto zbiory po stworzeniu nowego zbioru:\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  std::cout << "Tworzę pusty zbiór o nazwie \"Zbiór piąty\", a nastepnie wykonam na nim operację Zbiór piąty *= Zbiór pierwszy.";
  getline(std::cin, input);
  complex_numbers_set *fifth = new complex_numbers_set("Zbiór piąty");
  set.push_back(fifth);
  std::cout << "Oto zbiory i ich zawartość:\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  *fifth *= *first;
  std::cout << "Oto zbiory po operacji.\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  std::cout << "Teraz dodam do zbioru piątego zbiór pierwszy, a następnie wykonam operację Zbiór piąty *= Zbiór drugi.";
  getline(std::cin, input);
  *fifth += *first;
  std::cout << "Oto zbiory po dodaniu:\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  *fifth *= *second;
  std::cout << "Oto zbiory po operacji.\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  std::cout << "Teraz stworzę \"Zbiór szósty\" będący wynikiem operacji Zbiór szósty = Zbiór trzeci * Zbiór drugi.";
  getline(std::cin, input);
  complex_numbers_set *sixth = new complex_numbers_set("Zbiór szósty");
  *sixth += *third * *second;
  set.push_back(sixth);
  std::cout << "Oto zbiory i ich zawartość:\n";
  print_set_and_get_size(set);
  getline(std::cin, input);
  for(complex_numbers_set *iterator: set){
    delete iterator;
  }
  std::cout << LINE << "\nEND OF AUTOTEST\n" << LINE << std::endl;
}

//Funkcja odpowiadająca za przeprowadzenie manualnego testu
void manutest(){
  bool exit = false;
  std::string temp_name;
  std::vector<complex_numbers_set*> set; //Kontener wskaźników do obiektów reprezentujących zbiory liczb zespolonych
  complex_numbers_set * new_set; //Pomocniczy wskaźnik przydatny przy tworzeniu nowych obiektów
  while(!exit){
    switch(menu()){
      case '1':
        std::cout << "Wprowadź nazwę zbioru." << std::endl;
        temp_name = correct_name_input(set);
        new_set = new complex_numbers_set(temp_name);
        set.push_back(new_set);
        break;
      case '2':
        if(set.size()){
          for(complex_numbers_set *iterator: set){
            iterator->print();
          }
        }
        else std::cout << "Najpierw stwórz jakiś zbiór." << std::endl;
        break;
      case '3':
        if(set.size()){
          std::cout << "Wybierz numer zbioru do którego chcesz dodać liczbę lub 'q' by wrócić.\n";
          while(!exit){
            int index = print_set_and_get_size(set);
            while(!exit){
              char sign = correct_character_input(char(index + 48), 'q'); //Wczytanie numeru zbioru jako znaku z odpowiedniego zakresu
              if(sign == 'q') exit = true;
              while(!exit){
                index = int(sign) - 49; //Ustalenie liczby porządkowej zbioru, na którym chce operować użytkownik
                std::cout << "Wciśnij '1' aby wprowadzić liczbę do zbioru " << "\"" << set[index]->get_name() << "\"" << " lub 'q' aby wyjść." << std::endl;
                char operation = correct_character_input('1', 'q');
                switch(operation){
                  case '1':{
                    std::cout << "Wprowadź część reczywistą liczby." << std::endl;
                    double real_part = correct_double_input();
                    std::cout << "Wprowadź część urojoną liczby. (bez 'j')" << std::endl;
                    double imaginary_part = correct_double_input();
                    set[index]->add_number(real_part, imaginary_part); //Dodanie do wybranego zbioru liczby wprowadzonej przez użytkownika
                    break;
                  }
                  case 'q':
                    exit = true;
                    break;
                }
              }
            }
          }
          exit = false;
        }
        else std::cout << "Najpierw stwórz jakiś zbiór." << std::endl;
        break;
      case '4':
        if(set.size()>1){
          while(!exit){
            int index_a, index_b;
            char sign;
            switch(operation_menu()){
              case '1':
                index_a = index_b = print_set_and_get_size(set);
                std::cout << "Wybierz dwa numery porządkowe, najpierw zbioru A, potem zbioru B." << std::endl;
                sign = correct_character_input(char(index_a + 48));
                index_a = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie pierwszy numer porządkowy, teraz wprowadź drugi." << std::endl;
                sign = correct_character_input(char(index_b + 48));
                index_b = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie drugi numer porządkowy." << std::endl;
                *(set[index_a]) += *(set[index_b]);
                break;
              case '2':
                index_a = index_b = print_set_and_get_size(set);
                std::cout << "Wybierz dwa numery porządkowe, najpierw zbioru A, potem zbioru B." << std::endl;
                sign = correct_character_input(char(index_a + 48));
                index_a = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie pierwszy numer porządkowy, teraz wprowadź drugi." << std::endl;
                sign = correct_character_input(char(index_b + 48));
                index_b = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie drugi numer porządkowy." << std::endl;
                std::cout << "Wprowadź nazwę zbioru C." << std::endl;
                temp_name = correct_name_input(set);
                new_set = new complex_numbers_set(temp_name);
                *new_set += (*(set[index_a]) + *(set[index_b]));
                set.push_back(new_set);
                break;
              case '3':
                index_a = index_b = print_set_and_get_size(set);
                std::cout << "Wybierz dwa numery porządkowe, najpierw zbioru A, potem zbioru B." << std::endl;
                sign = correct_character_input(char(index_a + 48));
                index_a = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie pierwszy numer porządkowy, teraz wprowadź drugi." << std::endl;
                sign = correct_character_input(char(index_b + 48));
                index_b = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie drugi numer porządkowy." << std::endl;
                *(set[index_a]) *= *(set[index_b]);
                break;
              case '4':
                index_a = index_b = print_set_and_get_size(set);
                std::cout << "Wybierz dwa numery porządkowe, najpierw zbioru A, potem zbioru B." << std::endl;
                sign = correct_character_input(char(index_a + 48));
                index_a = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie pierwszy numer porządkowy, teraz wprowadź drugi." << std::endl;
                sign = correct_character_input(char(index_b + 48));
                index_b = int(sign) - 49;
                std::cout << "Wprowadziłeś poprawnie drugi numer porządkowy." << std::endl;
                std::cout << "Wprowadź nazwę zbioru C." << std::endl;
                temp_name = correct_name_input(set);
                new_set = new complex_numbers_set(temp_name);
                *new_set += (*(set[index_a]) * *(set[index_b]));
                set.push_back(new_set);
                break;
              case 'q':
                exit = true;
                break;
              }
          }
          exit = false;
        }
        else std::cout << "Jest za mało zbiorów do wykonania operacji." << std::endl;
        break;
      case '5':
        if(set.size()){
          int index = print_set_and_get_size(set);
          std::cout << "Wprowadź numer zbioru." << std::endl;
          char sign = correct_character_input(char(index + 48));
          index = int(sign) - 49;
          set[index]->biggest_number();
        }
        else std::cout << "Najpierw stwórz jakiś zbiór." << std::endl;
        break;
      case 'q':
        exit = true;
        break;
      default:
        std::cout << "Wprowadzono nieprawidłowy znak" << std::endl;
        break;
    }
  }
  for(complex_numbers_set *iterator: set){ //Wyczyszczenie kontenera obiektów
    delete iterator;
  }
}
