#pragma one
#include "DataGenerator.h"
using namespace std;

void bubbleSort(int a[], int n, long long& comparisons);

void shakerSort(int a[], int n, long long& comparisons);

void selectionSort(int a[], int n, long long& comparisons);

void insertionSort(int a[], int n, long long& comparisons);

int partition(int a[], int first, int last, long long& comparisons);
void quickSort(int a[], int first, int last, long long& comparisons);

void heapRebuild(int a[], int pos, int n, long long& comparisons);
void heapConstruct(int a[], int n, long long& comparisons);
void heapSort(int a[], int n, long long& comparisons);

void merge(int a[], int first, int mid, int last, long long& comparisons);
void mergeSort(int a[], int first, int last, long long& comparisons);

void shellSort(int a[], int n, long long& comparisons);

int binarySearch(int a[], int first, int item, int last, long long& comparisons);
void binaryInsertionSort(int a[], int n, long long& comparisons);

void countingSort(int a[], int n, long long& comparisons);

void radixSort(int a[], int n, long long& comparisons);

void flashSort(int a[], int n, long long& comparisons);