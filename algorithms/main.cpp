#include "sorting.h"

using namespace std;

void printArr(int a[], int n) {
    for (int i = 0; i < n; i++){
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {

    processArg(argc, argv);

    return 0;
}