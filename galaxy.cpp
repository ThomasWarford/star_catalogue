#include<set>
#include"galaxy.h"
#include"io_functions.h"

void galaxy::set_hubble_type(std::string new_hubble_type)
{

    if (!allowed_hubble_galaxy_types.count(new_hubble_type)) {  // Check inputted string corresponds with hubble galaxy type
        throw std::invalid_argument("Hubble type not valid.");
    }
    hubble_type = new_hubble_type;

}


std::ostream& galaxy::print_derived(std::ostream& os) const
{
    print_table_row(os, GET_VARIABLE_NAME(hubble_type), hubble_type);
    return os;
}

void galaxy::populate_derived(std::ifstream& file, int& line_counter)
{
    std::string new_hubble_type;
    read_line_into_var(file, GET_VARIABLE_NAME(hubble_type), new_hubble_type, line_counter);
    set_hubble_type(new_hubble_type);
}

void galaxy::populate_derived()
{
    std::string new_hubble_type;
    prompt_and_read_into_var("hubble_type", new_hubble_type, allowed_hubble_galaxy_types);
    set_hubble_type(new_hubble_type);
}