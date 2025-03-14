#include "DataGenerator.h"
#include "Sort.h"
#include <getopt.h>
#include <iostream>
#include <cstring>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

int* readInput(string filename, int &size) {
    ifstream file(filename);
    if (!file) {
        exit(1);
    }
    file >> size;
    int *arr = new int [size];
    int i = 0;
    while(file >> arr[i++]){
    }
    file.close();
    return arr;
}

void callSortFunction(const string& algorithm, int arr[], int size, long long& comparisons) {
    if (algorithm == "bubble-sort") {
        bubbleSort(arr, size, comparisons);
    } else if (algorithm == "shaker-sort") {
        shakerSort(arr, size, comparisons);
    } else if (algorithm == "selection-sort") {
        selectionSort(arr, size, comparisons);
    } else if (algorithm == "insertion-sort") {
        insertionSort(arr, size, comparisons);
    } else if (algorithm == "heap-sort") {
        heapSort(arr, size, comparisons);
    } else if (algorithm == "shell-sort") {
        shellSort(arr, size, comparisons);
    } else if (algorithm == "binary-insertion-sort") {
        binaryInsertionSort(arr, size, comparisons);
    } else if (algorithm == "counting-sort") {
        countingSort(arr, size, comparisons);
    } else if (algorithm == "radix-sort") {
        radixSort(arr, size, comparisons);
    } else if (algorithm == "flash-sort") {
        flashSort(arr, size, comparisons);
    } else if (algorithm == "quick-sort") {
        quickSort(arr, 0, size - 1, comparisons);
    } else if (algorithm == "merge-sort") {
        mergeSort(arr, 0, size - 1, comparisons);
    } 
    else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        exit(1);
    }
}

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
            
        }
    }

    // Handle remaining arguments
    if (mode == "a") {
        if (optind < argc) {
            try {
                inputSize = stoi(argv[optind++]);
            } catch (invalid_argument& e) {
                inputFile = argv[optind - 1];
                optind++;
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
            try {
                inputSize = stoi(argv[optind++]);
            } catch (invalid_argument& e) {
                inputFile = argv[optind - 1];
            }
        }
        if (optind < argc) {
            inputOrder = argv[optind++];
        }
    }

    // Example usage of the sort function map
    if (mode == "a") {
        long long comparisons = 0;
        int* arr = nullptr;
        cout << "ALGORITHM MODE\n";
        cout << "Algorithm: " << algorithm1 << '\n';
        if (!inputFile.empty()) {
            arr = readInput(inputFile, inputSize);
            cout << "Input file: " << inputFile << '\n';
            cout << "Input size: " << inputSize << '\n';
            auto start = high_resolution_clock::now();
            callSortFunction(algorithm1, arr, inputSize, comparisons);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);
           
            if (outputParam == "time") {
                cout << "Running time: " << duration.count() << " milliseconds\n";
            } else if (outputParam == "comp") {
                cout << "Comparisons: " << comparisons << '\n';
            } else if (outputParam == "both") {
                cout << "Running time: " << duration.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons << '\n';
            }
            delete[] arr;
        } else if (inputOrder.empty()) {
            int* arrRand = new int[inputSize];
            int* arrSorted = new int[inputSize];
            int* arrRev = new int[inputSize];
            int* arrNearlySorted = new int[inputSize];
            GenerateRandomData(arrRand, inputSize);
            GenerateSortedData(arrSorted, inputSize);
            GenerateReverseData(arrRev, inputSize);
            GenerateNearlySortedData(arrNearlySorted, inputSize);

            cout << "Input size: " << inputSize << '\n' << '\n';
          
            if (outputParam == "both") {
                cout << "Input order: Randomize\n";
                comparisons = 0;
                auto start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrRand, inputSize, comparisons);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons << '\n' << '\n';

                comparisons = 0;
                cout << "Input order: Nearly Sorted\n";
                start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrNearlySorted, inputSize, comparisons);
                stop = high_resolution_clock::now();
                duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons << '\n' << '\n';

                comparisons = 0;
                cout << "Input order: Sorted\n";
                start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrSorted, inputSize, comparisons);
                stop = high_resolution_clock::now();
                duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons << '\n' << '\n';

                comparisons = 0;
                cout << "Input order: Reverse\n";
                start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrRev, inputSize, comparisons);
                stop = high_resolution_clock::now();
                duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons << '\n';
            } else if (outputParam == "time") {
                cout << "Input order: Randomize\n";
                comparisons = 0;
                auto start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrRand, inputSize, comparisons);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n" << '\n';

                cout << "Input order: Nearly Sorted\n";
                comparisons = 0;
                start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrNearlySorted, inputSize, comparisons);
                stop = high_resolution_clock::now();
                duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n" << '\n';

                cout << "Input order: Sorted\n";
                comparisons = 0;
                start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrSorted, inputSize, comparisons);
                stop = high_resolution_clock::now();
                duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n" << '\n';

                cout << "Input order: Reverse\n";
                comparisons = 0;
                start = high_resolution_clock::now();
                callSortFunction(algorithm1, arrRev, inputSize, comparisons);
                stop = high_resolution_clock::now();
                duration = duration_cast<milliseconds>(stop - start);
                cout << "Running time: " << duration.count() << " milliseconds\n";
            } else if (outputParam == "comp") {
                cout << "Input order: Randomize\n";
                comparisons = 0;
                callSortFunction(algorithm1, arrRand, inputSize, comparisons);
                cout << "Comparisons: " << comparisons << '\n' << '\n';

                comparisons = 0;
                cout << "Input order: Nearly Sorted\n";
                callSortFunction(algorithm1, arrNearlySorted, inputSize, comparisons);
                cout << "Comparisons: " << comparisons << '\n' << '\n';

                comparisons = 0;
                cout << "Input order: Sorted\n";
                callSortFunction(algorithm1, arrSorted, inputSize, comparisons);
                cout << "Comparisons: " << comparisons << '\n' << '\n';

                comparisons = 0;
                cout << "Input order: Reverse\n";
                callSortFunction(algorithm1, arrRev, inputSize, comparisons);
                cout << "Comparisons: " << comparisons << '\n';
            }

            delete[] arrRand;
            delete[] arrSorted;
            delete[] arrRev;
            delete[] arrNearlySorted;
        } else {
            cout << "Input size: " << inputSize << '\n';
            cout << "Input order: " << inputOrder << '\n';
            cout << '\n';
            int* arr = new int[inputSize];
            if (inputOrder == "rand") {
                GenerateRandomData(arr, inputSize);
                if(outputParam == "both"){
                    cout << "Input order: Randomize\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                    cout << "Comparisons: " << comparisons << '\n';
                }
                if(outputParam == "time"){
                    cout << "Input order: Randomize\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                }
                if(outputParam == "comp"){
                    cout << "Input order: Randomize\n";
                    comparisons = 0;
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    cout << "Comparisons: " << comparisons << '\n';
                }

            } else if (inputOrder == "nsorted") {
                GenerateNearlySortedData(arr, inputSize);
                if(outputParam == "both"){
                    cout << "Input order: Nearly Sorted\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                    cout << "Comparisons: " << comparisons << '\n';
                }
                if(outputParam == "time"){
                    cout << "Input order: Nearly Sorted\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                }
                if(outputParam == "comp"){
                    cout << "Input order: Nearly Sorted\n";
                    comparisons = 0;
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    cout << "Comparisons: " << comparisons << '\n';
                }
            } else if (inputOrder == "sorted") {
                GenerateSortedData(arr, inputSize);
                if(outputParam == "both"){
                    cout << "Input order: Sorted\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                    cout << "Comparisons: " << comparisons << '\n';
                }
                if(outputParam == "time"){
                    cout << "Input order: Sorted\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                }
                if(outputParam == "comp"){
                    cout << "Input order: Sorted\n";
                    comparisons = 0;
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    cout << "Comparisons: " << comparisons << '\n';
                }
            } else if (inputOrder == "rev") {
                GenerateReverseData(arr, inputSize);
                if(outputParam == "both"){
                    cout << "Input order: Reverse\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                    cout << "Comparisons: " << comparisons << '\n';
                }
                if(outputParam == "time"){
                    cout << "Input order: Reverse\n";
                    comparisons = 0;
                    auto start = high_resolution_clock::now();
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(stop - start);
                    cout << "Running time: " << duration.count() << " milliseconds\n";
                }
                if(outputParam == "comp"){
                    cout << "Input order: Reverse\n";
                    comparisons = 0;
                    callSortFunction(algorithm1, arr, inputSize, comparisons);
                    cout << "Comparisons: " << comparisons << '\n';
                }

            }
            delete[] arr;
        }

    }
    if(mode == "c"){
        long long comparisons1 = 0;
        long long comparisons2 = 0;
        cout << inputFile << '\n';
        cout << "COMPARE MODE\n";
        cout << "Algorithm : " << algorithm1 <<" | " << algorithm2 << '\n';
        if (!inputFile.empty()) {
            int* arr = nullptr;
            arr = readInput(inputFile, inputSize);
            cout << "Input file: " << inputFile << '\n';
            cout << "Input size: " << inputSize << '\n';
            cout << '\n';
            auto start = high_resolution_clock::now();
            callSortFunction(algorithm1, arr, inputSize, comparisons1);
            auto stop = high_resolution_clock::now();
            auto duration1 = duration_cast<milliseconds>(stop - start);
            start = high_resolution_clock::now();
            callSortFunction(algorithm2, arr, inputSize, comparisons2);
            stop = high_resolution_clock::now();
            auto duration2 = duration_cast<milliseconds>(stop - start);
            cout << "Running time: "  << duration1.count() << " milliseconds" << " | " << duration2.count() << " milliseconds\n";
            cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << '\n';
            delete[] arr;
        } else {
            cout << "Input size: " << inputSize << '\n';
            cout << "Input order: " << inputOrder << '\n';
            cout << '\n';
            int* arr1 = new int[inputSize];
            int* arr2 = new int[inputSize];
            if(inputOrder== "rand"){
                GenerateRandomData(arr1, inputSize);
                GenerateRandomData(arr2, inputSize);
                auto start = high_resolution_clock::now();
                callSortFunction(algorithm1, arr1, inputSize, comparisons1);
                auto stop = high_resolution_clock::now();
                auto duration1 = duration_cast<milliseconds>(stop - start);
                start = high_resolution_clock::now();
                callSortFunction(algorithm2, arr2, inputSize, comparisons2);
                stop = high_resolution_clock::now();
                auto duration2 = duration_cast<milliseconds>(stop - start);
                cout << "Input order: Randomize\n";
                cout << "Running time: "  << duration1.count() << " milliseconds" << " | " << duration2.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << '\n';
            }
            if(inputOrder== "nsorted"){
                GenerateNearlySortedData(arr1, inputSize);
                GenerateNearlySortedData(arr2, inputSize);
                auto start = high_resolution_clock::now();
                callSortFunction(algorithm1, arr1, inputSize, comparisons1);
                auto stop = high_resolution_clock::now();
                auto duration1 = duration_cast<milliseconds>(stop - start);
                start = high_resolution_clock::now();
                callSortFunction(algorithm2, arr2, inputSize, comparisons2);
                stop = high_resolution_clock::now();
                auto duration2 = duration_cast<milliseconds>(stop - start);
                cout << "Input order: Nearly Sorted\n";
                cout << "Running time: "  << duration1.count() << " milliseconds" << " | " << duration2.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << '\n';
            }
            if(inputOrder== "sorted"){
                GenerateSortedData(arr1, inputSize);
                GenerateSortedData(arr2, inputSize);
                auto start = high_resolution_clock::now();
                callSortFunction(algorithm1, arr1, inputSize, comparisons1);
                auto stop = high_resolution_clock::now();
                auto duration1 = duration_cast<milliseconds>(stop - start);
                start = high_resolution_clock::now();
                callSortFunction(algorithm2, arr2, inputSize, comparisons2);
                stop = high_resolution_clock::now();
                auto duration2 = duration_cast<milliseconds>(stop - start);
                cout << "Input order: Sorted\n";
                cout << "Running time: "  << duration1.count() << " milliseconds" << " | " << duration2.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << '\n';
            }
            if(inputOrder== "rev"){
                GenerateReverseData(arr1, inputSize);
                GenerateReverseData(arr2, inputSize);
                auto start = high_resolution_clock::now();
                callSortFunction(algorithm1, arr1, inputSize, comparisons1);
                auto stop = high_resolution_clock::now();
                auto duration1 = duration_cast<milliseconds>(stop - start);
                start = high_resolution_clock::now();
                callSortFunction(algorithm2, arr2, inputSize, comparisons2);
                stop = high_resolution_clock::now();
                auto duration2 = duration_cast<milliseconds>(stop - start);
                cout << "Input order: Reverse\n";
                cout << "Running time: "  << duration1.count() << " milliseconds" << " | " << duration2.count() << " milliseconds\n";
                cout << "Comparisons: " << comparisons1 << " | " << comparisons2 << '\n';
            }
            delete[] arr1;
            delete[] arr2;


        }
    }
    return 0;
}