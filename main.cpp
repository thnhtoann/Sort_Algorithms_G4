#include "DataGenerator.h"
#include <getopt.h>
#include <iostream>
#include <cstring>
using namespace std;

// Prototype 1: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]
// Ex: a.exe -a radix-sort input.txt --both
// Prototype 2: [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
// Prototype 3: [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]
// Prototype 4: [Execution file] -c [Algorithm 1] [Algorithm 2] [Given input]
// Prototype 5: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]

int main(int argc, char *argv[]) {
    int opt;
    string mode;
    string algorithm1, algorithm2;
    string inputFile;
    int inputSize = 0;
    string inputOrder;
    string outputParam;

    // Define the long options
    static struct option long_options[] = {
        {"time", no_argument, 0, 't'},
        {"comp", no_argument, 0, 'p'},
        {"both", no_argument, 0, 'b'},
        {"rand", no_argument, 0, 'r'},
        {"nsorted", no_argument, 0, 'n'},
        {"sorted", no_argument, 0, 's'},
        {"rev", no_argument, 0, 'v'},
        {0, 0, 0, 0}
    };

    // Define the short options
    const char* short_options = "a:c:";

    // Parse the options
    while ((opt = getopt_long_only(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (opt) {
            case 'a':
                mode = "a";
                algorithm1 = optarg;
                break;
            case 'c':
                mode = "c";
                algorithm1 = optarg;
                if (optind < argc) {
                    algorithm2 = argv[optind++];
                }
                break;
            case 't':
                outputParam = "time";
                break;
            case 'p':
                outputParam = "comp";
                break;
            case 'b':
                outputParam = "both";
                break;
            case 'r':
                inputOrder = "rand";
                break;
            case 'n':
                inputOrder = "nsorted";
                break;
            case 's':
                inputOrder = "sorted";
                break;
            case 'v':
                inputOrder = "rev";
                break;
            default:
                cerr << "Usage: " << argv[0] << " -a [Algorithm] [Given input] [Output parameter(s)]" << endl;
                cerr << "       " << argv[0] << " -a [Algorithm] [Input size] [Input order] [Output parameter(s)]" << endl;
                cerr << "       " << argv[0] << " -a [Algorithm] [Input size] [Output parameter(s)]" << endl;
                cerr << "       " << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Given input]" << endl;
                cerr << "       " << argv[0] << " -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]" << endl;
                return 1;
        }
    }

    // Handle remaining arguments
    if (mode == "a") {
        if (optind < argc) {
            inputFile = argv[optind++];
        }
        if (optind < argc) {
            try {
                inputSize = stoi(argv[optind++]);
            } catch (invalid_argument& e) {
                inputOrder = argv[optind - 1];
            }
        }
        if (optind < argc) {
            inputOrder = argv[optind++];
        }
        if (optind < argc) {
            outputParam = argv[optind++];
        }
    } else if (mode == "c") {
        if (optind < argc) {
            inputFile = argv[optind++];
        }
        if (optind < argc) {
            try {
                inputSize = stoi(argv[optind++]);
            } catch (invalid_argument& e) {
                inputOrder = argv[optind - 1];
            }
        }
        if (optind < argc) {
            inputOrder = argv[optind++];
        }
    }

    // Print the parsed arguments
    cout << "Mode: " << mode << endl;
    cout << "Algorithm 1: " << algorithm1 << endl;
    if (!algorithm2.empty()) {
        cout << "Algorithm 2: " << algorithm2 << endl;
    }
    if (!inputFile.empty()) {
        cout << "Input File: " << inputFile << endl;
    }
    if (inputSize > 0) {
        cout << "Input Size: " << inputSize << endl;
    }
    if (!inputOrder.empty()) {
        cout << "Input Order: " << inputOrder << endl;
    }
    if (!outputParam.empty()) {
        cout << "Output Parameter: " << outputParam << endl;
    }

    return 0;
}