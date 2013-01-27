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
    scope *globalScope = buildScope(statements);
    #ifdef TESTING
       recursivelyDebugScope(globalScope); 
    #endif
}

void FixieParser::recursivelyDebugScope(FixieParser::scope *debugScope) {
    std::cout << "SCOPE: " << debugScope->name << std::endl;
    for (int i = 0; i < debugScope->variables->size(); i++) {
        std::cout << "VAR: " << debugScope->variables->at(i)->name << std::endl;
    }
    for (int i = 0; i < debugScope->children->size(); i++) {
        recursivelyDebugScope(debugScope->children->at(i));
    }
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

/*
 * Adds an error to our error list
 */
void FixieParser::addError(std::vector<FixieParser::error> *errors, std::string message, int lineNumber) {
    error *newError = new error;
    newError->message = message;
    newError->lineNumber = lineNumber;
}

/*
 * Creates a fresh scope, properly initialized
 */
FixieParser::scope *FixieParser::freshScope() {
    scope *newScope = new scope;
    newScope->children = new std::vector<scope* >();
    newScope->variables = new std::vector<variable* >();
    return newScope;
}

/*
 * Builds the scope tree from a list of statements
 */
FixieParser::scope *FixieParser::buildScope(std::vector<std::vector<FixieTokenizer::token> > *statements) {

    //Set up an array to hold errors

    std::vector<error> *errors = new std::vector<error>;

    //Set up the global scope

    scope *globalScope = freshScope();
    scope *currentScope = globalScope;

    //Debug scope level

    int scopeLevel = 0;

    //Loop through the statements

    for (int i = 0; i < statements->size(); i++) {
        std::vector<FixieTokenizer::token> statement = statements->at(i); 
        
        //Check the first word of the statement to see how we should respond

        if (statement.at(0).string == "class" || statement.at(0).string == "function") {

            //Basic class declaration syntax check

            if (statement.size() < 3) {
                addError(errors,"Incomplete Scope Declaration",statement.at(0).lineNumber);
            }

            //We'll create a new scope for classes and functions

            scope *newScope = freshScope();

            //Add name to our scope

            newScope->name = statement.at(1).string;

            //Insert it in the scope trie

            newScope->parent = currentScope;
            currentScope->children->push_back(newScope);
            currentScope = newScope;
        }
        else if (statement.at(0).string == "}") {

            //Backtrack up the scoping hierarchy

            currentScope = currentScope->parent;
        }
        else {
            
            //Check if we've encountered a variable declaration
            
            if (statement.at(0).string == "int" || statement.at(0).string == "string") {
                variable *newVariable = new variable;
                newVariable->name = statement.at(1).string;
                currentScope->variables->push_back(newVariable);
            }
        }
    }

    return globalScope;
}
