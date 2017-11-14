#include "header.hpp"
#include "complex_set_class.hpp"

//Konstruktor klasy
complex_numbers_set::complex_numbers_set(std::string new_name) : name(new_name) {
  std::cout << "----------ZBIÓR \"" << name <<  "\" ZOSTAŁ UTWORZONY----------" << std::endl;
}

//Destruktor klasy
complex_numbers_set::~complex_numbers_set(){
  for(std::complex<double> * iterator: collection){
    delete iterator;
  }
  collection.clear();
  std::cout << "----------ZBIÓR \"" << name << "\" ZOSTAŁ USUNIĘTY----------" << std::endl;
}

//Funkcja dodająca liczbę zespoloną do klasy reprezentującej zbiór liczb zespolonych
//Funkcja pobiera argument liczby rzeczywistej i zespolonej, następnie tworzy obiekt typu complex(liczba zespolona) ze standardowej biblioteki
//Wskaźnik do obiektu zapisuje w kontenerze liczb zespolonych, który jest reprezentacją zbioru w klasie zbioru liczb zespolonych
void complex_numbers_set::add_number(double real, double imaginary){
  bool there_is = false;
  std::complex<double> * number;
  number = new std::complex<double>(real, imaginary);
  for(std::complex<double> * iterator: collection){
    if(*iterator == *number) there_is = true;
  }
  if(!there_is) collection.push_back(number);
  else{
      delete number;
      std::cout << "Wprowadzono liczbę, która już występuje w zbiorze." << std::endl;
  }
}

//Funkcja wyświetlająca dane znajdujące się w obiekcie typu complex_set_number
//Może zostać wywołana z argumentem okreslającym numer porządkowy zbioru, przydatne w wszelkiego typu menu wyboru
void complex_numbers_set::print(int index){
  std::complex<double> number;
  std::cout << LINE << "\n";
  if(index) std::cout << index << ". ";
  else std::cout << "Zbiór o nazwie: ";
  std::cout << '\"' << name << "\".\n";
  if(collection.size()){
    std:: cout << "{ ";
    for(std::complex<double> *iterator: collection){
      number = *iterator;
      std::cout << "(" << real(number) << ")" << " + " << "(" << imag(number) << "j)" << ", moduł: " << abs(number) << (iterator == collection.back() ? " }\n" : " ;; ");
    }
  }
  else std::cout << "Zbiór jest pusty." << std::endl;
  std::cout << LINE << std::endl;
}

//Funkcja zwracająca ze zbioru liczbę o najwiekszym module
//Wykorzystanie funkcji abs z biblioteki complex, określającą moduł liczby reprezentowanej przez obiekt liczby zespolonej
std::complex<double> complex_numbers_set::biggest_number(){
  if(collection.size()){
    double max = 0;
    std::complex<double> number;
    for(std::complex<double> * iterator: collection){
      if(abs(*iterator)>max){
        number = *iterator;
        max = abs(number);
      }
    }
    std::cout << LINE << "\nLiczba zespolona o największym module w zbiorze \"" << name << "\" to: (" << real(number) << ")" << " + " << "(" << imag(number) << "j)" << ", jej moduł wynosi: " << abs(number) << "\n" << LINE << std::endl;
    return number;
  }
  else{
    std::cout << "Wybrany zbior jest pusty." << std::endl;
    return 0;
  }
}

//Funkcja służąca do pozyskania nazwy obiektu klasy
std::string complex_numbers_set::get_name(){
  return name;
}

