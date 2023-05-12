#ifndef PLANET
#define PLANET

#include"astronomical_object.h"


class planet : public astronomical_object 
{
private:
    double period; // years
    const double period_bound_lower{5e-5};
    const double period_bound_upper{1.5e6};

    // from https://en.wikipedia.org/wiki/List_of_exoplanet_extremes
    inline double mass_bound_lower() override {return 1e-9;}
    inline double mass_bound_upper() override {return 0.08;}
    inline double distance_bound_lower() override {return 0;}
    inline double distance_bound_upper() override {return 9000.0;}

    std::ostream& print_derived(std::ostream& os) const override;

public:
    planet(std::string name) : astronomical_object(name) {};
    inline std::string type() const override {return "planet";}
    inline std::string colour() const override {return "\033[32m";}

    void populate_derived(std::ifstream& file, int& line_counter) override;
    void populate_derived(bool indent) override;
    void set_period(double new_period);

};

#endif