#ifndef GALAXY
#define GALAXY

#include"astronomical_object.h"
#include<iostream>


class galaxy : public astronomical_object 
{   
private:
    std::string hubble_type{""};
    const std::set<std::string> allowed_hubble_galaxy_types{"E0", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "S0", "Sa", "Sb", "Sc", "SBa", "SBb", "SBc", "Irr"};

    double mass_bound_lower() override {return 1e5;}
    double mass_bound_upper() override{return 1e16;}
    std::ostream& print_derived(std::ostream& os) const override;
    std::string type() const override {return "galaxy";}

public:
    galaxy(std::string name): astronomical_object{name} {}
    void set_hubble_type(std::string new_hubble_type);
    void populate_derived(std::ifstream& file, int& line_counter) override;
    void populate_derived() override;

};


#endif