#include "DataGenerator.h"
#include <iostream>
using namespace std;

void bubbleSort(int a[], int n, long long& comparisons) {
    for (int i = n - 1; i >= 0; i--) {
        comparisons++;   
        bool swapped = false;
        for (int j = 0; j < i; j++) {
            comparisons++;   
            comparisons++;   
            if (a[j] > a[j + 1]) {
                swapped = true;
                HoanVi(a[j], a[j + 1]);
            }
        }
        comparisons++;   
        if (!swapped)
            return;
    }
}

void shakerSort(int a[], int n, long long& comparisons) {
    int left = 0;
    int right = n - 1;
    int k = 0;
    while (left <= right) {
        comparisons++;  
        bool swapped = false;
        for (int j = left; j < right; j++) {
            comparisons++;   
            comparisons++;   
            if (a[j] > a[j + 1]) {
                swapped = true;
                HoanVi(a[j], a[j + 1]);
                k = j;
            }
        }
        comparisons++;   
        if (!swapped)
            return;
        right = k;
        swapped = false;
        for (int j = right; j > left; j--) {
            comparisons++;   
            comparisons++;   
            if (a[j] < a[j - 1]) {
                swapped = true;
                HoanVi(a[j], a[j - 1]);
                k = j;
            }
        }
        comparisons++;   
        if (!swapped)
            return;
        left = k;
    }
}

