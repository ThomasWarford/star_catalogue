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
bool common_element(const std::set<std::string>& set1, const std::set<std::string>& set2);

// Checks that a key in map exists in set
// template<typename T>
// bool common_element(const std::set<std::string>& set, const std::map<std::string, T>& map)  
// {
//     auto it = std::find_first_of(map.begin(), map.end(), set.begin(), set.end(),
//                                 [](const std::pair<int, std::string>& map_pair, const int& set_value) {
//                                     return map_pair.first == set_value;
//                                 });
//     return it != map.end();
// }

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

// template<typename T>
// T prompt_variable_input(std::string variable_name, T variable)
// {   
//     error_message
//     while (std::getline(std::cin, line_string)) {
//         std::stringstream ss{line_string};
//         if ((ss>>output) && !(ss>>line_string)){
//             return output;
//         }
//         std::cout<<prompt<<std::endl;
//     }
//     return 0; // to avoid compiler warning, shouldn't be read.
// }


#endif