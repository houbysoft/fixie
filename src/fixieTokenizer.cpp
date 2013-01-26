#include "fixieTokenizer.h"

#ifdef UNIT_TESTING
public main(int argc, char** argv) {
}
#endif

#define NO_COMMENTS_IN_PROGRESS 0
#define WAITING_FOR_NEWLINE 1
#define INSIDE_MULTILINE_COMMENT 2

/*
 * Basic empty constructor
 */
FixieTokenizer::FixieTokenizer() {

    //set up our comment state so that it can be persistent
    //across multiple calls to tokenizeLine, so that a '/*'
    //that we read in one line will continue to effect the
    //next line read.

    commentState = NO_COMMENTS_IN_PROGRESS;
}

/*
 * Tokenize a file, and return a vector of tokens
 */
std::vector<FixieTokenizer::token> *FixieTokenizer::tokenize(std::ifstream *file) {
    std::vector<FixieTokenizer::token> *tokens = new std::vector<FixieTokenizer::token>();
    std::string line;
    int lineNumber = 0;

    //Read off the lines into the tokenizer

    while (file->good()) {
        lineNumber++;
        getline(*file,line);

        //The tokenizer takes a vector as an argument, and 
        //pumps its tokens into that vector

        tokenizeLine(lineNumber,line,tokens);
    }

    return tokens;
}

/*
 * Tokenize takes a line number and an input string to tokenize. Will return
 * a vector of tokens with this line number noted in their values.
 */
void FixieTokenizer::tokenizeLine(int lineNumber, std::string input, std::vector<FixieTokenizer::token> *tokenized) {

    //Gets the chunks of the string

    std::vector<std::string> *chunked = chunk(stripComments(input));

    //Drops in the line number with the chunks for error reporting

    for (int i = 0; i < chunked->size(); i++) {
        FixieTokenizer::token token;
        token.string = chunked->at(i);
        token.lineNumber = lineNumber;

        //Pushes the result into the tokenized array that gets passed in

        tokenized->push_back(token);
    }
}

/*
 * Clears out all the comments from a code input
 */
std::string FixieTokenizer::stripComments(std::string input) {

    // If we were waiting for a newline last line chunk, we're done waiting

    if (commentState == WAITING_FOR_NEWLINE) commentState = NO_COMMENTS_IN_PROGRESS;

    // Simple finite state machine for clearing out comments

    std::string res;
    for (int i = 0; i < input.size(); i++) {

        // If no comments are in progress, wait for something to trigger a jump

        if (commentState == NO_COMMENTS_IN_PROGRESS) {
            if (input[i] == '/' && i+1 < input.size() && input[i+1] == '/') {
                commentState = WAITING_FOR_NEWLINE;
                i++;
                continue;
            }
        
            if (input[i] == '/' && i+1 < input.size() && input[i+1] == '*') {
                commentState = INSIDE_MULTILINE_COMMENT;
                i++;
                continue;
            }

            res += input[i];
        
        } 

        // If we've encountered a '//' comment, wait for a newline
        
        else if (commentState == WAITING_FOR_NEWLINE) {
            if (input[i] == '\n') {
                commentState = NO_COMMENTS_IN_PROGRESS;
            }
        } 
        
        // If we've encountered a '/**/' comment, wait for the '*/'

        else if (commentState == INSIDE_MULTILINE_COMMENT) {
            if (input[i] == '*' && i+1 < input.size() && input[i+1] == '/') {
                commentState = NO_COMMENTS_IN_PROGRESS;
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

    //Create the vector to hold the result

    std::vector<std::string> *result = new std::vector<std::string>();

    //Build our massive regex to catch strings of letters and numbers, and all those
    //important other symbols.
    /*
     
       Here's the list of characters we match so far:

        " ' ; = * . , || && ( ) [ ] { } + - \ / ? $ ~

     */

    boost::xpressive::sregex re = boost::xpressive::sregex::compile("[0-9a-zA-Z]+|\"|\'|;|=|\\*|\\.|,|\\|\\||&&|\\(|\\)|\\[|\\]|{|}|\\+|-|\\\\|\\/|\\*|\\?|\\$|\\^");

    //Iterate over all the matches in the input

    boost::xpressive::sregex_token_iterator begin( input.begin(), input.end(), re ), end;

    //Spit the chunks into our vector

    for (; begin != end; ++begin) {
        result->push_back(*begin);
    }

    return result;
}

#undef NO_COMMENTS_IN_PROGRESS
#undef WAITING_FOR_NEWLINE
#undef INSIDE_MULTILINE_COMMENT
