#pragma one
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <unistd.h>
#include <cmath>
#include <time.h>
#include <getopt.h>
#include <unordered_map>
#include <string>

using namespace std;

template <class T>
void HoanVi(T &a, T &b);
void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);