#ifndef FIXIETOKENIZER_H
#define FIXIETOKENIZER_H

#include <string>


class FixieTokenizer {
    public:
        FixieTokenizer(std::string input);
        ~FixieTokenizer() {};
    
    private:
        std::string stripComments(std::string input);
};

#endif

