#include "fixieParser.h"
#define TESTING 1

/*
 * Basic empty constructor
 */
FixieParser::FixieParser() {
}

/*
 * Parses a string of tokens into a tree format
 */
void FixieParser::parse(std::vector<FixieTokenizer::token> *tokens) {
    std::vector<std::vector<FixieTokenizer::token> > *statements = statementList(tokens);

    #ifdef TESTING
        std::cout << std::endl << "STATEMENTS LIST:" << std::endl;
        for (int i = 0; i < statements->size(); i++) {
            std::vector<FixieTokenizer::token> statement = statements->at(i); 
            for (int s = 0; s < statement.size(); s++) {
                if (s == 0) {
                    if (statement.at(s).string == "int") {
                        std::cout << "INT DECLARATION: ";
                    }
                    if (statement.at(s).string == "string") {
                        std::cout << "STRING DECLARATION: ";
                    }
                    if (statement.at(s).string == "class") {
                        std::cout << "CLASS DECLARATION: ";
                    }
                    if (statement.at(s).string == "function") {
                        std::cout << "FUNCTION DECLARATION: ";
                    }
                }
                std::cout << statement.at(s).string << " ";
            }
            std::cout << std::endl;
        }
    #endif
}

/*
 * Groups the tokens into statements, eg function/class/variable/loop declaration, or variable assignment
 * Returns a vector of groups (each group is a vector of tokens)
 */
std::vector<std::vector<FixieTokenizer::token> > *FixieParser::statementList(std::vector<FixieTokenizer::token> *tokens) {

    //Set up our returned vector

    std::vector<std::vector<FixieTokenizer::token> > *statements = new std::vector<std::vector<FixieTokenizer::token> >();

    //Set up our current statement

    std::vector<FixieTokenizer::token> *statement = new std::vector<FixieTokenizer::token>();

    //Break up chunks when ';', '{' or '}' is encountered

    for (int i = 0; i < tokens->size(); i++) {
        statement->push_back(tokens->at(i));
        if (tokens->at(i).string == ";" || tokens->at(i).string == "{" || tokens->at(i).string == "}") {
            
            //We dereference our vector so it won't be a pointer in the vector of vectors we return

            statements->push_back(*statement);
            statement = new std::vector<FixieTokenizer::token>();
        }
    }

    return statements;
}


