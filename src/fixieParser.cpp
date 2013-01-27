#include "fixieParser.h"
#define TESTING 1

#define SCOPE_CLASS 0
#define SCOPE_FUNCTION 1

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
    std::vector<FixieParser::error> *errors = new std::vector<FixieParser::error>();
    scope *globalScope = buildScopes(statements,errors);
    #ifdef TESTING
        std::cout<<"first pass scoping:"<<std::endl;
       recursivelyDebugScope(globalScope,0); 
    #endif
}

void FixieParser::recursivelyDebugScope(FixieParser::scope *debugScope, int scopeLevel) {
    for (int p = 0; p < scopeLevel; p++) {
        std::cout << "   ";
    }
    std::cout << "SCOPE: " << debugScope->name << std::endl;
    for (int i = 0; i < debugScope->variables->size(); i++) {
        for (int p = 0; p < scopeLevel; p++) {
            std::cout << "   ";
        }
        std::cout << "-VAR: " << debugScope->variables->at(i)->name << std::endl;
    }
    for (int i = 0; i < debugScope->children->size(); i++) {
        recursivelyDebugScope(debugScope->children->at(i), scopeLevel+1);
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

    //Storing these lets us slowly knock statements out as they are processed in different passes
    //These get filled in buildScopes, and are whittled away at after that

    newScope->parameterStatement = new std::vector<FixieTokenizer::token>();
    newScope->statements = new std::vector<std::vector<FixieTokenizer::token> >();

    //These help us do type checking for everything

    newScope->variables = new std::vector<variable* >();
    newScope->parameters = new std::vector<variable* >();
    return newScope;
}

/*
 * Builds the scope tree from a list of statements
 */
FixieParser::scope *FixieParser::buildScopes(std::vector<std::vector<FixieTokenizer::token> > *statements, std::vector<FixieParser::error> *errors) {

    //Set up the global scope

    scope *globalScope = freshScope();
    globalScope->name = "GLOBAL";
    scope *currentScope = globalScope;

    //Loop through the statements

    for (int i = 0; i < statements->size(); i++) {
        std::vector<FixieTokenizer::token> statement = statements->at(i); 
        
        //Check the first word of the statement to see how we should respond

        if (statement.at(0).string == "class" || statement.at(0).string == "function") {

            //Basic scope declaration syntax check

            if (statement.size() < 5) {
                addError(errors,"Incomplete scope declaration",statement.at(0).lineNumber);
                continue;
            }

            //We'll create a new scope for classes and functions

            scope *newScope = freshScope();

            //Add name to our scope

            newScope->name = statement.at(1).string;

            //Check syntax

            if (statement.at(2).string != "(") {
                addError(errors,"Missing '(' in scope delcaration",statement.at(0).lineNumber);
            }

            //Read off parameters of our scope

            int readParameterStatement = 3;
            while (true) {
                if (readParameterStatement >= statement.size()) {
                    addError(errors,"Missing ')' in scope declaration",statement.at(0).lineNumber);
                    break;
                }
                if (statement.at(readParameterStatement).string == ")") break;
                newScope->parameterStatement->push_back(statement.at(readParameterStatement));
                readParameterStatement++;
            }

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
            
            //Add the statement to the scope's statement list to be processed in another pass

            currentScope->statements->push_back(statement);
        }
    }

    return globalScope;
}

void FixieParser::processVars(FixieParser::scope *globalScope, std::vector<FixieParser::error> *errors) {

}
