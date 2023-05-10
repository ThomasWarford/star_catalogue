#ifndef MISC_OBJECT
#define MISC_OBJECT

#include"astronomical_object.h"


class misc_object : public astronomical_object 
{
private:
    // fromhttps://en.wikipedia.org/wiki/List_of_exoplanet_extremes
    inline double mass_bound_upper() override {return 9000.0;}
    

    // inline std::ostream& print_derived(std::ostream& os) const override {};
    inline std::string type() const override {return "misc";}
    inline std::string colour() const override {return "\033[35m";}

public:
    misc_object(std::string name) : astronomical_object(name) {};
    void populate_derived(std::ifstream& file, int& line_counter) override {};
    void populate_derived(bool indent) override {};
    std::ostream& print_derived(std::ostream& os) const override {return os;}

};

#endif