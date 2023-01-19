#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include "compare.h"

int main()
{

    namespace fs = std::filesystem;
    std::string to_path;


    std::cout << "when you re entering directory, either you re putting the full directory \n";
    std::cout << "\ne.g.) /net/laguna/h1/k/kikiroh/Bar/submissions \n";
    std::cout << "or \n";
    std::cout << "submissions, if your submissions folder is in the same directory \n";
    std::cout << "where all the compare.h compare.cpp file stored at \n\n\n";
    std::cout << "Please enter your directory: ";
    std::cin >> to_path;
    fs::path p1(to_path);

    //declare new CompareFiles variable using its constructor 
    CompareFiles new_compare(p1);

    // using comparison functions to have the final result.
    new_compare.comparison_function();


    return 0;

}
