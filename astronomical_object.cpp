#include<iostream>
#include<sstream>
#include"astronomical_object.h"
#include"functions.h"
#include <regex>


void astronomical_object::set_right_ascension(const std::string& string) {
    std::regex right_ascension_regex("^([-+]?\\d+)h(\\d+)m([\\d.]+)s$");
    std::smatch match;
    
    if (std::regex_match(string, match, right_ascension_regex)) {
        int hours = std::stoi(match[1]);
        int minutes = std::stoi(match[2]);
        double seconds = std::stod(match[3]);
        set_right_ascension(hours, minutes, seconds);
        return;
    }
    throw std::invalid_argument("Right ascension value not formatted correctly.");
    return;

}

void astronomical_object::set_declination(const std::string& string) {
    std::regex declination_regex("^([-+]?\\d+)°(\\d+)′([\\d.]+)″$");
    std::smatch match;
    
    if (std::regex_match(string, match, declination_regex)) {
        int degrees = std::stoi(match[1]);
        int minutes = std::stoi(match[2]);
        double seconds = std::stod(match[3]);
        set_declination(degrees, minutes, seconds);
        return;
    }
    throw std::invalid_argument("Declination value not formatted correctly.");
    return;

}

void astronomical_object::set_distance(double new_distance)
{
    check_range_error("Distance", distance_bound_lower(), distance_bound_upper(), new_distance);
    distance=new_distance;
}

std::ostream& operator<<(std::ostream& os, const astronomical_object& output_astronomical_object)
{
    print_table_row(os, "name", output_astronomical_object.name);
    print_table_row(os, "type", output_astronomical_object.type());
    print_table_row(os, "right_ascension", output_astronomical_object.get_right_ascension());
    print_table_row(os, "declination", output_astronomical_object.get_declination());
    print_table_row(os, "distance", output_astronomical_object.distance);
    print_table_row(os, "mass", output_astronomical_object.mass);
    
    output_astronomical_object.print_derived(os);

    os << std::left << std::setw(WIDTH) << std::setfill(' ') << "children";
    for (auto child : output_astronomical_object.children) {
        os << child << "  ";
    }
    os<<'\n';
    return os;
}

void astronomical_object::set_right_ascension(int hours, int minutes, double seconds)
{   
    check_range_error("Seconds", 0, 60, seconds);
    check_range_error("Minutes", 0, 59.1, minutes);
    check_range_error("Hours", 0, 23.1, hours);
    double new_right_ascension{ hours + minutes/60 + seconds/3600 };
    check_range_error("Right ascension", 0, 24, new_right_ascension);
    // right_ascension = new_right_ascension;
    right_ascension.hours = hours;
    right_ascension.minutes = minutes;
    right_ascension.seconds = seconds;

}

std::string astronomical_object::get_right_ascension() const
{

    // int hours = static_cast<int>(right_ascension);
    // double remaining = (right_ascension - hours) * 60.0;
    // int minutes = static_cast<int>(remaining);
    // remaining = (remaining * 60.0) - minutes;
    // double seconds = remaining * 60.0;

    std::stringstream out;
    out<<right_ascension.hours<<'h'<<right_ascension.minutes<<'m'<<right_ascension.seconds<<'s';
    return out.str();
}

void astronomical_object::set_declination(int degrees, int minutes, double seconds)
{   
    check_range_error("Seconds", 0, 60, seconds);
    check_range_error("Minutes", 0, 59.1, minutes);
    check_range_error("Degrees", -90, 89.1, degrees);
    double new_declination{ degrees + minutes/60 + seconds/3600 };
    check_range_error("Declination", -90, 90, new_declination);
    // right_ascension = new_right_ascension;
    declination.degrees = degrees;
    declination.minutes = minutes;
    declination.seconds = seconds;

}

std::string astronomical_object::get_declination() const
{
    std::stringstream out;
    out<<declination.degrees<<"\u00B0"<<declination.minutes<<"\u2032"<<declination.seconds<<"\u2033";
    return out.str();
}


