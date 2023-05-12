#ifndef MISC_OBJECT
#define MISC_OBJECT

#include"astronomical_object.h"


class misc_object : public astronomical_object 
{
private:
    inline double mass_bound_upper() override {return 1e52;} // mass of observable universe
    
    std::ostream& print_derived(std::ostream& os) const override {return os;}
public:
    misc_object(std::string name) : astronomical_object(name) {};
    inline std::string type() const override {return "misc";}
    inline std::string colour() const override {return "\033[35m";}

    
    void populate_derived(std::ifstream& file, int& line_counter) override {};
    void populate_derived(bool indent) override {};

};

#endif