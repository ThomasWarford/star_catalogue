#include<iostream>
#include<sstream>
#include"astronomical_object.h"
#include"io_functions.h"

std::ostream& astronomical_object::print_base(std::ostream& os) const
{
    os << "name:    " << name << '\n';
    os << "mass:    " << mass << '\n';
    return os;
}


std::ostream& operator<<(std::ostream& os, const astronomical_object& output_astronomical_object)
{
    print_table_row(os, "name", output_astronomical_object.name);
    print_table_row(os, "type", output_astronomical_object.type());
    print_table_row(os, "mass", output_astronomical_object.mass);



    // os << "name:    " << output_astronomical_object.name << '\n';
    // os << "type:    "<< output_astronomical_object.type() << '\n';
    // os << "mass:    " << output_astronomical_object.mass << '\n';
    output_astronomical_object.print_derived(os);
    return os;
}

void astronomical_object::set_mass(double new_mass)
{   
    check_range_error("Mass", mass_bound_lower(), mass_bound_upper(), new_mass);

    mass = new_mass;
}

void astronomical_object::check_range_error(std::string quantity_name, double lower, double upper, double entered_value) const
{
    if ((entered_value > upper) | entered_value < lower){
        std::stringstream error_message;
        error_message<<quantity_name<<" should be between "<<lower<<" and "<<upper<<". Value entered: " << entered_value;
        throw std::range_error(error_message.str());
    }
}


void astronomical_object::set_children(std::vector<std::string> new_children)
{
    children = new_children;
}
void astronomical_object::set_parent(std::string new_parent)
{
    parent = new_parent;
}

void astronomical_object::populate(std::ifstream& file, int& line_counter)
{   
    populate_base(file, line_counter);
    populate_derived(file, line_counter);
}
void astronomical_object::populate_base(std::ifstream& file, int& line_counter)
{   
    double new_mass;
    read_line_into_var(file, GET_VARIABLE_NAME(mass), new_mass, line_counter);
    set_mass(new_mass);
}

