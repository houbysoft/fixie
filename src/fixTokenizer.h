#ifndef FIXIETOKENIZER_H
#define FIXIETOKENIZER_H

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <iostream>


class FixieTokenizer {
    public:
        FixieTokenizer(std::string input);
        ~FixieTokenizer() {};
    
    private:
        std::string stripComments(std::string input);
        std::vector<std::string> *tokenize(std::string input);
};

#endif

