#include <iostream>
#include <vector>
#include "ArgManager.h"


int main(int argc, char *argv[]) {
    cse::ArgManager args(argc, argv);  // Pass input args into manager for processing.
    if (args.Has("-h") || args.Has("--help")) {
        args.PrintHelp();
        exit(0);
    }
    // Set a default output filename, then Test if one was specified in the
    // command line arguments sent in.
    std::string out_filename="default_output.dat";
    if (args.Has("-o")) out_filename = args.GetOption("-o");
}

