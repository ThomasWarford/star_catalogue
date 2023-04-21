#ifndef IO_FUNCTIONS
#define IO_FUNCTIONS

#include<sstream>
#include<fstream>
#include<iostream> // only for debugging!
#include<iomanip>

#define GET_VARIABLE_NAME(variable) (#variable)

const int WIDTH{24};


// template<typename T>
// void read_line_into_var(std::string line_string, std::string variable_name, T& variable)
// {   
//     std::stringstream ss{line_string};
//     std::string first_string;
//     if ((ss>>first_string>>variable) and (!(ss>>line_string))){ // check remainder of line is empty
//         if ((first_string==variable_name+":")){ // check name is as expected
//             return;
//         }
//     }
//     std::stringstream error_message;
//     error_message << "Expected line to take form:" <<std::endl;
//     error_message << variable_name<<":   "<<"\"value\" (type:"<<typeid(T).name()<<")."<<std::endl;

//     throw std::invalid_argument(error_message.str());
// }


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
    std::cerr<<"reading "<<variable_name<<line_number<<std::endl;
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
T input(std::string prompt)
{   
    std::string line_string;
    T output;

    while (std::getline(std::cin, line_string)) {
        std::stringstream ss{line_string};
        if ((ss>>output) && !(ss>>line_string)){
            return output;
        }
        std::cout<<prompt<<std::endl;
    }
    return 0; // to avoid compiler warning, shouldn't be read.
}

#endif