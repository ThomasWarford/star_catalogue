#ifndef ASTRONOMICAL_OBJECT
#define ASTRONOMICAL_OBJECT

#include <vector>
#include <string>
#include <fstream>
#include <set>

class astronomical_object
{
private:
    struct
    {
        int hours;
        int minutes;
        double seconds;
    } right_ascension;

    struct
    {
        int degrees;
        int minutes;
        double seconds;
    } declination;

    const std::string name;
    double mass;     // in solar masses
    double distance; // in parsecs
    std::set<std::string> children;

    virtual double mass_bound_lower() { return 0; }
    virtual double mass_bound_upper() = 0;
    virtual double distance_bound_lower() { return 0; }
    virtual double distance_bound_upper() { return 9.8e9; };

    void populate_base(std::ifstream &file, int &line_counter);
    virtual void populate_derived(std::ifstream &file, int &line_counter) = 0;
    void populate_base(bool indent);
    virtual void populate_derived(bool indent) = 0; 

    std::ostream &print_base(std::ostream &os) const;
    virtual std::ostream &print_derived(std::ostream &os) const = 0;

protected:

    void prompt_and_read_into_var(const std::string &quantity_name, double &variable, const double lower_bound, const double upper_bound, bool indent); // for numerical values
    void prompt_and_read_into_var(const std::string &quantity_name, std::string &variable, const std::set<std::string> &allowed_values, bool indent);   // for strings
    void prompt_and_read_into_var(const std::string &quantity_name, char &variable, const std::set<char> &allowed_values, bool indent);                 // for characters

public:
    inline astronomical_object(std::string name) : name{name} {};
    virtual std::string type() const = 0;
    virtual std::string colour() const = 0;  


    inline std::string get_name() { return name; }

    void set_distance(double new_distance);
    inline double get_distance() { return distance; }

    void set_right_ascension(int hours, int minutes, double seconds);
    void set_right_ascension(bool indent);               // from user
    void set_right_ascension(const std::string &string); // regex
    std::string get_right_ascension() const;

    void set_declination(int degrees, int minutes, double seconds);
    void set_declination(bool indent);               // prompt user
    void set_declination(const std::string &string); // regex
    std::string get_declination() const;

    void set_mass(double mass);
    inline double get_mass() { return mass; }

    inline void set_children(std::set<std::string> new_children) { children = new_children; }
    inline std::set<std::string> get_children() const { return children; }
    void remove_child_if_exists(std::string &child_name);
    inline void add_child(std::string new_child) { children.insert(new_child); }

    friend std::ostream &operator<<(std::ostream &os, const astronomical_object &output_astronomical_object);

    void check_range_error(std::string quantity_name, double lower, double upper, double entered_value) const;
    void populate(std::ifstream &file, int &line_counter);
    void populate(bool indent);
};

#endif