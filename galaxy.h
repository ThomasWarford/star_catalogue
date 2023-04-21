#ifndef GALAXY
#define GALAXY

#include"astronomical_object.h"
#include<iostream>


class galaxy : public astronomical_object 
{   
private:
    std::string hubble_type{""};
    double mass_bound_lower() override {return 1e5;}
    double mass_bound_upper() override{return 1e16;}
    std::ostream& print_derived(std::ostream& os) const override;
    std::string type() const override {return "galaxy";}

public:
    galaxy(std::string name): astronomical_object{name} {}
    void set_hubble_type(std::string new_hubble_type);
    void populate_derived(std::ifstream& file, int& line_counter) override;

};


#endif