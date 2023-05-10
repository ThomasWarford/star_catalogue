#ifndef CATALOGUE
#define CATALOGUE

#include<map>
#include<string>
#include<iostream>
#include"astronomical_object.h"
#include<memory>


class catalogue
{
private:
    std::map<std::string, std::unique_ptr<astronomical_object>> object_ptrs;
    std::pair<int, std::set<std::string>> get_number_of_objects_and_names(std::string file_name) const;
    enum type_cases { is_star, is_galaxy, is_planet, is_misc }; // defined here so it's only defined once // would be good to put const!
    std::map<std::string, type_cases> type_cases_map{
        {"star", type_cases::is_star}, {"galaxy", type_cases::is_galaxy}, {"planet", type_cases::is_planet}, { "misc", type_cases::is_misc} 
        };
    type_cases get_type_enum(std::string type_string) const;
    std::set<std::string> read_children(std::ifstream& file, int& line_counter) const;
    void set_object_children(std::unique_ptr<astronomical_object>& parent_object, bool recursion_check=true);



public:
    ~catalogue(){};
    void set_object_children();
    void print() const;
    // std::pair<std::map<std::string, astronomical_object*>::iterator, bool> add_object(astronomical_object* object_ptr)
    void add_object(std::unique_ptr<astronomical_object> object);
    void add_object(std::string& name, bool second_call=false);
    void add_object();
    void remove_object(std::string& name);
    void remove_object();
    std::vector<std::string> get_indices() const;
    std::vector<std::string>& sort_indices(std::vector<std::string>& indices) const;
    void print_children() const;
    std::vector<std::string> get_parent_indices() const;
    // astronomical_object& operator[](std::string);
    friend std::ostream& operator<<(std::ostream& os, const catalogue& outputted_catalogue);
    void print(std::vector<std::string>& indexes) const;
    // returns 1 and cancels if file already exists
    // void set_object_children(std::unique_ptr<astronomical_object> parent_object, std::vector<std::string>& children_names);
    void save(std::string& file_name) const;
    void load(std::string& file_name);
    void save() const;
    void load();

    
    // astronomical_object* get_parent(std::string key);
    // catalogue get_children(std::string key); returns a subcatalogue, must be efficent
    // do I overload << or just make a print function? Pretty print is different to computer-friendly file.
    // use latex as inspiration!!

    // reading in:
    // name: ___
    // check if already exists, if so cancel operation (maybe ask user, option to override all, ect.)
    // type: ___
    // then use constructor of this type 
    // easiest to have constructor of empty object, then populate individually

    // base_attributes: ___
    // specialized_attributes:___

};


#endif