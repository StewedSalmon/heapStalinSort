#include <algorithm>

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

void heapStalinSort(int a[], int n)
{
    int *purged = new int[n]; // worst case: all elements are purged
    int purgeCount = 0;

    // scan for max and min 
    int min_val = a[0], max_val = a[0];
    for (int i = 1; i < n; ++i) {
        if (a[i] < min_val) min_val = a[i];
        else if (a[i] > max_val) max_val = a[i];
    }
    long long range = max_val - min_val;

    int writeIndex = 1;
    for (int i = 1; i < n; ++i) {
        // Compute dynamic upper bound: Expected linear value + 10% tolerance gap
        long long expected_max = min_val + (range * i) / n + (range / 50);

        if (a[i] >= a[writeIndex - 1] && a[i] <= expected_max) {
            a[writeIndex++] = a[i]; // Passed both the relative and global bounds
        } else {
            // apply 1-look back to see if the PREVIOUS element was a false spike
            if (writeIndex == 1 || (a[i] >= a[writeIndex - 2] && a[i] <= expected_max)) {
                purged[purgeCount++] = a[writeIndex - 1];
                a[writeIndex - 1] = a[i]; 
            } else {
                purged[purgeCount++] = a[i];
            }
        }
    }

    if (purgeCount == 0)
    {
        delete [] purged;
        return;
    }

    // min-heap merge

    buildMinHeap(purged, purgeCount);
    int* merge = new int[n];
    int i = 0; int k = 0;
    while (i < writeIndex && purgeCount)
    {
        if (a[i] < purged[0])
        {
            merge[k++] = a[i];
            i++;
        }
        else
        {
            merge[k++] = purged[0];
            purged[0] = purged[purgeCount - 1];
            purgeCount--;
            heapifyMin(purged, purgeCount, 0);
        }
    }

    while (i < writeIndex)
    {
        merge[k++] = a[i];
        i++;
    }

    while (purgeCount)
    {
        merge[k++] = purged[0];
        purged[0] = purged[purgeCount - 1];
        purgeCount--;
        heapifyMin(purged, purgeCount, 0);
    }

    std::copy(merge, merge + n, a);
    delete [] merge;
    delete [] purged;
}