void selectionSort(int a[], int n, long long& comparisons) {
    for (int i = 0; i < n; i++) {
        comparisons++;   
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;   
            comparisons++;   
            if (a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        HoanVi(a[i], a[minIndex]);
    }
}

void insertionSort(int a[], int n, long long& comparisons) {
    for (int i = 1; i < n; i++) {
        comparisons++;   
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;  
            comparisons++;   
            if (a[j] > key) {
                a[j + 1] = a[j];
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
}

int partition(int a[], int first, int last, long long& comparisons) {
    int pivot = a[(first + last) / 2];
    int i = first;
    int j = last;
    while (i <= j) {
        comparisons++;  
        while (a[i] < pivot) {
            comparisons++;  
            i++;
        }
        while (a[j] > pivot) {
            comparisons++;  
            j--;
        }
        comparisons++;   
        if (i <= j) {
            HoanVi(a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(int a[], int first, int last, long long& comparisons) {
    int index = partition(a, first, last, comparisons);
    comparisons++;   
    if (first < index - 1)
        quickSort(a, first, index - 1, comparisons);
    comparisons++;   
    if (index < last)
        quickSort(a, index, last, comparisons);
}

void heapRebuild(int a[], int pos, int n, long long& comparisons) {
    while (2 * pos + 1 < n) {
        comparisons++;  
        int j = 2 * pos + 1;
        comparisons++;   
        if (j < n - 1) {
            comparisons++;   
            if (a[j] < a[j + 1])
                j++;
        }
        comparisons++;   
        if (a[pos] >= a[j])
            return;
        HoanVi(a[pos], a[j]);
        pos = j;
    }
}

void heapConstruct(int a[], int n, long long& comparisons) {
    for (int i = (n - 1) / 2; i >= 0; i--) {
        comparisons++;   
        heapRebuild(a, i, n, comparisons);
    }
}

void heapSort(int a[], int n, long long& comparisons) {
    heapConstruct(a, n, comparisons);
    int r = n - 1;
    while (r > 0) {
        comparisons++;  
        HoanVi(a[0], a[r]);
        heapRebuild(a, 0, r, comparisons);
        r--;
    }
}

void merge(int a[], int first, int mid, int last, long long& comparisons) {
    int n1 = mid - first + 1;
    int n2 = last - mid;
    int *L = new int[n1];
    int *R = new int[n2];
    for (int i = 0; i < n1; i++) {
        comparisons++;   
        L[i] = a[first + i];
    }
    for (int j = 0; j < n2; j++) {
        comparisons++;   
        R[j] = a[mid + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = first;
    while (i < n1 && j < n2) {
        comparisons += 2;  
        comparisons++;   
        if (L[i] < R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (j < n2) {
        comparisons++;  
        a[k++] = R[j++];
    }
    while (i < n1) {
        comparisons++;  
        a[k++] = L[i++];
    }
    delete[] L;
    delete[] R;
}

void mergeSort(int a[], int first, int last, long long& comparisons) {
    comparisons++;   
    if (first < last) {
        int mid = first + (last - first) / 2;
        mergeSort(a, first, mid, comparisons);
        mergeSort(a, mid + 1, last, comparisons);
        merge(a, first, mid, last, comparisons);
    }
}

void shellSort(int a[], int n, long long& comparisons) {
    for (int interval = n / 2; interval > 0; interval /= 2) {
        comparisons++;   
        for (int i = interval; i < n; i++) {
            comparisons++;   
            int temp = a[i];
            int j = i;
            while (j >= interval) {
                comparisons++;  
                comparisons++;   
                if (a[j - interval] > temp) {
                    a[j] = a[j - interval];
                    j -= interval;
                } else {
                    break;
                }
            }
            a[j] = temp;
        }
    }
}

int binarySearch(int a[], int first, int item, int last, long long& comparisons) {
    while (true) {
        comparisons++;   
        if (first >= last) {
            comparisons++;   
            return (a[first] > item) ? first : first + 1;
        }
        int mid = (first + last) / 2;
        comparisons++;   
        if (a[mid] == item)
            return mid + 1;
        comparisons++;   
        if (a[mid] < item)
            first = mid + 1;
        else
            last = mid - 1;
    }
}

void binaryInsertionSort(int a[], int n, long long& comparisons) {
    int i, loc, j, k, selected;
    for (i = 1; i < n; ++i) {
        comparisons++;   
        j = i - 1;
        selected = a[i];
        loc = binarySearch(a, 0, selected, j, comparisons);
        while (j >= loc) {
            comparisons++;  
            a[j + 1] = a[j];
            j--;
        }
        a[loc] = selected;
    }
}

void countingSort(int a[], int n, long long& comparisons) {
    int max = a[0];
    for (int i = 1; i < n; i++) {
        comparisons++;   
        comparisons++;   
        if (a[i] > max)
            max = a[i];
    }

    int *count = new int[max + 1];
    for (int i = 0; i <= max; i++) {
        comparisons++;   
        count[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        comparisons++;   
        count[a[i]]++;
    }

    for (int i = 1; i <= max; i++) {
        comparisons++;   
        count[i] += count[i - 1];
    }

    int *temp = new int[n];
    for (int i = 0; i < n; i++) {
        comparisons++;   
        temp[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }

    for (int i = 0; i < n; i++) {
        comparisons++;   
        a[i] = temp[i];
    }
    delete[] count;
    delete[] temp;
}

void radixSort(int a[], int n, long long& comparisons) {
    int *b = new int[n];
    int m = a[0], exp = 1;

    for (int i = 0; i < n; i++) {
        comparisons++;   
        comparisons++;   
        if (a[i] > m)
            m = a[i];
    }

    while (m / exp > 0) {
        comparisons++;  
        int bucket[10] = { 0 };
        for (int i = 0; i < n; i++) {
            comparisons++;   
            bucket[a[i] / exp % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            comparisons++;   
            bucket[i] += bucket[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) {
            comparisons++;   
            b[--bucket[a[i] / exp % 10]] = a[i];
        }
        for (int i = 0; i < n; i++) {
            comparisons++;   
            a[i] = b[i];
        }
        exp *= 10;
    }
    delete[] b;
}

void flashSort(int a[], int n, long long& comparisons) {
    int minVal = a[0];
    int max = 0;
    int m = int(0.45 * n);
    int* l = new int[m];
    for (int i = 0; i < m; i++) {
        comparisons++;   
        l[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        comparisons++;   
        comparisons++;   
        if (a[i] < minVal)
            minVal = a[i];
        comparisons++;   
        if (a[i] > a[max])
            max = i;
    }
    comparisons++;   
    if (a[max] == minVal)
        return;
    double c1 = (double)(m - 1) / (a[max] - minVal);
    for (int i = 0; i < n; i++) {
        comparisons++;   
        int k = int(c1 * (a[i] - minVal));
        ++l[k];
    }
    for (int i = 1; i < m; i++) {
        comparisons++;   
        l[i] += l[i - 1];
    }
    HoanVi(a[max], a[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (nmove < n - 1) {
        comparisons++;  
        while (j > l[k] - 1) {
            comparisons++; 
            j++;
            k = int(c1*(a[j] - minVal));
        }
        flash = a[j];
        comparisons++; 
        if (k < 0) break;
        while (j != l[k]) {
            comparisons++; 
            k = int(c1*(flash - minVal));
            int hold = a[t = --l[k]];
            a[t] = flash;
            flash = hold;
            ++nmove;
        }
    }
    delete[] l;
    insertionSort(a, n, comparisons);
}