#include"functions.h"
#include "planet.h"

void planet::set_period(double new_period)
{
    check_range_error("Period", period_bound_lower, period_bound_upper, new_period);
    period = new_period;
}


std::ostream& planet::print_derived(std::ostream& os) const
{
    print_table_row(os, GET_VARIABLE_NAME(period), period); 
    return os;
}

void planet::populate_derived(std::ifstream& file, int& line_counter)
{
    double new_period;
    read_line_into_var(file, GET_VARIABLE_NAME(period), new_period, line_counter);
    set_period(new_period);
}

void planet::populate_derived(bool indent)
{
    double new_period;
    prompt_and_read_into_var("period (yrs)", new_period, period_bound_lower, period_bound_upper, indent);
    set_period(new_period);
}
