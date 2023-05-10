#ifndef STAR
#define STAR

#include<iostream>
#include"astronomical_object.h"


class star : public astronomical_object 
{
    // in solar masses // from https://en.wikipedia.org/wiki/List_of_star_extremes:
    double mass_bound_lower() override {return 0.05;}
    double mass_bound_upper() override {return 250;}

    const std::set<char> allowed_spectral_types{'O', 'B', 'A', 'F', 'G', 'K', 'M'};

    // from https://en.wikipedia.org/wiki/Apparent_magnitude
    const double relative_magnitude_lower{-28};
    const double relative_magnitude_upper{33};
    char spectral_type{' '};
    double relative_magnitude{-100};
    std::ostream& print_derived(std::ostream& os) const override;
    inline std::string type() const override {return "star";}
public:
    // star( std::string name, double mass, char spectral_type, double relative_magnitude, std::vector<std::string> children, std::string parent);
    star(std::string name): astronomical_object(name){};
    void set_spectral_type(char new_spectral_type);
    void set_relative_magnitude(double new_relative_magnitude);
    void populate_derived(std::ifstream& file, int& line_counter) override;
    void populate_derived(bool indent) override;

};


#endif