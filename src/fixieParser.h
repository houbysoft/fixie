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
         * Variable struct for declared variables
         */
        typedef struct variable {
            std::string name;
            int type;
        } variable;

        /*
         * Scopes are the basic object in our parse trees. There's the global scope,
         * which will have children for global function and class scopes.
         */
        typedef struct scope {

            //Scopes need to know where they sit in the scope tree, so they can
            //search for variables in their parents if they don't find them in this
            //scope

            struct scope *parent;
            std::vector<struct scope *> *children;

            //Variables that have been set in this scope

            std::vector<variable *> *variables;

            //Define scope type

            int scopeType;

            //Scope name

            std::string name;
        } scope;

        /*
         * Struct for holding the errors that we generate
         */
        typedef struct error {
            std::string message;
            int lineNumber;
        } error;
    
    private:
        /*
         * Breaks up the input string into a list of statements
         */
        std::vector<std::vector<FixieTokenizer::token> > *statementList(std::vector<FixieTokenizer::token> *tokens);

        /*
         * Returns the global scope, with pointers to all the other scopes
         */
        scope *buildScope(std::vector<std::vector<FixieTokenizer::token> > *statements);

        /*
         * Adds an error to our error message list
         */
        void addError(std::vector<error> *errors, std::string message, int lineNumber);

        /*
         * Debugs all the data in our scope tree
         */
        void recursivelyDebugScope(scope *debugScope);

        /*
         * Helper function to properly initialize a new scope
         */
        scope *freshScope();
};

#endif

