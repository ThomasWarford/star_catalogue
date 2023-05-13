#ifndef FUNCTIONS
#define FUNCTIONS

#include<sstream>
#include<fstream>
#include<iostream> // only for debugging!
#include<iomanip>
#include<limits>
#include<set>
#include<map>

#define GET_VARIABLE_NAME(variable) (#variable)

const int WIDTH{24};

void wait_for_enter();
bool yes_or_no(const std::string& prompt);


template<typename T>
void print_table_row(std::ostream& os, const std::string& variable_name, const T& variable)
{   
    os << std::left << std::setw(WIDTH) << std::setfill(' ') << variable_name;
    os << std::left << std::setw(WIDTH) << std::setfill(' ') << variable;
    os<<'\n';
}

template<typename T>
void read_line_into_var(std::ifstream& file, const std::string& variable_name, T& variable, int& line_number)
{   
    line_number++;
    std::string line_string;
    std::getline(file, line_string);
    std::stringstream ss{line_string};
    std::string first_string;
    if ((ss>>first_string>>variable) and (!(ss>>line_string))){ // check remainder of line is empty
        if ((first_string==variable_name)){ // check name is as expected
            return;
        }
    }
    std::stringstream error_message;
    error_message << "Expected line to take form:" <<std::endl;
    print_table_row(error_message, variable_name, "____");
    error_message<<"where ____ is type "<<typeid(T).name()<<std::endl;
    throw std::invalid_argument(error_message.str());
}

template<typename T>
T input(std::string prompt, bool indent=false)
{   
    prompt = std::string(int(indent), '\t') + prompt;
    std::string line_string;
    T output;
    std::cout<<prompt;
    
    while (std::getline(std::cin, line_string)) {
        if (line_string.empty()) { // if the user inputs nothing
            return T{}; // return an empty T object
        }
        std::stringstream ss{line_string};
        if ((ss>>output) && !(ss>>line_string)){
            return output;
        }
        std::cout<<prompt;
    }
    return output; // to avoid compiler warning, shouldn't be called.
}


#endif