void astronomical_object::set_mass(double new_mass)
{   
    check_range_error("Mass", mass_bound_lower(), mass_bound_upper(), new_mass);

    mass = new_mass;
}

void astronomical_object::check_range_error(std::string quantity_name, double lower, double upper, double entered_value) const
{
    if ((entered_value >= upper) | entered_value < lower){
        std::stringstream error_message;
        error_message<<quantity_name<<" should be between "<<lower<<" and "<<upper<<". Value entered: " << entered_value;
        throw std::range_error(error_message.str());
    }
}




void astronomical_object::populate(std::ifstream& file, int& line_counter)
{   
    populate_base(file, line_counter);
    populate_derived(file, line_counter);
}
void astronomical_object::populate_base(std::ifstream& file, int& line_counter)
{   
    std::string new_right_ascension;
    read_line_into_var(file, GET_VARIABLE_NAME(right_ascension), new_right_ascension, line_counter);
    set_right_ascension(new_right_ascension);

    std::string new_declination;
    read_line_into_var(file, GET_VARIABLE_NAME(declination), new_declination, line_counter);
    set_declination(new_declination);

    double new_distance;
    read_line_into_var(file, GET_VARIABLE_NAME(distance), new_distance, line_counter);
    set_distance(new_distance);

    double new_mass;
    read_line_into_var(file, GET_VARIABLE_NAME(mass), new_mass, line_counter);
    set_mass(new_mass);

}

void astronomical_object::set_right_ascension(bool indent)
{
    bool looping{true};
    int hours;
    int minutes;
    double seconds;
    while (looping) {
        std::cout<<"right_ascension:\n";
        hours = input<int>("  hours: ", indent);
        minutes = input<int>("  minutes: ", indent);
        seconds = input<double>("  seconds: ", indent);
        try{
            set_right_ascension(hours, minutes, seconds);
            looping=false;
        }
        catch(std::range_error error) {
            std::cout<<error.what()<<std::endl;
        }
    }
}

void astronomical_object::set_declination(bool indent)
{
    bool looping{true};
    int degrees;
    int minutes;
    double seconds;
    while (looping) {
        std::cout<<"declination:\n";
        degrees = input<int>("  degrees: ", indent);
        minutes = input<int>("  minutes: ", indent);
        seconds = input<double>("  seconds: ", indent);
        try{
            set_declination(degrees, minutes, seconds);
            looping=false;
        }
        catch(std::range_error error) {
            std::cout<<error.what()<<std::endl;
        }
    }
}

void astronomical_object::remove_child_if_exists(std::string& child_name)
{
    auto it { children.find(child_name) };
    if (it != children.end()) {
        children.erase(it);
    }
}

void astronomical_object::populate(bool indent)
{
    populate_base(indent);
    populate_derived(indent);
}

void astronomical_object::populate_base(bool indent)
{   
    set_right_ascension(indent);
    set_declination(indent);

    double new_distance;
    prompt_and_read_into_var("distance (kpc)", new_distance, distance_bound_lower(), distance_bound_upper(), indent);
    set_distance(new_distance);

    double new_mass;
    prompt_and_read_into_var("mass (\u2609)", new_mass, mass_bound_lower(), mass_bound_upper(), indent);
    set_mass(new_mass);
}

void astronomical_object::prompt_and_read_into_var(const std::string &quantity_name, double& variable, const double lower_bound, const double upper_bound, bool indent)
{   
    double output;
    bool looping{true};
    while (looping) {
        looping=false;
        output = input<double>(quantity_name+": ", indent=indent);
        
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




void astronomical_object::prompt_and_read_into_var(const std::string &quantity_name, std::string& variable, const std::set<std::string>& allowed_values, bool indent)
{
    std::string output;
    bool looping{true};
    while (looping) {
        output = input<std::string>(quantity_name+": ", indent=indent);

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

void astronomical_object::prompt_and_read_into_var(const std::string &quantity_name, char& variable, const std::set<char>& allowed_values, bool indent)
{
    char output;
    bool looping{true};
    while (looping) {
        output = input<char>(quantity_name+": ", indent=indent);

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



