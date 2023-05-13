#ifndef CATALOGUE
#define CATALOGUE

#include <map>
#include <string>
#include <iostream>
#include "astronomical_object.h"
#include <memory>

class catalogue
{
private:
    std::map<std::string, std::unique_ptr<astronomical_object>> object_ptrs;
    // Associate type strings with cases
    enum type_cases{is_star, is_galaxy ,is_planet ,is_misc};
    const std::map<std::string, type_cases> type_cases_map{
        {"star", type_cases::is_star},
        {"galaxy", type_cases::is_galaxy},
        {"planet", type_cases::is_planet},
        {"misc", type_cases::is_misc}};

    type_cases get_type_enum(std::string type_string) const;
    std::set<std::string> read_children(std::ifstream &file, int &line_counter) const;
    void set_object_children(std::unique_ptr<astronomical_object> &parent_object, bool recursion_check = true);

    void add_object(std::unique_ptr<astronomical_object> object);
    void add_object(std::string &name, bool second_call = false);

    void remove_object(std::string &name);

    std::vector<std::string>& sort_indices(std::vector<std::string> &indices) const;
    std::vector<std::string> get_parent_indices() const;

    std::pair<int, std::set<std::string>> get_number_of_objects_and_names(std::string file_name) const;
    void save(std::string &file_name) const;
    void load(std::string &file_name);

public:
    void set_object_children();
    void add_object();
    void remove_object();
    void print_children() const;

    std::vector<std::string> get_indices() const;
    friend std::ostream &operator<<(std::ostream &os, const catalogue &outputted_catalogue);
    void print(std::vector<std::string> &indexes) const;
    void print() const;
    void save() const;
    void load();
};

#endif