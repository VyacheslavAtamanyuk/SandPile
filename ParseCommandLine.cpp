#include "ParseCommandLine.h"

Arguments Parser(int argc, char** argv) {
    Arguments args;
    bool flag_for_input = false;
    bool flag_for_output = false;
    bool flag_for_max_iter = false;
    bool flag_for_freq = false;
    for (int i = 0; i < argc; ++i) {
        if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")) {
            args.input = argv[i+1];
            flag_for_input = true;
        }
        if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
            args.output = argv[i+1];
            flag_for_output = true;
        }
        if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--max-iter")) {
            char* end{};
            args.max_iter = strtol(argv[i+1], &end, 10);
            flag_for_max_iter = true;
        }
        if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--freq")) {
            char* end{};
            args.freq = strtol(argv[i+1],&end,10);
            flag_for_freq = true;
        }
    }
    if (!flag_for_freq || !flag_for_max_iter || !flag_for_input || !flag_for_output) {
        std::cerr << "Input data is incorrect!";
    }
    return args;
}