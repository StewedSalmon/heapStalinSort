#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <map>
#include "timsort.hpp"
using namespace std;
using namespace std::chrono;

struct Record {
    long long comparison;
    long long time; // in nanoseconds
    long long purgeCount; // for heapStalinSort
};

//function which returns Record struct of each sorting algorithm, passing the sorting function as a pointer
Record getRecord(int a[], int n, void (*sortFunctionCmp)(int[], int, long long&), void (*sortFunction)(int[], int));

// Prototype for original functions
void selectionSort(int a[], int n);
void insertionSort(int a[], int n);
void bubbleSort(int a[], int n);
void shakerSort(int a[], int n);
void shellSort(int a[], int n);
void heapSort(int a[], int n);
void mergeSort(int a[], int n);
void quickSort(int a[], int n);
void countingSort(int a[], int n);
void radixSort(int a[], int n);
void flashSort(int a[], int n);
void heapStalinSort(int a[], int n);
void timSort(int a[], int n);
void emaHeapStalinSort(int a[], int n);
void testSubject(int a[], int n);
// Prototype for functions with comparison counter
void selectionSort(int a[], int n, long long &comparison);
void insertionSort(int a[], int n, long long &comparison);
void bubbleSort(int a[], int n, long long &comparison);
void shakerSort(int a[], int n, long long &comparison);
void shellSort(int a[], int n, long long &comparison);
void heapSort(int a[], int n, long long &comparison);
void mergeSort(int a[], int n, long long &comparison);
void quickSort(int a[], int n, long long &comparison);
void countingSort(int a[], int n, long long &comparison);
void radixSort(int a[], int n, long long &comparison);
void flashSort(int a[], int n, long long &comparison);
void heapStalinSort(int a[], int n, long long &comparison, long long &purgeCnt);
void timSort(int a[], int n, long long& comparison);
void emaHeapStalinSort(int a[], int n, long long& comparison, long long& purgeCnt);
void testSubject(int a[], int n, long long& comparison, long long& purgeCnt);
//Data generator
void GenerateRandomData(int a[], int n);
void GenerateSortedData(int a[], int n);
void GenerateReverseData(int a[], int n);
void GenerateNearlySortedData(int a[], int n);
void GenerateData(int a[], int n, int dataType);

//Processing commandline args
void processArg(int argc, char* argv[]);


