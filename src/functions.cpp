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
