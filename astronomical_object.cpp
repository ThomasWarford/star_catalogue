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

void astronomical_object::populate()
{
    populate_base();
    populate_derived();
}

void astronomical_object::populate_base()
{
    double new_mass;
    prompt_and_read_into_var("mass", new_mass, mass_bound_lower(), mass_bound_upper());
    set_mass(new_mass);
}

void astronomical_object::prompt_and_read_into_var(const std::string &quantity_name, double& variable, const double lower_bound, const double upper_bound)
{   
    double output;
    bool looping{true};
    while (looping) {
        looping=false;
        output = input<double>(quantity_name+": ");
        
        try{
            check_range_error(quantity_name, lower_bound, upper_bound, output);
            variable=output;
        }
        catch(std::range_error error) {
            std::cout<<error.what()<<std::endl;
            looping=true;
        }
    }
}

void astronomical_object::prompt_and_read_into_var(const std::string &quantity_name, std::string& variable, const std::set<std::string>& allowed_values)
{
    std::string output;
    bool looping{true};
    while (looping) {
        output = input<std::string>(quantity_name+": ");

        if (allowed_values.count(output)){
            looping=false;
            variable=output;
        }
        else {
            looping=true;

            std::cout<<output<<" is not an allowed value for "<<quantity_name<<'.'<<std::endl;
            std::cout<<"The allowed values are: ";
            for (auto element: allowed_values){
                std::cout<<element<<", ";
            }
            std::cout<<std::endl;
        }

    }
}

void astronomical_object::prompt_and_read_into_var(const std::string &quantity_name, char& variable, const std::set<char>& allowed_values)
{
    char output;
    bool looping{true};
    while (looping) {
        output = input<char>(quantity_name+": ");

        if (allowed_values.count(std::toupper(output))){
            looping=false;
            variable=output;
        }
        else {
            looping=true;

            std::cout<<output<<" is not an allowed value for "<<quantity_name<<'.'<<std::endl;
            std::cout<<"The allowed values are: ";
            for (auto element: allowed_values){
                std::cout<<element<<", ";
            }
            std::cout<<std::endl;
        }

    }
}