//Przeciążenie operatora +=
//Funkcja sprawdza jakie liczby występują w drugim obiekcie reprezentującym zbiór
//W przypadku gdy liczba występuje w obydwu zbiorach nic się nie dzieje
//W przeciwnym wypadku zostaje utworzony wskaźnik do liczby będącej kopią liczby niepowtarzającej się
//Wskaźnik zostaje dodany do kontenera liczb zespolonych
//Jeżeli obiekt ma domyślną nazwę to znaczy że jest kopią wynikającą z operacji przeciążenia operatorów + lub *
//To znaczy, że po wykorzystaniu musi być zniszczony
//Dzieje się to tutaj, ponieważ używanie operatorów * i + ma sens tylko gdy w działaniu bierze też udział += jako operator główny
//(w przypadku zbioru pustego += działa jak ==, stąd brak przeciążenia operatora ==, które nie jest potrzebne w programie)
complex_numbers_set& complex_numbers_set::operator+=(complex_numbers_set& complex_right){
  for(std::complex<double> *iterator: complex_right.collection){
    bool there_is = false;
    for(std::complex<double> *equal_iterator: collection){
      if((*equal_iterator) == (*iterator)){
        there_is = true;
        break;
      }
    }
    if(!there_is){
      double real_part = real(*iterator);
      double imaginary_part = imag(*iterator);
      add_number(real_part, imaginary_part);
    }
  }
  if(complex_right.name == "-----DEAFULT-----") delete &complex_right;
  return (*this);
}

//Przeciążenie operatora *=
//Tworzony jest nowy, tymczasowy kontener, do którego wrzucane są wskaźniki do obiektów będących kopiami liczb powtarzających się
//Następnie niszczone są wskaźniki do liczb w kontenerze obiektu głównego i dodawane są wskaźniki z tymczasowego kontenera
complex_numbers_set& complex_numbers_set::operator*=(const complex_numbers_set& complex_right){
  std::vector<std::complex<double>*> temp_collection;
  std::complex<double> *number;
  for(std::complex<double> *iterator: complex_right.collection){
    bool there_is = false;
    for(std::complex<double> *equal_iterator: collection){
      if((*equal_iterator) == (*iterator)){
        there_is = true;
        break;
      }
    }
    if(there_is){
      double real_part = real(*iterator);
      double imaginary_part = imag(*iterator);
      number = new std::complex<double>(real_part, imaginary_part);
      temp_collection.push_back(number);
    }
  }
  for(std::complex<double> *iterator: collection){
    delete iterator;
  }
  collection.clear();
  for(std::complex<double> *iterator: temp_collection){
    collection.push_back(iterator);
  }
  return (*this);
}

//Przeciążenie operator +
//Tworzony jest tymczasowy obiekt klasy complex_numbers_set
//Dodaje się do niego wskaźniki do kopii niepowtarzających się liczb z pierwszego i drugiego zbioru
//Tymczasowy obiekt zostaje zwrócony jako wynik działania operatora +
complex_numbers_set& complex_numbers_set::operator+(const complex_numbers_set& complex_right){
  complex_numbers_set * temporary;
  temporary = new complex_numbers_set;
  double real_part, imaginary_part;
  for(std::complex<double> *iterator: collection){
    real_part = real(*iterator);
    imaginary_part = imag(*iterator);
    temporary->add_number(real_part, imaginary_part);
  }
  for(std::complex<double> *iterator: complex_right.collection){
    bool there_is = false;
    for(std::complex<double> *equal_iterator: collection){
      if((*equal_iterator) == (*iterator)){
        there_is = true;
        break;
      }
    }
    if(!there_is){
      real_part = real(*iterator);
      imaginary_part = imag(*iterator);
      temporary->add_number(real_part, imaginary_part);
    }
  }
  return (*temporary);
}

//Przeciążenie operatora *
//Działa analogicznie do przeciążenia operatora +, z ta różnicą, że przekazuje obiekt zawierający kontener ze wskaźnikami na POWTARZAJĄCE się obiekty
complex_numbers_set& complex_numbers_set::operator*(const complex_numbers_set& complex_right){
  complex_numbers_set * temporary;
  temporary = new complex_numbers_set;
  for(std::complex<double> *iterator: complex_right.collection){
    bool there_is = false;
    for(std::complex<double> *equal_iterator: collection){
      if((*equal_iterator) == (*iterator)){
        there_is = true;
        break;
      }
    }
    if(there_is){
      double real_part = real(*iterator);
      double imaginary_part = imag(*iterator);
      temporary->add_number(real_part, imaginary_part);
    }
  }
  return (*temporary);
}
