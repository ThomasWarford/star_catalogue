#include<sstream>
#include<fstream>
#include<algorithm>
#include<iterator>
#include<any>
#include"functions.h"
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
    add_object(name);
}

void catalogue::add_object(std::string& name, bool second_call)
{
    std::string type_string;
    type_cases type_enum;
    // while (type_cases_map.find(type_string) != type_cases_map.end()){
    //     type_string = input<std::string>("type: ");
    // }
    bool looping{true};
    while (looping) {
        looping = false;
        type_string = input<std::string>("type: ", second_call);
        
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
            new_object_ptr = std::unique_ptr<astronomical_object>( new galaxy(name) ); 
            break;
        default:
            break;
    }


    new_object_ptr->populate(second_call); // indent prompting if second call

    if (!second_call){
        set_object_children(new_object_ptr);
    }

    add_object(std::move(new_object_ptr));
}

void catalogue::set_object_children(std::unique_ptr<astronomical_object>& parent_object)
{
    std::string child_name;

    while (true){
        child_name = input<std::string>("Enter the name of a child object of parent "+parent_object->get_name()+ " (or enter nothing to stop): ");
        
        if (child_name==parent_object->get_name()) {
            std::cout<<"Object cannot be its own child.\n";
            continue;
        }

        if (child_name.empty()){ // Exit when the user presses enter
            return;

        }
        if (object_ptrs.find(child_name) == object_ptrs.end()){ // if child is not in the catalogue
            std::cout<<child_name<<" is not in the catalogue.\n";
            if (yes_or_no("Create a new child "+child_name+" of parent "+parent_object->get_name()+ "?")){
                parent_object->add_child(child_name);
                add_object(child_name, true); // second_call = true to prevent 'grandparent' being created again as child
            }
            else{
                std::cout<<"Child "+child_name+" not added to parent "+parent_object->get_name()+".\n";
            }
        }
        else { // if child is in the catalogue
            parent_object->add_child(child_name);
        }
    }
}

void catalogue::remove_object(std::string& name)
{
    if (!object_ptrs.erase(name)){
        throw std::invalid_argument("Object with name "+name+" does not exist.\n");
    }
}

void catalogue::remove_object()
{
    std::string name{ input<std::string>("Name of object to remove: ") };

    remove_object(name);
    std::cout<<"Object with name "<<name<<" removed.\n";
}

std::ostream& operator<<(std::ostream& os, const catalogue& outputted_catalogue)
{
    for (auto const& key_value: outputted_catalogue.object_ptrs) {
        os << (*key_value.second);
        os << '\n';
    }

    return os;
}

void catalogue::print(std::vector<std::string>& indexes) const
{   
    if (indexes.empty()){
        for (auto& key_value: object_ptrs){
            std::cout << *(key_value.second);
            std::cout << '\n';
        }
    }
    else{
        for (auto& index: indexes) {
            std::cout << *(object_ptrs.at(index));
            std::cout << '\n';
        }
    }
}

std::vector<std::string> catalogue::get_indices() const
{
    std::cout<<"Would you like to print objects of a specific type?\n";

    std::string type;    
    bool looping{true};
    while (looping){
        std::cout<<"Allowed types are: ";
        for (auto const& key_value: type_cases_map) {
            std::cout<<key_value.first<<",";
        }
        std::cout<<"\nOr enter nothing to print all objects.\n";


        type = input<std::string>("Type: ");

        if (type_cases_map.find(type) != type_cases_map.end()) { // if type is in the map
            looping = false;
        }
        if (type.empty()){ 
            looping = false;
        }    

    }

    std::vector<std::string> indices;

    if (type.empty()){ // add all keys to indices
        for (auto const& key_value: object_ptrs) {
            indices.push_back(key_value.first);
        }
    }
    else{ // add keys of specified type to indices
        for (auto const& key_value: object_ptrs) {
                if (key_value.second->type() == type) {
                    indices.push_back(key_value.first);
                }
            }
    }

    sort_indices(indices);

    return indices;
}

std::vector<std::string> catalogue::get_parent_indices() const
{
    std::vector<std::string> indices;
    for (auto& key_value: object_ptrs) {
        if ( !(key_value.second->get_children().empty()) ) {
            indices.push_back(key_value.first);
        }
    }

    return indices;
}

std::vector<std::string>& catalogue::sort_indices(std::vector<std::string>& indices) const
{
    std::cout<<"How would you like to sort the objects?\n";

    std::set<std::string> sort_by_options{"mass", "type", "string"};
    
    bool looping{true};
    std::string sort_by;
    while (looping){
        std::cout<<"You can sort by mass, name or type (entering nothing will sort by name.\n";
        sort_by = input<std::string>("Sort by: ");

        if (sort_by_options.find(sort_by) != sort_by_options.end()) { // if type is in the map
            looping = false;
        }
        if (sort_by.empty()){ 
            return indices;
        }    
    }

    std::any lambda;
    if (sort_by=="mass"){
        std::sort(indices.begin(), indices.end(), [this](std::string& i, std::string& j){ return (object_ptrs.at(i)->get_mass() > object_ptrs.at(j)->get_mass()); }); 
    }
    if (sort_by=="type"){
        std::sort(indices.begin(), indices.end(), [this](std::string& i, std::string& j){ return (object_ptrs.at(i)->type() < object_ptrs.at(j)->type()); }); 
    }

    // map is already sorted by name!

    return indices;
}

