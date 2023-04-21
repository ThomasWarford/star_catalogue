#include<set>
#include"star.h"
#include"io_functions.h"

// star::star( std::string name, double mass, char spectral_type, double relative_magnitude, std::vector<std::string> children, std::string parent) : astronomical_object{name, mass, children, parent}, spectral_type{(char)std::toupper(spectral_type)}, relative_magnitude{relative_magnitude}
// {   
//     std::set<char> allowed_spectral_types{'O', 'B', 'A', 'F', 'G', 'K', 'M'};
    
//     if (!allowed_spectral_types.count((char)std::toupper(spectral_type))) {
//         throw std::invalid_argument("Invalid spectral type.");
//     } 
// }

star::star( std::string name): astronomical_object{name} {}

std::ostream& star::print_derived(std::ostream& os) const
{
    // os << "spectral_type:    " << spectral_type << std::endl;
    print_table_row(os, GET_VARIABLE_NAME(spectral_type), spectral_type);
    // os << "relative_magnitude:    " << relative_magnitude << std::endl;
    print_table_row(os, GET_VARIABLE_NAME(relative_magnitude), relative_magnitude);

    return os;
}

void star::set_spectral_type(char new_spectral_type)
{
    std::set<char> allowed_spectral_types{'O', 'B', 'A', 'F', 'G', 'K', 'M'};
    
    if (!allowed_spectral_types.count((char)std::toupper(new_spectral_type))) {
        throw std::invalid_argument("Invalid spectral type.");
    } 

    spectral_type = (char)std::toupper(new_spectral_type);
}

void star::set_relative_magnitude(double new_relative_magnitude)
{
    // if (new_relative_magnitude > relative_magnitude_upper){
    //     throw std::invalid_argument("Relative magnitude must be less than the upper bound.");
    // }
    // if (new_relative_magnitude < relative_magnitude_lower){
    //     throw std::invalid_argument("Relative magnitude must be greater than the lower bound.");
    // }
    check_range_error("Relative magnitude", relative_magnitude_lower, relative_magnitude_upper, new_relative_magnitude);

    relative_magnitude = new_relative_magnitude;
}

void star::populate_derived(std::ifstream& file, int& line_counter)
{
    char new_spectral_type;
    read_line_into_var(file, GET_VARIABLE_NAME(spectral_type), new_spectral_type, line_counter);
    set_spectral_type(new_spectral_type);

    double new_relative_magnitude;
    read_line_into_var(file, GET_VARIABLE_NAME(relative_magnitude), new_relative_magnitude, line_counter);
    set_relative_magnitude(new_relative_magnitude);
}
