#include <iostream>
#include <fstream>
#include <string>
#include "fixieTokenizer.h"
#include "fixieParser.h"

#define TESTING 1


int main(int argc, char **argv) {

    //Remind the stupid that they must specify a file
    
    if (argc < 2) {
        std::cout << "Must enter a file to compile as an argument." << std::endl;
        return 0;
    }

    //Open up our file

    std::ifstream file(argv[1]);
    if (file.is_open()) {

        //Provide some user feedback

        std::cout << "Cranking..." << std::endl;

        //Set up the tokenizer and our necessary variables

        FixieTokenizer *tokenizer = new FixieTokenizer();
        std::vector<FixieTokenizer::token> *tokens = tokenizer->tokenize(&file);

        //If we're testing we read off our line numbers and chunks

        if (TESTING) {
            std::cout << std::endl << "TOKENS LIST:" << std::endl;
            for (int i = 0; i < tokens->size(); i++) {
                std::cout << tokens->at(i).lineNumber << ": " << tokens->at(i).string << std::endl;
            }
        }

        //Set up the parser

        FixieParser *parser = new FixieParser();
        parser->parse(tokens);
    }
    else {
        std::cout << "Bad file." << std::endl;
    }
}

