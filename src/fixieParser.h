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

        /*
         * Scopes are the basic object in our parse trees. There's the global scope,
         * which will have children for global function and class scopes.
         */
        typedef struct {

            //Scopes need to know where they sit in the scope tree, so they can
            //search for variables in their parents if they don't find them in this
            //scope

            scope *parent;
            std::vector<scope *> children;

            //Variables that have been set in this scope

            std::vector<variable *> variables;
        } scope;
    
    private:
        std::vector<std::vector<FixieTokenizer::token> > *statementList(std::vector<FixieTokenizer::token> *tokens);
};

#endif

