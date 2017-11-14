#ifndef COMPLEX_SET_CLASS_HPP
#define COMPLEX_SET_CLASS_HPP

//Definicja klasy reprezentującej zbiór liczb zespolonych
//Obiekt klasy zawiera kontener ze wskaźnikami na obiekty typu complex, czyli obiekty reprezentujące liczby zespolone
class complex_numbers_set{
  std::string name;
  std::vector<std::complex<double>*> collection;
  public:
  complex_numbers_set(std::string name = "-----DEAFULT-----");
  ~complex_numbers_set();
  void add_number(double real, double imaginary);
  void print(int index = 0);
  std::complex<double> biggest_number();
  std::string get_name();
  complex_numbers_set& operator+=(complex_numbers_set& complex_right);
  complex_numbers_set& operator*=(const complex_numbers_set& complex_right);
  complex_numbers_set& operator+(const complex_numbers_set& complex_right);
  complex_numbers_set& operator*(const complex_numbers_set& complex_right);
};
#endif
