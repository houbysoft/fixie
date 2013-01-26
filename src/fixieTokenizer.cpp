#include "fixieTokenizer.h"

#ifdef UNIT_TESTING
public main(int argc, char** argv) {
}
#endif

/*
 * Basic empty constructor
 */
FixieTokenizer::FixieTokenizer() {
}

/*
 * Tokenize takes a line number and an input string to tokenize. Will return
 * a vector of tokens with this line number noted in their values.
 */
void FixieTokenizer::tokenize(int lineNumber, std::string input, std::vector<FixieTokenizer::token> *tokenized) {
    std::vector<std::string> *chunked = chunk(stripComments(input));
    for (int i = 0; i < chunked->size(); i++) {
        FixieTokenizer::token token;
        token.string = chunked->at(i);
        token.lineNumber = lineNumber;
        tokenized->push_back(token);
    }
}

/*
 * Clears out all the comments from a code input
 */
std::string FixieTokenizer::stripComments(std::string input) {
    int mode = 0;
    // can be either 0 (no comments in progress), 1 (inside // comment, waiting for newline), 2 (inside /* */ comment, wait for */)

    std::string res;
    for (int i = 0; i < input.size(); i++) {
        if (mode == 0) {
            if (input[i] == '/' && i+1 < input.size() && input[i+1] == '/') {
                mode = 1;
                i++;
                continue;
            }
        
            if (input[i] == '/' && i+1 < input.size() && input[i+1] == '*') {
                mode = 2;
                i++;
                continue;
            }

            res += input[i];
        
        } else if (mode == 1) {
            if (input[i] == '\n') {
                mode = 0;
            }
        } else if (mode == 2) {
            if (input[i] == '*' && i+1 < input.size() && input[i+1] == '/') {
                mode = 0;
                i++;
            }
        }
    }

    return res;
}

/*
 * Tokenizes the code, assumed to have been cleaned of all comments
 */
std::vector<std::string> *FixieTokenizer::chunk(std::string input) {
    std::vector<std::string> *result = new std::vector<std::string>();
    boost::xpressive::sregex re = boost::xpressive::sregex::compile("[0-9a-zA-Z]+|\"|\'|;|=|\\*|\\.|\\||\\|\\||&&|\\(|\\)|\\[|\\]|\\+|-|\\\\|\\/|\\*|\\?|\\$|\\^");

    //Iterate over all the words in the input

    boost::xpressive::sregex_token_iterator begin( input.begin(), input.end(), re ), end;

    for (; begin != end; ++begin) {
        result->push_back(*begin);
    }

    return result;
}

