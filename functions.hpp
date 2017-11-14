#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

bool character_input(char *operation);

char correct_character_input(char maximum, char exception = '1');

bool double_input(double *number);

double correct_double_input();

bool correct_name(std::string *name, std::vector<complex_numbers_set*> set);

std::string correct_name_input(std::vector<complex_numbers_set*> set);

char menu();

char operation_menu();

int print_set_and_get_size(std::vector<complex_numbers_set*> set);

void autotest();

void manutest();

#endif
