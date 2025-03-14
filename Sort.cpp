#include "DataGenerator.h"
#include <iostream>
using namespace std;

void bubbleSort(int a[], int n, long long& comparisons) {
    for (int i = n - 1; ++comparisons, i >= 0; i--) {
        bool swapped = false;
        for (int j = 0; ++comparisons, j < i; j++) {
            if (++comparisons, a[j] > a[j + 1]) {
                swapped = true;
                HoanVi(a[j], a[j + 1]);
            }
        }
        if (++comparisons, !swapped)
            return;
    }
}

void shakerSort(int a[], int n, long long& comparisons) {
    int left = 0;
    int right = n - 1;
    int k = 0;
    while (++comparisons, left <= right) {
        bool swapped = false;
        for (int j = left; ++comparisons, j < right; j++) {
            if (++comparisons, a[j] > a[j + 1]) {
                swapped = true;
                HoanVi(a[j], a[j + 1]);
                k = j;
            }
        }
        if (++comparisons, !swapped)
            return;
        right = k;
        swapped = false;
        for (int j = right; ++comparisons, j > left; j--) {
            if (++comparisons, a[j] < a[j - 1]) {
                swapped = true;
                HoanVi(a[j], a[j - 1]);
                k = j;
            }
        }
        if (++comparisons, !swapped)
            return;
        left = k;
    }
}

void selectionSort(int a[], int n, long long& comparisons) {
    for (int i = 0; ++comparisons, i < n; i++) {
        int minIndex = i;
        for (int j = i + 1; ++comparisons, j < n; j++) {
            if (++comparisons, a[j] < a[minIndex]) {
                minIndex = j;
            }
        }
        HoanVi(a[i], a[minIndex]);
    }
}

