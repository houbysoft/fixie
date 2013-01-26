#ifndef FIXIETOKENIZER_H
#define FIXIETOKENIZER_H

#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <iostream>
#include <fstream>


class FixieTokenizer {
    public:
        FixieTokenizer();
        ~FixieTokenizer() {};

        //We bundle lineNumber and string together in token to allow clear debug messages

        typedef struct {
            std::string string;
            int lineNumber;
        } token;

        // tokenizes a whole file, and spits out the result
        
        std::vector<token> *tokenize(std::ifstream *file);
    
    private:
       
        // tokenizes a single line at a time, but maintains comment state across multiple
        // lines, ie if '/*' was found on one line, all other text is ignored until '*/'
        
        void tokenizeLine(int lineNumber, std::string input, std::vector<token> *tokenized);
        
        // strips the comments from a line of a file, with memory of the last line that was
        // stripped of comments

        std::string stripComments(std::string input);

        // feeds a commentless string through a regex to chunk it out

        std::vector<std::string> *chunk(std::string input);
        
        //Allows multiline comment persistence across multiple calls to tokenizeLine

        int commentState;
};

#endif

