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
    catalogue cat;

    std::cout<<"Welcome to Tom's star catalogue."<<std::endl<<std::endl;

    bool looping{true};
    while(looping){
        try{             
            looping = false;
            std::cout<<"Enter a number to select one of the following options to start."<<std::endl;
            std::cout<<"1: Load catalogue from file."<<std::endl;
            std::cout<<"2: Create new catalogue."<<std::endl;
            int choice{ input<int>("Please enter an integer.") };
            
            switch (choice){
                case 1:{
                    cat.load();
                    cat.save("deez.cat");
                    break;
                }
                case 2:{
                    // cat.create
                }
                    
                default:
                    throw std::invalid_argument("Please input a listed integer.");
            }
        }
        catch(std::exception& error){
            looping=true;
            std::cout<<error.what()<<'\n'<<'\n';
        }

    }

 //#################################################

    // star* star_ptr = new star("star_1");
    // galaxy* galaxy_ptr = new galaxy("galaxy_1");
    // catalogue cat;
    // cat.add_object(star_ptr);
    // cat.add_object(galaxy_ptr);
    // std::cout<<cat;
    
    return 0;
}