void insertionSort(int a[], int n, long long& comparisons) {
    for (int i = 1; ++comparisons, i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (++comparisons, j >= 0) {
            if (++comparisons, a[j] > key) {
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
    while (++comparisons, i <= j) {
        while (++comparisons, a[i] < pivot) {
            i++;
        }
        while (++comparisons, a[j] > pivot) {
            j--;
        }
        if (++comparisons, i <= j) {
            HoanVi(a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(int a[], int first, int last, long long& comparisons) {
    int index = partition(a, first, last, comparisons);
    if (++comparisons, first < index - 1)
        quickSort(a, first, index - 1, comparisons);
    if (++comparisons, index < last)
        quickSort(a, index, last, comparisons);
}

void heapRebuild(int a[], int pos, int n, long long& comparisons) {
    while (++comparisons, 2 * pos + 1 < n) {
        int j = 2 * pos + 1;
        if (++comparisons, j < n - 1) {
            if (++comparisons, a[j] < a[j + 1])
                j++;
        }
        if (++comparisons, a[pos] >= a[j])
            return;
        HoanVi(a[pos], a[j]);
        pos = j;
    }
}

void heapConstruct(int a[], int n, long long& comparisons) {
    for (int i = (n - 1) / 2; ++comparisons, i >= 0; i--) {
        heapRebuild(a, i, n, comparisons);
    }
}

void heapSort(int a[], int n, long long& comparisons) {
    heapConstruct(a, n, comparisons);
    int r = n - 1;
    while (++comparisons, r > 0) {
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
    for (int i = 0; ++comparisons, i < n1; i++) {
        L[i] = a[first + i];
    }
    for (int j = 0; ++comparisons, j < n2; j++) {
        R[j] = a[mid + j + 1];
    }
    int i = 0;
    int j = 0;
    int k = first;
    while (++comparisons, i < n1 && ++comparisons, j < n2) {
        if (++comparisons, L[i] < R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (++comparisons, j < n2) {
        a[k++] = R[j++];
    }
    while (++comparisons, i < n1) {
        a[k++] = L[i++];
    }
    delete[] L;
    delete[] R;
}

void mergeSort(int a[], int first, int last, long long& comparisons) {
    if (++comparisons, first < last) {
        int mid = first + (last - first) / 2;
        mergeSort(a, first, mid, comparisons);
        mergeSort(a, mid + 1, last, comparisons);
        merge(a, first, mid, last, comparisons);
    }
}

void shellSort(int a[], int n, long long& comparisons) {
    for (int interval = n / 2; ++comparisons, interval > 0; interval /= 2) {
        for (int i = interval; ++comparisons, i < n; i++) {
            int temp = a[i];
            int j = i;
            while (++comparisons, j >= interval) {
                if (++comparisons, a[j - interval] > temp) {
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
    while (++comparisons, true) {
        if (++comparisons, first >= last) {
            return (++comparisons, a[first] > item) ? first : first + 1;
        }
        int mid = (first + last) / 2;
        if (++comparisons, a[mid] == item)
            return mid + 1;
        if (++comparisons, a[mid] < item)
            first = mid + 1;
        else
            last = mid - 1;
    }
}

void binaryInsertionSort(int a[], int n, long long& comparisons) {
    int i, loc, j, k, selected;
    for (i = 1; ++comparisons, i < n; ++i) {
        j = i - 1;
        selected = a[i];
        loc = binarySearch(a, 0, selected, j, comparisons);
        while (++comparisons, j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[loc] = selected;
    }
}

void countingSort(int a[], int n, long long& comparisons) {
    int max = a[0];
    for (int i = 1; ++comparisons, i < n; i++) {
        if (++comparisons, a[i] > max)
            max = a[i];
    }

    int *count = new int[max + 1];
    for (int i = 0; ++comparisons, i <= max; i++) {
        count[i] = 0;
    }

    for (int i = 0; ++comparisons, i < n; i++) {
        count[a[i]]++;
    }

    for (int i = 1; ++comparisons, i <= max; i++) {
        count[i] += count[i - 1];
    }

    int *temp = new int[n];
    for (int i = 0; ++comparisons, i < n; i++) {
        temp[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }

    for (int i = 0; ++comparisons, i < n; i++) {
        a[i] = temp[i];
    }
    delete[] count;
    delete[] temp;
}

void radixSort(int a[], int n, long long& comparisons) {
    int *b = new int[n];
    int m = a[0], exp = 1;

    for (int i = 0; ++comparisons, i < n; i++) {
        if (++comparisons, a[i] > m)
            m = a[i];
    }

    while (++comparisons, m / exp > 0) {
        int bucket[10] = { 0 };
        for (int i = 0; ++comparisons, i < n; i++) {
            bucket[a[i] / exp % 10]++;
        }
        for (int i = 1; ++comparisons, i < 10; i++) {
            bucket[i] += bucket[i - 1];
        }
        for (int i = n - 1; ++comparisons, i >= 0; i--) {
            b[--bucket[a[i] / exp % 10]] = a[i];
        }
        for (int i = 0; ++comparisons, i < n; i++) {
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
    for (int i = 0; ++comparisons, i < m; i++) {
        l[i] = 0;
    }
    for (int i = 1; ++comparisons, i < n; i++) {
        if (++comparisons, a[i] < minVal)
            minVal = a[i];
        if (++comparisons, a[i] > a[max])
            max = i;
    }
    if (++comparisons, a[max] == minVal)
        return;
    double c1 = (double)(m - 1) / (a[max] - minVal);
    for (int i = 0; ++comparisons, i < n; i++) {
        int k = int(c1 * (a[i] - minVal));
        ++l[k];
    }
    for (int i = 1; ++comparisons, i < m; i++) {
        l[i] += l[i - 1];
    }
    HoanVi(a[max], a[0]);
    int nmove = 0;
    int j = 0;
    int k = m - 1;
    int t = 0;
    int flash;
    while (++comparisons, nmove < n - 1) {
        while (++comparisons, j > l[k] - 1) {
            j++;
            k = int(c1*(a[j] - minVal));
        }
        flash = a[j];
        if (++comparisons, k < 0) break;
        while (++comparisons, j != l[k]) {
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