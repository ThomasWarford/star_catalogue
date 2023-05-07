#include"functions.h"
#include<algorithm>

void wait_for_enter()
{
    std::cout << "Press Enter to Continue\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

bool yes_or_no(const std::string& prompt) 
{
    while (true) {
        char answer{input<char>(prompt+" (y/n)")};

        if (answer == 'y' || answer == 'Y'){
            return true;
        }

        if (answer == 'n' || answer == 'N'){
            return false;
        }
    
    }
}

bool common_element(const std::set<std::string>& set1, const std::set<std::string>& set2)
{
    return std::find_first_of(set1.begin(), set1.end(),
                            set2.begin(), set2.end()) != set1.end();
}
