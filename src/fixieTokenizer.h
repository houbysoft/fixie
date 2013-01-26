#ifndef FIXIETOKENIZER_H
#define FIXIETOKENIZER_H

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <iostream>


class FixieTokenizer {
    public:
        FixieTokenizer();
        ~FixieTokenizer() {};

        typedef struct {
            std::string string;
            int lineNumber;
        } token;

        void tokenize(int lineNumber, std::string input, std::vector<token> *tokenized);
    
    private:
        std::string stripComments(std::string input);
        std::vector<std::string> *chunk(std::string input);
};

#endif

