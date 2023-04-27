#include<fstream>
#include<sstream>
#include"io_functions.h"
#include"catalogue.h"
#include"star.h"
#include"galaxy.h"


void catalogue::add_object(std::unique_ptr<astronomical_object> object)
{   
    auto result = object_ptrs.emplace(std::pair(object->get_name(), std::move(object)));
    if (!result.second){ // if emplace fails
        std::stringstream error_message;
        error_message<<"Object with name "<<object->get_name()<<" already exists.";
        throw std::invalid_argument(error_message.str());
    }
}

void catalogue::add_object()
{
    std::string name{ input<std::string>("name: ") };

    while( object_ptrs.find(name) != object_ptrs.end() ){
        std::cout<<name<<" is already in the catalogue. Enter a different name. \n";
        std::string name{ input<std::string>("name: ") };
    }

    std::string type_string;
    type_cases type_enum;
    // while (type_cases_map.find(type_string) != type_cases_map.end()){
    //     type_string = input<std::string>("type: ");
    // }
    bool looping{true};
    while (looping) {
        looping = false;
        type_string = input<std::string>("type: ");
        
        // try to get type_cases member corresponding with entered string
        try {
            type_enum = get_type_enum(type_string);
        }
        catch (std::invalid_argument error) {  
            std::cout<<error.what();
            looping=true;
        }
    }

    std::unique_ptr<astronomical_object> new_object_ptr;

    switch(type_enum){
        case is_star:
            std::cout<<"*star*";
            new_object_ptr = std::unique_ptr<astronomical_object>( new star(name) ); 
            break;

        case is_galaxy:
            std::cout<<"*galaxy*";
            break;
        default:
            break;
    }


    new_object_ptr->populate();
}


// astronomical_object& catalogue::operator[](std::string index)
// {
//     return *object_ptrs[index];
// }

std::ostream& operator<<(std::ostream& os, const catalogue& outputted_catalogue)
{
    for (auto const& key_value: outputted_catalogue.object_ptrs) {
        os << (*key_value.second);
        os << '\n';
    }

    return os;
}

void catalogue::save(std::string file_name) const
{
    std::ofstream file;
    file.open(file_name, std::ios::out);
    file << (*this);
    file.close();
}

catalogue::type_cases catalogue::get_type_enum(std::string type_string) const
{   
    auto iterator{type_cases_map.find(type_string)};
    if (iterator == type_cases_map.end()) {
        throw std::invalid_argument("Invalid astronomical object type: " + type_string + "\n");
    }

    return iterator->second;
}

void catalogue::load(std::string file_name)
{   
    int number_of_objects{get_number_of_objects(file_name)};
    catalogue new_catalogue;
    std::ifstream file;
    file.open(file_name);
    std::string line_string;

    std::string name;
    std::string type;

    int line_counter{0};
    try{
        for (int i{0}; i<number_of_objects; i++) {
            read_line_into_var(file, GET_VARIABLE_NAME(name), name, line_counter);
            read_line_into_var(file, GET_VARIABLE_NAME(type), type, line_counter);

            std::unique_ptr<astronomical_object> new_object_ptr;
            
            switch(get_type_enum(type)) {
                case type_cases::is_star:
                    std::cerr <<"*star*";
                    new_object_ptr = std::unique_ptr<astronomical_object>( new star(name) ); 
                    break;
                
                case type_cases::is_galaxy:
                    std::cerr <<"*galaxy*";
                    new_object_ptr = std::unique_ptr<astronomical_object>( new galaxy(name) ); 

                    break;
                

                default:
                    throw std::invalid_argument("Invalid astronomical object type.");
            } 

            new_object_ptr->populate(file, line_counter);
            new_catalogue.add_object(std::move(new_object_ptr));      

            line_counter++;
            std::getline(file, line_string);
            if (!line_string.empty()){
                throw std::invalid_argument("There should be empty lines between entries.");
            }
        }

        // for (auto ptr : object_ptrs){delete ptr.second;} 
        // object_ptrs.clear();
        
        object_ptrs = std::move(new_catalogue.object_ptrs);
    }
    catch(std::exception& error){
        std::stringstream error_message;
        error_message<<"Error on line "<<line_counter<<" of file \""<<file_name<<"\".\n"<<error.what();
        throw std::invalid_argument(error_message.str());
    }
    
}

void catalogue::load()
{
    std::string file_name{ input<std::string>("Please enter a file name without spaces.\n") };
    load(file_name);
    std::cout << file_name << " loaded."<<std::endl;
}

int catalogue::get_number_of_objects(std::string file_name) const
{
    std::ifstream file;
    file.open(file_name);
    std::string line_string;
    int line_counter{0};
    int object_counter{0};


    if (!file.good()){
        throw std::invalid_argument("File not found.");
    }


    while (std::getline(file, line_string)) {
        line_counter++;
        std::string first_word_of_line;
        std::stringstream line_stream{line_string};
        if ((line_stream >> first_word_of_line) && (first_word_of_line=="name")) {
            object_counter++;
        }
    }

    file.close();
    return object_counter;
}


// template function taking line and checking it follows "name: type" format, returning value of type 