void catalogue::print_children() const
{
    bool looping{true};
    std::string name;
    std::vector<std::string> parents{get_parent_indices()};

    if (parents.empty()){
        std::cout<<"There are no parents in the catalogue.\n";
        return;
    }



    while(looping) {
        std::cout<<"The available parents are:";
        for (auto& parent: parents){
            std::cout<<" "<<parent;
        }
        std::cout<<".\n";
        name = input<std::string>("Enter a parent name: ");
        if (std::find(parents.begin(), parents.end(), name) == parents.end()) {
            looping = true;
            std::cout<<name<<" is not a parent.\n";
        }
        else {
            looping = false;
        }
    }

    std::set<std::string> children = object_ptrs.at(name)->get_children();

    if (children.empty()) {
        std::cout << name << " has no children!";
        return;
    }

    std::vector<std::string> indices{children.begin(), children.end()};
    
    sort_indices(indices);

    print(indices);
}

void catalogue::save(std::string& file_name) const
{
    std::ofstream file;
    file.open(file_name, std::ios::out);
    file << (*this);
    file.close();
}

void catalogue::save() const
{
    std::string file_name{ input<std::string>("Enter a file name without spaces (the file will be overwritten.)\n") };
    save(file_name);
}

catalogue::type_cases catalogue::get_type_enum(std::string type_string) const
{   
    auto iterator{type_cases_map.find(type_string)};
    if (iterator == type_cases_map.end()) {
        throw std::invalid_argument("Invalid astronomical object type: " + type_string + "\n");
    }

    return iterator->second;
}

std::set<std::string> catalogue::read_children(std::ifstream& file, int& line_number) const
{
    line_number++;
    std::set<std::string> children;

    std::string line_string;
    std::getline(file, line_string);
    std::stringstream ss{line_string};
    std::string first_string;
    std::string child_name;

    if ((ss>>first_string) && (first_string=="children")){ 
        while(ss>>child_name){
            if (!children.insert(child_name).second) { // returns true if successful
                throw std::invalid_argument("Duplicate child name: "+child_name+"\n");
            }
        }
    }
    else {
        throw std::invalid_argument("Expected line to take form: children   child_name_1    child_name_2 ...\n");
    }

    return children;
}

// bool catalogue::any_names_in_catalogue(const std::set<std::string>& names)
// {
//     auto it = std::find_first_of(object_ptrs.begin(), object_ptrs.end(), names.begin(), names.end(),
//                                 [](const std::pair<const std::string, std::unique_ptr<astronomical_object>>& map_pair, const std::string& set_value) {
//                                     return map_pair.first == set_value;
//                                 });

//     return it != object_ptrs.end();
// }



void catalogue::load(std::string& file_name)
{   
    auto [number_of_objects, object_names]{get_number_of_objects_and_names(file_name)};
    
    // Puts keys of object_ptrs into object_names:
    std::transform(
        object_ptrs.begin(), object_ptrs.end(),
        std::inserter(object_names, object_names.end()),
        [](auto& pair){ return pair.first; }
        );

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
            if (object_ptrs.count(name)){
                throw std::invalid_argument("Object with name "+name+" already exists.\n");
            }
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
            std::set<std::string> children{read_children(file, line_counter)};
            
            // Check that object is not its own child:
            if (children.count(name)) {
                throw std::invalid_argument("Object with name "+name+" cannot be a child of itself.\n");
            }

            // Check that children is a subset of all object names:
            if (!std::includes(object_names.begin(), object_names.end(), children.begin(), children.end())){
                std::stringstream error_message;
                error_message<<"Children names: ";

                for (auto child : children) {
                    std::cout<<child<<std::endl;
                    if (!object_names.count(child)){
                        error_message<<child<<", ";
                    }
                }

                error_message<<"do not exist in catalogue or file.\n";
                error_message<<"Create objects with these names first.\n";
                throw std::invalid_argument(error_message.str());
            }

            new_object_ptr->set_children(children);
            new_catalogue.add_object(std::move(new_object_ptr));  
            


            line_counter++;
            std::getline(file, line_string);
            if (!line_string.empty()){
                throw std::invalid_argument("There should be empty lines between entries.");
            }
        }

        // for (auto ptr : object_ptrs){delete ptr.second;} 
        // object_ptrs.clear();
        
        // object_ptrs = std::move(new_catalogue.object_ptrs);
        object_ptrs.insert(
            std::make_move_iterator(new_catalogue.object_ptrs.begin()),
            std::make_move_iterator(new_catalogue.object_ptrs.end())
            );

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

std::pair<int, std::set<std::string>> catalogue::get_number_of_objects_and_names(std::string file_name) const
{
    std::ifstream file;
    file.open(file_name);
    std::string line_string;
    int line_counter{0};
    int object_counter{0};
    std::set<std::string> object_names;


    if (!file.good()){
        throw std::invalid_argument("File not found.");
    }


    while (std::getline(file, line_string)) {
        line_counter++;
        std::string first_word_of_line;
        std::string second_word_of_line;
        std::stringstream line_stream{line_string};
        if ((line_stream >> first_word_of_line) && (first_word_of_line=="name")) {
            if (line_stream>>second_word_of_line) {
                object_counter++;
                object_names.insert(second_word_of_line);
            }
            else{
                throw std::invalid_argument("Line "+std::to_string(line_counter)+": name is missing.");
            }

        }
    }

    file.close();
    return std::pair<int, std::set<std::string>>{object_counter, object_names};
}


// template function taking line and checking it follows "name: type" format, returning value of type


