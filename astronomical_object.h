#ifndef ASTRONOMICAL_OBJECT
#define ASTRONOMICAL_OBJECT


#include<vector>
#include<string>
#include<fstream>
#include<set>




class astronomical_object 
{
private:
    const std::string name;
    double mass;
    std::set<std::string> children;
    std::string parent;
    virtual std::string type() const=0;
    virtual double mass_bound_lower() {return 0;}
    virtual double mass_bound_upper() {return 0;}

public: 
    virtual std::ostream& print_derived(std::ostream& os) const = 0;
    inline astronomical_object(std::string name): name{name}{};
    void set_mass(double mass);
    inline void set_children(std::set<std::string> new_children){children = new_children;}
    inline void add_child(std::string new_child){children.insert(new_child);}
    inline void set_parent(std::string new_parent){parent=new_parent;}
    inline std::string get_name() {return name;}
    friend std::ostream& operator<<(std::ostream& os, const astronomical_object& output_astronomical_object);
    std::ostream& print_base(std::ostream& os) const;
    void check_range_error(std::string quantity_name, double lower, double upper, double entered_value) const;
    void populate(std::ifstream& file, int& line_counter);
    void populate_base(std::ifstream& file, int& line_counter);
    virtual void populate_derived(std::ifstream& file, int& line_counter)=0;

    void populate(bool indent);
    void populate_base(bool indent);
    virtual void populate_derived(bool indent)=0;

    void prompt_and_read_into_var(const std::string &quantity_name, double& variable, const double lower_bound, const double upper_bound, bool indent);
    void prompt_and_read_into_var(const std::string &quantity_name, std::string& variable, const std::set<std::string>& allowed_values, bool indent);
    void prompt_and_read_into_var(const std::string &quantity_name, char& variable, const std::set<char>& allowed_values, bool indent);

};



#endif