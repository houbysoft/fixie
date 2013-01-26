#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "fixieTokenizer.h"


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
        std::vector<FixieTokenizer::token> *tokens = new std::vector<FixieTokenizer::token>();
        std::string line;
        int lineNumber = 0;

        //Read off the lines into the tokenizer

        while (file.good()) {
            lineNumber++;
            getline(file,line);

            //The tokenizer takes a vector as an argument, and 
            //pumps its tokens into that vector

            tokenizer->tokenizeLine(lineNumber,line,tokens);
        }

        //Here we just read off the result for testing

        for (int i = 0; i < tokens->size(); i++) {
            std::cout << tokens->at(i).lineNumber << ": " << tokens->at(i).string << std::endl;
        }
    }
    else {
        std::cout << "Bad file." << std::endl;
    }
}

