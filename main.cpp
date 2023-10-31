#include "ParseCommandLine.h"
#include "SandPile.h"

int main(int argc, char** argv) {
    Arguments args;
    args = Parser(argc, argv);
    SandPile(args);
}