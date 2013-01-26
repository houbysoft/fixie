#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive.hpp>
#include <iostream>
#include "fixTokenizer.h"

#ifdef UNIT_TESTING
public main(int argc, char** argv) {
}
#endif

FixieTokenizer::FixieTokenizer(std::string input) {

    std::cout<<input<<std::endl;

    //Prints out a list of the tokens

    boost::xpressive::sregex re = boost::xpressive::sregex::compile("[0-9a-zA-Z]+");

    //Iterate over all the words in the input

    boost::xpressive::sregex_token_iterator begin( input.begin(), input.end(), re ), end;

    //Print out all the words
    
    std::ostream_iterator< std::string > out_iter( std::cout, "\n" );
    std::copy( begin, end, out_iter );
}


