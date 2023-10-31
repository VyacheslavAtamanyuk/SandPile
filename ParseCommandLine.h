#ifndef LABWORK3_PARSER_H
#define LABWORK3_PARSER_H

#include <cstring>
#include <cstdlib>
#include <iostream>

struct Arguments {
    char* input;
    char* output;
    int max_iter;
    int freq;
};

Arguments Parser(int argc, char** argv);
#endif //LABWORK3_PARSER_H
