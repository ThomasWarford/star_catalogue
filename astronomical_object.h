#ifndef ASTRONOMICAL_OBJECT
#define ASTRONOMICAL_OBJECT


#include<vector>
#include<string>
#include<fstream>
#include<functional>
#include"io_functions.h"



class astronomical_object 
{
private:
    const std::string name;
    double mass;
    std::vector<std::string> children;
    std::string parent;
    virtual std::string type() const=0;
    virtual double mass_bound_lower() {return 0;}
    virtual double mass_bound_upper() {return 0;}

public: 
    virtual std::ostream& print_derived(std::ostream& os) const = 0;
    inline astronomical_object(std::string name): name{name}{};
    // astronomical_object(std::string name, double mass, std::vector<std::string> children=std::vector<std::string>(), std::string parent="");
    void set_mass(double mass);
    void set_children(std::vector<std::string> new_children);
    void set_parent(std::string new_parent);
    inline std::string get_name() {return name;}
    friend std::ostream& operator<<(std::ostream& os, const astronomical_object& output_astronomical_object);
    std::ostream& print_base(std::ostream& os) const;
    void check_range_error(std::string quantity_name, double lower, double upper, double entered_value) const;
    void populate(std::ifstream& file, int& line_counter);
    void populate_base(std::ifstream& file, int& line_counter);
    virtual void populate_derived(std::ifstream& file, int& line_counter)=0;

    void populate();
    void populate_base();
    // virtual void populate_derived()=0;

    // template<typename T>
    // void prompt_and_set(const std::string prompt, std::function<void(T)> setter);

    // template<typename T>
    // void read_line_and_set(std::ifstream& file, const std::string& variable_name, std::function<void(T)> setter, int& line_number);

    template<typename T>
    void prompt_and_set(const std::string& prompt, void (astronomical_object::*setter)(T))
    {
        bool looping{true};
        T output;

        while (looping) {
            looping = false;
            try {
                (this->*setter)( input<T>(prompt) );
            }
            catch (std::exception error) {
                looping = false;
                std::cout<<error.what()<<std::endl;
            }
        }
    }
};


// prompts user for an input, then runs function with that input. Repeats until function runs without throwing an error.
// template<typename T>
// void astronomical_object::prompt_and_read_into_var(const std::string prompt, std::function<void(T)> setter)
// {
//     bool looping{true};
//     T output;

//     while (looping) {
//         looping = false;
//     }
// }

// template<typename T>
// void astronomical_object::read_line_and_set(std::ifstream& file, const std::string& variable_name, void (astronomical_object::*setter)(T), int& line_number)
// {   
//     T new_value;
//     read_line_into_var(file, variable_name, new_value, line_number);
//     setter(new_value);
// }
#endif