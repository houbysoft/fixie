#ifndef FIXIEPARSER_H
#define FIXIEPARSER_H

#include <string>
#include <vector>
#include <iostream>
#include "fixieTokenizer.h"

class FixieParser {
    public:
        FixieParser();
        ~FixieParser() {};
        void parse(std::vector<FixieTokenizer::token> *tokens);
    
    private:
        std::vector<std::vector<FixieTokenizer::token> > *statementList(std::vector<FixieTokenizer::token> *tokens);
};

#endif

