#include<set>
#include"star.h"
#include"functions.h"

void star::set_spectral_type(char new_spectral_type)
{
    
    
    if (!allowed_spectral_types.count((char)std::toupper(new_spectral_type))) {
        throw std::invalid_argument("Invalid spectral type.");
    } 

    spectral_type = (char)std::toupper(new_spectral_type);
}

void star::set_relative_magnitude(double new_relative_magnitude)
{
    check_range_error("Relative magnitude", relative_magnitude_bound_lower, relative_magnitude_bound_upper, new_relative_magnitude);

    relative_magnitude = new_relative_magnitude;
}

std::ostream& star::print_derived(std::ostream& os) const
{
    print_table_row(os, GET_VARIABLE_NAME(relative_magnitude), relative_magnitude);
    print_table_row(os, GET_VARIABLE_NAME(spectral_type), spectral_type);
    return os;
}


void star::populate_derived(std::ifstream& file, int& line_counter)
{

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
    prompt_and_read_into_var("relative_magnitude", new_relative_magnitude, relative_magnitude_bound_lower, relative_magnitude_bound_upper, indent);
    set_relative_magnitude(new_relative_magnitude);

    char new_spectral_type;
    prompt_and_read_into_var("spectral_type", new_spectral_type, allowed_spectral_types, indent);
    set_spectral_type(new_spectral_type);
}