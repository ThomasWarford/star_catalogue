#include<set>
#include"star.h"
#include"functions.h"

// star::star( std::string name, double mass, char spectral_type, double relative_magnitude, std::vector<std::string> children, std::string parent) : astronomical_object{name, mass, children, parent}, spectral_type{(char)std::toupper(spectral_type)}, relative_magnitude{relative_magnitude}
// {   
//     std::set<char> allowed_spectral_types{'O', 'B', 'A', 'F', 'G', 'K', 'M'};
    
//     if (!allowed_spectral_types.count((char)std::toupper(spectral_type))) {
//         throw std::invalid_argument("Invalid spectral type.");
//     } 
// }


std::ostream& star::print_derived(std::ostream& os) const
{
    print_table_row(os, GET_VARIABLE_NAME(relative_magnitude), relative_magnitude);
    print_table_row(os, GET_VARIABLE_NAME(spectral_type), spectral_type);
    return os;
}

void star::set_spectral_type(char new_spectral_type)
{
    
    
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
    // Setter pointers are statically casted to be astronomical object pointers.
    // read_line_and_set<char>(
    //     file, 
    //     "spectral_type", 
    //     static_cast<void (astronomical_object::*)(char)> (&star::set_spectral_type), 
    //     line_counter);

    double new_relative_magnitude;
    read_line_into_var(file, GET_VARIABLE_NAME(relative_magnitude), new_relative_magnitude, line_counter);
    set_relative_magnitude(new_relative_magnitude);

    char new_spectral_type;
    read_line_into_var(file, GET_VARIABLE_NAME(spectral_type), new_spectral_type, line_counter);
    set_spectral_type(new_spectral_type);

}

void star::populate_derived(bool indent)
{
    double new_relative_magnitude;
    prompt_and_read_into_var("relative_magnitude", new_relative_magnitude, relative_magnitude_lower, relative_magnitude_upper, indent);
    set_relative_magnitude(new_relative_magnitude);

    char new_spectral_type;
    prompt_and_read_into_var("spectral_type", new_spectral_type, allowed_spectral_types, indent);
    set_spectral_type(new_spectral_type);
}