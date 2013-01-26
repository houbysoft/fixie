#include <boost/algorithm/string.hpp>
#include "fixTokenizer.h"

#ifdef UNIT_TESTING
public main(int argc, char** argv) {
    
    //Unit test harness


}
#endif


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

