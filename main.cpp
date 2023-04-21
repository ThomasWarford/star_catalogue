#include<iostream>
#include<vector>
#include<map>
#include<string>
#include"astronomical_object.h"
#include"galaxy.h"
#include"star.h"
#include"catalogue.h"
#include"io_functions.h"

const std::vector<std::string> EMPTY_STRING_VECTOR = std::vector<std::string>();

int main() 
{   
    bool looping{true};
    catalogue cat;

    std::cout<<"Welcome to Tom's star catalogue."<<std::endl<<std::endl;

    while(looping){

        looping = false;
        std::cout<<"Enter a number to select one of the following options to start."<<std::endl;
        std::cout<<"1: Load catalogue from file."<<std::endl;
        int choice{ input<int>("Please enter an integer.") };
        
        switch (choice){
            case 1:{
                std::cout << "Please enter a file name."<<std::endl;
                std::string file_name{ input<std::string>("File name should be a string without spaces.") };
                cat.load(file_name);
                std::cerr<<cat;
                // cat.save("deez.cat");
                break;
            }
                
            default:
                looping=true;
                std::cout<<"Please input a listed integer."<<std::endl;
            }
        
        }
 //#################################################

    // astronomical_object ao{"ao", 10, EMPTY_STRING_VECTOR, "father"};

    // star_1.set_mass(1);
    // star_1.set_parent("sda");
    // star_1.set_spectral_type('O');
    // star_1.set_relative_magnitude(3);

    // galaxy galaxy_1{"galaxy_1"};
    // galaxy_1.set_mass(1e8);
    // galaxy_1.set_hubble_type("E3");

    // star star_1{"star_1"};
    // galaxy galaxy_1{"galaxy_1"};
    // catalogue cat;
    // cat.add_object(star_1);
    // cat.add_object(galaxy_1);
    // std::cout<<cat;
    // std::cout<<hooray<<std::endl;

    // std::cout<<ao<<std::endl;
    // std::cout<<star_1<<std::endl;

    // cat.add_object(ao);
    // cat.add_object(star_1);
    // cat.add_object(galaxy_1);
    // std::cout<<cat["star_1"];

    // cat.save("catalogue.cat"); // if fails should print failed!!
    // cat.load_from_file("catalogue.cat");

    // std::cout<<cat;

    // std::string string{"name: a_name"};
    // std::string name;
    
    // catalogue cat_2;
    // cat_2.load("catalogue.cat");
    
    return 0;
}