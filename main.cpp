#include<iostream>
#include<vector>
#include<map>
#include<string>
#include"astronomical_object.h"
#include"galaxy.h"
#include"star.h"
#include"catalogue.h"
#include"functions.h"

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
            int choice{ input<int>("Please enter an integer. \n") };
            
            switch (choice){
                case 1:{
                    cat.load();
                    break;
                }
                case 2:{
                    cat.add_object();
                    break;
                }
                    
                default:
                    throw std::invalid_argument("Please input a listed integer.");
            }
        }
        catch(std::exception& error){
            looping=true;
            std::cout<<error.what()<<'\n'<<'\n';
        }
        wait_for_enter();
    }

    looping =true;
    while(looping){
        try{             
            std::cout<<"Enter a number to select one of the following options to continue."<<std::endl;
            std::cout<<"1: View the catalogue."<<std::endl;
            std::cout<<"2: Save the catalogue."<<std::endl;
            std::cout<<"3: Add additional object."<<std::endl;
            std::cout<<"4: Merge catalogue with another catalogue file."<<std::endl;
            std::cout<<"5: Remove an object."<<std::endl;
            std::cout<<"6: View children of object."<<std::endl;
            std::cout<<"7: Select and sort objects."<<std::endl;
            std::cout<<"8: Quit."<<std::endl;


            int choice{ input<int>("Please enter an integer. \n") };
            
            switch (choice){
                case 1:{
                    std::cout<<cat;
                    break;
                }
                case 2:{
                    cat.save();
                    break;
                }
                case 3:{ // add object
                    cat.add_object();
                    break;
                }
                case 4:{ // merge with another file
                    cat.load();
                    break;
                }
                case 5:{ // remove an object
                    cat.remove_object();
                    break;
                }
                case 6:{ // view children subcatalogue
                    cat.print_children();
                    break;
                }
                case 7:{ // select and sort
                    std::vector<std::string> indices = cat.get_indices();
                    cat.print(indices);
                    break;
                }
                case 8:{ // quit
                    looping=false;
                    std::cout<<"Thank you for using the catalogue."<<std::endl;
                    break;
                }
                    
                default:
                    throw std::invalid_argument("Please input a listed integer.");
            }
        }
        catch(std::exception& error){
            looping=true;
            std::cout<<error.what()<<'\n'<<'\n';
        }
        wait_for_enter();
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