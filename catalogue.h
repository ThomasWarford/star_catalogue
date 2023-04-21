#ifndef CATALOGUE
#define CATALOGUE

#include<map>
#include<string>
#include<iostream>
#include"astronomical_object.h"



class catalogue
{
private:
    std::map<std::string, astronomical_object*> object_ptrs;
    int get_number_of_objects(std::string file_name) const;
public:
    // std::pair<std::map<std::string, astronomical_object*>::iterator, bool> add_object(astronomical_object* object_ptr)
    void add_object(astronomical_object *object);
    astronomical_object& operator[](std::string);
    friend std::ostream& operator<<(std::ostream& os, const catalogue& outputted_catalogue);
    // returns 1 and cancels if file already exists
    void save(std::string file_name) const;
    void load(std::string file_name);


    
    // astronomical_object* get_parent(std::string key);
    // catalogue get_children(std::string key); returns a subcatalogue, must be efficent
    // do I overload << or just make a print function? Pretty print is different to computer-friendly file.
    // use latex as inspiration!!

    // reading in:
    // name: ___
    // check if already exists, if so cancel operation (maybe ask user, option to override all, ect.)
    // type: ___
    // then use constructor of this type 
    // easiest to have constructor of empty object, then populate individually

    // base_attributes: ___
    // specialized_attributes:___

};


#endif