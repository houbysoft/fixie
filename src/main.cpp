#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "fixieTokenizer.h"


int main(int argc, char **argv) {
    
    if (argc < 2) {
        std::cout << "Must enter atleast one file to compile as an argument." << std::endl;
        return 0;
    }

    std::ifstream file(argv[1]);
    if (file.is_open()) {
        std::cout << "Cranking..." << std::endl;
        std::stringstream buffer;
        buffer << file.rdbuf();
        FixieTokenizer *tok = new FixieTokenizer(buffer.str());
    }
    else {
        std::cout << "Bad file." << std::endl;
    }
}

