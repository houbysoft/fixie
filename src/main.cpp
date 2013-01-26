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
        FixieTokenizer *tok = new FixieTokenizer();
        std::string line;
        int lineNumber = 0;
        std::vector<FixieTokenizer::token> *tokens = new std::vector<FixieTokenizer::token>();
        while (file.good()) {
            lineNumber++;
            getline(file,line);
            tok->tokenize(lineNumber,line,tokens);
        }
        for (int i = 0; i < tokens->size(); i++) {
            std::cout << tokens->at(i).lineNumber << ": " << tokens->at(i).string << std::endl;
        }
    }
    else {
        std::cout << "Bad file." << std::endl;
    }
}

