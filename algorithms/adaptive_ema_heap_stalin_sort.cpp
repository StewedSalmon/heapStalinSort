#include <algorithm>
#include <cmath>

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

void heapifyMin(int a[], int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left] < a[smallest])
    {
        smallest = left;
    }
    if (right < n && a[right] < a[smallest])
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(a[i], a[smallest]);
        heapifyMin(a, n, smallest);
    }
}

void buildMinHeap(int a[], int n)
{
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapifyMin(a, n, i);
    }
}

void adapativeEmaHeapStalinSort(int a[], int n) {
    int purgeCount = 0;
    int *purged = new int[n]; 

    // 1. O(N) boundary scan to find min and max values
    int min_val = a[0], max_val = a[0];
    long long reverseCount = 0;
    for (int i = 1; i < n; ++i) {
        if (a[i] < a[i - 1]) reverseCount++;
        if (a[i] < min_val) min_val = a[i];
        else if (a[i] > max_val) max_val = a[i];
    }

    // reverse the array if it is mostly in descending order
    float reverseRatio = (float)reverseCount / n;
    if (reverseRatio > 0.8) {
        std::reverse(a, a + n);
        reverseRatio = 1.0f - reverseRatio;
    }
    // estimate disorder percentage
    double core = 1.0 - 2.0 * reverseRatio;
    if (core < 0.0) core = 0.0;

    double p = 1.0 - std::sqrt(core);
    if (p > 0.99) p = 0.99;

    // EMA buffer
    int writeIndex = 1;
    long long ema = min_val; 

    long long range = max_val - min_val;
    long long avg_gap = range / n; 
    if (avg_gap == 0) avg_gap = 1; // Prevent zero-gap on flat lines

    // The hybrid tolerance formula
    long long tolerance = (range / 500) + (long long)(128 / (1 - p) * avg_gap);

    int consecutiveFall = 0;
    long long shadowSequenceStart = 0;

    for (int i = 1; i < n; ++i) {
        // expected mathematical ceiling
        if (a[i] >= a[writeIndex - 1] && a[i] <= ema + tolerance) {

            a[writeIndex++] = a[i]; 
            
            // update the EMA toward the valid number
            ema = ema + ((a[i] - ema) / 32);

            consecutiveFall = 0;
        } else {
            // 1-look back error correction
            if (writeIndex == 1 || (a[i] >= a[writeIndex - 2] && 
                                    a[i] <= ema + tolerance)) {
                
                purged[purgeCount++] = a[writeIndex - 1]; // Evict the false spike
                a[writeIndex - 1] = a[i]; 
                
                ema = ema + ((a[i] - ema) / 32);
                consecutiveFall = 0;
            } else {
                purged[purgeCount++] = a[i]; // true anomaly
            }
        }
    }

    if (purgeCount == 0) {
        delete [] purged;
        return;
    }

    // min-heap merge
    buildMinHeap(purged, purgeCount);

    int* merge = new int[n];
    int k = 0, v = 0;

    while (v < writeIndex && purgeCount > 0) {
        if (a[v] <= purged[0]) {
            merge[k++] = a[v++];
        } else {
            merge[k++] = purged[0];
            purged[0] = purged[purgeCount - 1];
            purgeCount--;
            if (purgeCount > 0) heapifyMin(purged, purgeCount, 0);
        }
    }

    while (v < writeIndex) merge[k++] = a[v++];
    
    while (purgeCount > 0) {
        merge[k++] = purged[0];
        purged[0] = purged[purgeCount - 1];
        purgeCount--;
        if (purgeCount > 0) heapifyMin(purged, purgeCount, 0);
    }

    std::copy(merge, merge + n, a);
    
    delete [] purged;
    delete [] merge;
}