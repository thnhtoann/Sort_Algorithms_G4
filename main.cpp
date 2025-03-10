#include "DataGenerator.h"

using namespace std;

int main() {
    int a[3] = {0};
    GenerateSortedData(a, 3);
    for (int i = 0; i < 3; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;

    return 0;
}