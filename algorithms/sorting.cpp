#include "sorting.h"

void copyArray(int a[], int b[], int n) {
    for (int i = 0; i < n; i++) {
        b[i] = a[i];
    }
}

Record getRecord(int a[], int n, void (*sortFunctionCmp)(int[], int, long long&), void (*sortFunction)(int[], int)) {
    Record record;
    record.comparison = 0;
    record.time = 0;
    record.purgeCount = 0;
    int *b = new int[n];
    copyArray(a, b, n);
    sortFunctionCmp(a, n, record.comparison);
    auto start = high_resolution_clock::now();
    sortFunction(b, n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    record.time = duration.count();
    delete[] b;
    return record;
}

void selectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int mn_index = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[mn_index]) {
                mn_index = j;
            }
        }
        int temp = a[i];
        a[i] = a[mn_index];
        a[mn_index] = temp;
    }
}

void selectionSort(int a[], int n, long long &comparison) {
    comparison = 0;
    for (int i = 0; ++comparison && i < n - 1; i++) {
        int mn_index = i;
        for (int j = i + 1; ++comparison && j < n; j++) {
            if (++comparison && a[j] < a[mn_index]) {
                mn_index = j;
            }
        }
        int temp = a[i];
        a[i] = a[mn_index];
        a[mn_index] = temp;
    }
}

// Original function
void insertionSort(int a[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

// Function with comparison counter
void insertionSort(int a[], int n, long long &comparison) {
    comparison = 0;

    int i, j, key;
	for (i = 1; i < n; i++) {
		key = a[i];
		j = i - 1;

		while ((j >= 0) && (++comparison && a[j] > key)) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}


void bubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (a[j+1] < a[j]) 
                swap(a[j+1], a[j]);
        }
    }
}

//comparison counter version

void bubbleSort(int a[], int n, long long &comparison) {
    comparison = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (++comparison && a[j+1] < a[j])
                swap(a[j+1], a[j]);
        }
    }
}

void shakerSort(int a[], int n) {
	int left = 0;
	int right = n - 1;
	int k = 0;

	while (left < right) {
		bool isSwapped = false;
		for (int i = left; i < right; i++) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				k = i;
				isSwapped = true;
			}
		}

		if (isSwapped == false) break;
		right = k;

		isSwapped = false;
		for (int i = right; i > left; i--) {
			if (a[i] < a[i - 1]) {
				swap(a[i], a[i - 1]);
				k = i;
				isSwapped = true;
			}
		}
		if (isSwapped == false) break;
			left = k;
		}
}

void shakerSort(int a[], int n, long long& comparison) {
    comparison = 0;
	int left = 0;
    int right = n - 1;
    int k = 0;

    while (++comparison && left < right) {
        bool isSwapped = false;
        for (int i = left; i < right; i++) {
            if (++comparison && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                k = i;
                isSwapped = true;
            }
        }

        if (isSwapped == false) break;
        right = k;

        isSwapped = false;
        for (int i = right; i > left; i--) {
            if (++comparison && a[i] < a[i - 1]) {
                swap(a[i], a[i - 1]);
                k = i;
                isSwapped = true;
            }
        }

        if (isSwapped == false) break;

        left = k;
    }
}

void shellSort(int a[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int tmp = a[i];
 
            int j;            
            for (j = i; j >= gap && a[j - gap] > tmp; j -= gap) {
                a[j] = a[j - gap];
            }
             
            a[j] = tmp;
        }
    }
}

void shellSort(int a[], int n, long long &comparison) {
    comparison = 0;
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int tmp = a[i];

            int j;
            for (j = i; (j >= gap) && (++comparison && a[j - gap] > tmp); j -= gap) {
                a[j] = a[j - gap];
            }

            a[j] = tmp;
        }
    }
}

void maxHeapify(int a[], int i, int n) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int mx = i;

    if (l <= n-1 && a[l] > a[mx]) {
        mx = l;
    }

    if (r <= n-1 && a[r] > a[mx]) {
        mx = r;
    }

    if (mx != i) {
        swap(a[i], a[mx]);
        maxHeapify(a, mx, n);
    }
}

void buildMaxHeap(int a[], int n) {
    for (int i = (n/2)-1; i >= 0; --i) {
        maxHeapify(a, i, n);
    }
}

void heapSort(int a[], int n) {

    buildMaxHeap(a, n);
    int sz = n;

    while (sz) {
        swap(a[0], a[sz-1]);
        --sz;
        maxHeapify(a, 0, sz);
    }
}

//Comparison version

void maxHeapify(int a[], int i, int n, long long &comparison) {
    int l = 2*i + 1;
    int r = 2*i + 2;
    int mx = i;

    if (l <= n-1 && ++comparison && a[l] > a[mx]) {
        mx = l;
    }

    if (r <= n-1 && ++comparison && a[r] > a[mx]) {
        mx = r;
    }

    if (mx != i) {
        swap(a[i], a[mx]);
        maxHeapify(a, mx, n, comparison);
    }
}

void buildMaxHeap(int a[], int n, long long &comparison) {
    for (int i = (n/2)-1; i >= 0; --i) {
        maxHeapify(a, i, n, comparison);
    }
}

void heapSort(int a[], int n, long long &comparison) {
    comparison = 0;
    buildMaxHeap(a, n, comparison);
    int sz = n;

    while (sz) {
        swap(a[0], a[sz-1]);
        --sz;
        maxHeapify(a, 0, sz, comparison);
    }
}

void Merge(int a[], int l, int mid, int r) {
    int* arr = new int[r - l + 1];
    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (a[i] < a[j])
            arr[k++] = a[i++];
        else
            arr[k++] = a[j++];
    }
    while (i <= mid) {
            arr[k++] = a[i++];
    }
    while (j <= r) {
            arr[k++] = a[j++];
    }

    for (int i = 0; i < k; i++) {
        a[l++] = arr[i];
    }

    delete[] arr;
}

void MergeSort(int a[], int l, int r) {
    if (l >= r) 
        return;

    int mid = (l + r) / 2;
    MergeSort(a, l, mid);
    MergeSort(a, mid + 1, r);

    Merge(a, l, mid, r);
}

void mergeSort(int a[], int n) {
    MergeSort(a, 0, n - 1);
}

//comparison counter version

void Merge(int a[], int l, int mid, int r, long long &comparison) {
    int* arr = new int[r - l + 1];
    int i = l, j = mid + 1, k = 0;

    while (i <= mid && j <= r) {
        if (++comparison && a[i] < a[j])
                arr[k++] = a[i++];
        else
                arr[k++] = a[j++];
    }
    while (i <= mid) {
            arr[k++] = a[i++];
    }
    while (j <= r) {
            arr[k++] = a[j++];
    }

    for (int i = 0; i < k; i++) {
        a[l++] = arr[i];
    }

    delete [] arr;
}

void MergeSort(int a[], int l, int r, long long& comparison) {
        if (l >= r) 
            return;

        int mid = (l + r) / 2;
        MergeSort(a, l, mid, comparison);
        MergeSort(a, mid + 1, r, comparison);
        Merge(a, l, mid, r, comparison);
}

void mergeSort(int a[], int n, long long &comparison) {
    MergeSort(a, 0, n - 1, comparison);
}

void swap(int &a, int &b){
    int tmp = a;
    a = b;
    b = tmp;
}

// Original function
int partition(int a[], int l, int r) {
    // FIX: Pick the middle element and swap it to the end
    int mid = l + (r - l) / 2;
    swap(a[mid], a[r]); 

    int p = r;  
    r = r - 1;        

    while (l <= r) {
        while (l <= r && a[l] < a[p]) l++;
        while (l <= r && a[r] > a[p]) r--;

        if (l <= r) {
            swap(a[l], a[r]);
            l++;
            r--;
        }
    }

    swap(a[l], a[p]);
    return l;
}

void QuickSort(int a[], int l, int r) {
    if (l >= r) return;
 
    int p = partition(a, l, r);

    QuickSort(a, l, p - 1);
    QuickSort(a, p + 1, r);
}

void quickSort(int a[], int n) {
    QuickSort(a, 0, n-1);
}


// Function with comparison counter
int partition(int a[], int l, int r, long long &comparison) {
    // FIX: Pick the middle element and swap it to the end
    int mid = l + (r - l) / 2;
    swap(a[mid], a[r]); 

    int p = r;  
    r = r - 1;        

    while (l <= r) {
        while (l <= r && ++comparison && a[l] < a[p]) l++;
        while (l <= r && ++comparison && a[r] > a[p]) r--;

        if (l <= r) {
            swap(a[l], a[r]);
            l++;
            r--;
        }
    }

    swap(a[l], a[p]);
    return l;
}

void QuickSort(int a[], int l, int r, long long &comparison) {
    if (l >= r) return;
 
    int p = partition(a, l, r, comparison);

    QuickSort(a, l, p - 1, comparison);
    QuickSort(a, p + 1, r, comparison);
}

void quickSort(int a[], int n, long long &comparison) {
    comparison = 0;
    QuickSort(a, 0, n - 1, comparison);
}

void countingSort(int a[], int n) {
    int maxx = INT_MIN;
    int minn = INT_MAX;
    for (int i = 0; i < n; i++) {
        maxx = max(maxx , a[i]);
        minn = min(minn, a[i]);
    }
    int range = maxx - minn + 1;
    int *c = new int[range + 1];
    for (int i = 0; i < range; i++) {
        c[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        c[a[i] - minn]++;
    }
    for (int i = 1; i < range; i++) {
        c[i] += c[i - 1];
    }
    int *o = new int[n];
    for (int i = n - 1; i >= 0; i--) {
        o[c[a[i] - minn] - 1] = a[i];
        c[a[i] - minn]--;
    }
    for (int i = 0; i < n; i++) {
        a[i] = o[i];
    }
    delete[] c;
    delete[] o;
}

void countingSort(int a[], int n, long long& comparison) {
    comparison = 0;
    int maxx = INT_MIN;
    int minn = INT_MAX;
    for (int i = 0; i < n; i++) {
        maxx = max(maxx , a[i]);
        ++comparison;
        minn = min(minn, a[i]);
        ++comparison;
    }
    int range = maxx - minn + 1;
    int *c = new int[range + 1];
    for (int i = 0; i < range; i++) {
        c[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        c[a[i] - minn]++;
    }
    for (int i = 1; i < range; i++) {
        c[i] += c[i - 1];
    }
    int *o = new int[n];
    for (int i = n - 1;i >= 0; i--) {
        o[c[a[i] - minn] - 1] = a[i];
        c[a[i] - minn]--;
    }
    for (int i = 0; i < n; i++) {
        a[i] = o[i];
    }
    delete[] c;
    delete[] o;
}

int getMax(int a[], int n)
{
    int maxx = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > maxx)
            maxx = a[i];
    return maxx;
}
int getMax(int a[], int n, long long& comparison)
{
    int maxx = a[0];
    for (int i = 1; i < n; i++)
        if ( ++comparison && a[i] > maxx)
            maxx = a[i];
    return maxx;
}
int getMin(int a[], int n)
{
    int minn = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] < minn)
            minn = a[i];
    return minn;
}
int getMin(int a[], int n, long long& comparison)
{
    int minn = a[0];
    for (int i = 1; i < n; i++)
        if ( ++comparison && a[i] < minn)
            minn = a[i];
    return minn;
}
void countingSort(int a[], int n, int exp, int minn) {
    int* o = new int[n];
    int c[10] = {0};
    
    for (int i = 0;  i < n; i++) {
        c[((a[i] - minn) / exp % 10)]++;
    }
    
    for (int i = 1;  i < 10; i++)
        c[i] += c[i - 1];
    
    for (int i = n - 1;  i >= 0; i--) {
        o[c[((a[i] - minn) / exp % 10)] - 1] = a[i];
        c[((a[i] - minn) / exp % 10)]--;
    }

    for (int i = 0;  i < n; i++)
        a[i] = o[i];
    
    delete[] o;
}
void countingSort(int a[], int n, int exp, int minn, long long& comparison) {
    int* o = new int[n];
    int c[10] = {0};
    
    for (int i = 0; ++comparison && i < n; i++) {
        c[((a[i] - minn) / exp % 10)]++;
    }
    
    for (int i = 1; ++comparison && i < 10; i++)
        c[i] += c[i - 1];
    
    for (int i = n - 1; ++comparison && i >= 0; i--) {
        o[c[((a[i] - minn) / exp % 10)] - 1] = a[i];
        c[((a[i] - minn) / exp % 10)]--;
    }

    for (int i = 0; ++comparison && i < n; i++)
        a[i] = o[i];
    
    delete[] o;
}
void radixSort(int a[], int n) {
    int minn = getMin(a, n);
    
    int* shiftedArr = new int[n];
    for (int i = 0; i < n; i++) {
        shiftedArr[i] = a[i] - minn;
    }
    
    int maxx = getMax(a, n);
    long long temp = 0;
    for (int exp = 1; maxx / exp > 0; exp *= 10)
        countingSort(shiftedArr, n, exp, minn);
    
    for (int i = 0; i < n; i++) {
        a[i] = shiftedArr[i] + minn;
    }
    
    delete[] shiftedArr;
}
void radixSort(int a[], int n, long long& comparison) {
     comparison = 0;

    int minn = getMin(a, n, comparison);
    
    int* shiftedArr = new int[n];
    for (int i = 0; ++comparison && i < n; i++) {
        shiftedArr[i] = a[i] - minn;
    }
    
    int maxx = getMax(a, n, comparison);
    for (int exp = 1; ++comparison && maxx / exp > 0; exp *= 10)
        countingSort(shiftedArr, n, exp, minn, comparison);
    
    for (int i = 0; ++comparison && i < n; i++) {
        a[i] = shiftedArr[i] + minn;
    }
    
    delete[] shiftedArr;
}

int getK(int a, int m, int max, int min) {
    return 1ll * (m - 1) * (a - min) / (max - min);
}

void flashSort(int a[], int n) {
    if (n <= 1) 
        return;

    // Step 1
    int m = n * 0.45;
    if (m <= 2)
        m = 2;

    int* bucket = new int[m];
    for (int i = 0; i < m; ++i) {
        bucket[i] = 0;
    }

    int max = a[0], min = a[0];
    for (int i = 1; i < n; ++i) {
        if (max < a[i]) max = a[i];
        if (min > a[i]) min = a[i];
    }

    if (max == min) {
        delete[] bucket;
        return;
    }

    for (int i = 0; i < n; ++i) {
        ++bucket[getK(a[i], m, max, min)];
    }
    for (int i = 1; i < m; ++i) {
        bucket[i] += bucket[i - 1];
    }

    // Step 2
    int count = 0;
    int i = 0;
    while (count < n) {
        int k = getK(a[i], m, max, min);
        while (i >= bucket[k]) {
            k = getK(a[++i], m, max, min);
        }
        int z = a[i];
        while (i != bucket[k]) {
            k = getK(z, m, max, min);
            int y = a[bucket[k] - 1];
            a[--bucket[k]] = z;
            z = y;
            ++count;
        }
    }

    // Step 3
    for (int k = 1; k < m; ++k) {
        for (int i = bucket[k] - 2; i >= bucket[k - 1]; --i) {
            if (a[i] > a[i + 1]) {
                int t = a[i], j = i;
                while (t > a[j + 1]) {
                    a[j] = a[j + 1];
                    ++j;
                }
                a[j] = t;
            }
        }
    }

    delete[] bucket;
}

// Comparison counter version

void flashSort(int a[], int n, long long& comparison) {
    if (++comparison && n <= 1)
        return;

    // Step 1
    int m = n * 0.45;
    if (m <= 2)
        m = 2;

    int* bucket = new int[m];
    for (int i = 0; i < m; ++i)
        bucket[i] = 0;

   int max = a[0], min = a[0];
    for (int i = 1; i < n; ++i) {
        if (++comparison && max < a[i]) max = a[i];
        else if (++comparison && min > a[i]) min = a[i];
    }

    if (++comparison && max == min) {
        delete[] bucket;
        return;
    }

    for (int i = 0; i < n; ++i)
        ++bucket[getK(a[i], m, max, min)];
    for (int i = 1; i < m; ++i)
        bucket[i] += bucket[i - 1];

    // Step 2
    int count = 0;
    int i = 0;
    while (count < n) {
        int k = getK(a[i], m, max, min);
        while (++comparison && i >= bucket[k])
            k = getK(a[++i], m, max, min);
        
        int z = a[i];
        while (++comparison && i != bucket[k]) {
            k = getK(z, m, max, min);
            int y = a[bucket[k] - 1];
            a[--bucket[k]] = z;
            z = y;
            ++count;
        }
    }

    // Step 3
    for (int k = 1; k < m; ++k) {
        for (int i = bucket[k] - 2; ++comparison && i >= bucket[k - 1]; --i) {
            if (++comparison && a[i] > a[i + 1]) {
                int t = a[i], j = i;
                while (++comparison && t > a[j + 1]) {
                    a[j] = a[j + 1];
                    ++j;
                }
                a[j] = t;
            }
        }
    }

    delete[] bucket;
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

void heapifyMin(int a[], int n, int i, long long& comparison)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && ++comparison && a[left] < a[smallest])
    {
        smallest = left;
    }
    if (right < n && ++comparison && a[right] < a[smallest])
    {
        smallest = right;
    }
    if (smallest != i)
    {
        swap(a[i], a[smallest]);
        heapifyMin(a, n, smallest, comparison);
    }
}

void buildMinHeap(int a[], int n, long long& comparison)
{
    for (int i = (n / 2) - 1; i >= 0; i--)
    {
        heapifyMin(a, n, i, comparison);
    }
}

void heapStalinSort(int a[], int n, long long& comparison, long long& purgeCnt) {
    comparison = 0;
    purgeCnt = 0;
    int purgeCount = 0;
    int *purged = new int[n]; 

    // scan for max and min 
    int min_val = a[0], max_val = a[0];
    for (int i = 1; i < n; ++i) {
        if (++comparison && a[i] < min_val) min_val = a[i];
        else if (++comparison && a[i] > max_val) max_val = a[i];
    }
    long long range = max_val - min_val;

    int writeIndex = 1;
    for (int i = 1; i < n; ++i) {
        // Compute dynamic upper bound: Expected linear value + 10% tolerance gap
        long long expected_max = min_val + (range * i) / n + (range / 50);

        if ((++comparison && a[i] >= a[writeIndex - 1]) && (++comparison && a[i] <= expected_max)) {
            a[writeIndex++] = a[i]; // Passed both the relative and global bounds
        } else {
            // apply 1-look back to see if the PREVIOUS element was a false spike
            if (writeIndex == 1 || (++comparison && a[i] >= a[writeIndex - 2] && a[i] <= expected_max)) {
                purged[purgeCount++] = a[writeIndex - 1];
                a[writeIndex - 1] = a[i]; 
            } else {
                purged[purgeCount++] = a[i];
            }
        }
    }

    purgeCnt = purgeCount; // Update purge count reference

    if (purgeCount == 0) { 
        delete [] purged;
        return;
    }
    
    // min-heap merge
    buildMinHeap(purged, purgeCount, comparison);
    int* merge = new int[n];
    int i = 0; int k = 0;
    
    while ((i < writeIndex) && (purgeCount)) {
        if (++comparison && a[i] < purged[0]) {
            merge[k++] = a[i];
            i++;
        } else {
            merge[k++] = purged[0];
            purged[0] = purged[purgeCount - 1];
            purgeCount--;
            heapifyMin(purged, purgeCount, 0, comparison);
        }
    }

    while (i < writeIndex) merge[k++] = a[i++];
    
    while (purgeCount) {
        merge[k++] = purged[0];
        purged[0] = purged[purgeCount - 1];
        purgeCount--;
        heapifyMin(purged, purgeCount, 0, comparison);
    }

    std::copy(merge, merge + n, a);
    delete [] merge;
    delete [] purged;
}

long long lib_comparison = 0;
bool count_compare(int a, int b) {
    lib_comparison++;
    return a < b;
}

void timSort(int a[], int n) {
    gfx::timsort(a, a + n, count_compare);
}

void timSort(int a[], int n, long long& comparison) {
    lib_comparison = 0;
    gfx::timsort(a, a + n, count_compare);
    comparison = lib_comparison;
}

// void doubleHeapStalinSort(int a[], int n) {
//     int purgeCount = 0;
//     int *purged = new int[n]; 

//     // 1. O(N) Boundary Scan
//     int min_val = a[0], max_val = a[0];
//     for (int i = 1; i < n; ++i) {
//         if (a[i] < min_val) min_val = a[i];
//         else if (a[i] > max_val) max_val = a[i];
//     }
//     long long range = max_val - min_val;

//     // 2. Phase 1: Forward Stalin Filter
//     int writeIndex = 1;
//     for (int i = 1; i < n; ++i) {
//         long long expected_max = min_val + (range * i) / n + (range / 50);
        
//         if (a[i] >= a[writeIndex - 1] && a[i] <= expected_max) {
//             a[writeIndex++] = a[i]; 
//         } else {
//             if (writeIndex == 1 || (a[i] >= a[writeIndex - 2] && a[i] <= expected_max)) {
//                 purged[purgeCount++] = a[writeIndex - 1];
//                 a[writeIndex - 1] = a[i]; 
//             } else {
//                 purged[purgeCount++] = a[i];
//             }
//         }
//     }

//     if (purgeCount == 0) {
//         delete [] purged;
//         return;
//     }

//     // 3. Phase 2: Full-Fledged Backward Salvage Pass
//     int* double_purged = new int[purgeCount];
//     int dpCount = 0;
//     int* salvaged = new int[purgeCount];
//     int salvageCount = 0;

//     // Initial anchor
//     salvaged[salvageCount++] = purged[purgeCount - 1]; 

//     for (int i = purgeCount - 2; i >= 0; --i) {
//         // Reverse Dynamic Threshold: Creating a mathematical floor 
//         long long expected_min = min_val + (range * i) / purgeCount - (range / 50);
        
//         if (purged[i] <= salvaged[salvageCount - 1] && purged[i] >= expected_min) {
//             salvaged[salvageCount++] = purged[i];
//         } else {
//             // 1-step look-back (which is forward in this context) to heal bad anchors
//             if (salvageCount == 1 || (purged[i] <= salvaged[salvageCount - 2] && purged[i] >= expected_min)) {
//                 double_purged[dpCount++] = salvaged[salvageCount - 1]; // Evict the false anchor
//                 salvaged[salvageCount - 1] = purged[i]; // Establish the true sequence
//             } else {
//                 double_purged[dpCount++] = purged[i]; // True anomaly
//             }
//         }
//     }

//     // 4. Phase 3: The 3-Way Merge
//     int* merge = new int[n];
    
//     // Stage A: Linear Merge of Array A and Salvaged Array
//     int* valid_merge = new int[writeIndex + salvageCount];
//     int p = 0, pA = 0;
//     int pS = salvageCount - 1; // Read the salvaged array backwards to make it ascending again

//     while (pA < writeIndex && pS >= 0) {
//         if (a[pA] <= salvaged[pS]) {
//             valid_merge[p++] = a[pA++];
//         } else {
//             valid_merge[p++] = salvaged[pS--];
//         }
//     }
//     while (pA < writeIndex) valid_merge[p++] = a[pA++];
//     while (pS >= 0) valid_merge[p++] = salvaged[pS--];
    
//     int valid_count = p;

//     // Stage B: Min-Heap Merge for true anomalies
//     if (dpCount > 0) {
//         buildMinHeap(double_purged, dpCount);
//     }

//     int k = 0, v = 0;
//     while (v < valid_count && dpCount > 0) {
//         if (valid_merge[v] <= double_purged[0]) {
//             merge[k++] = valid_merge[v++];
//         } else {
//             merge[k++] = double_purged[0];
//             double_purged[0] = double_purged[dpCount - 1];
//             dpCount--;
//             if (dpCount > 0) heapifyMin(double_purged, dpCount, 0);
//         }
//     }

//     while (v < valid_count) merge[k++] = valid_merge[v++];
    
//     while (dpCount > 0) {
//         merge[k++] = double_purged[0];
//         double_purged[0] = double_purged[dpCount - 1];
//         dpCount--;
//         if (dpCount > 0) heapifyMin(double_purged, dpCount, 0);
//     }

//     std::copy(merge, merge + n, a);
    
//     delete [] valid_merge;
//     delete [] double_purged;
//     delete [] salvaged;
//     delete [] purged;
//     delete [] merge;
// }

// void doubleHeapStalinSort(int a[], int n, long long& comparison, long long& purgeCnt) {
//     comparison = 0;
//     int purgeCount = 0;
//     int *purged = new int[n]; 

//     // 1. O(N) Boundary Scan
//     int min_val = a[0], max_val = a[0];
//     for (int i = 1; i < n; ++i) {
//         if (++comparison && a[i] < min_val) min_val = a[i];
//         else if (++comparison && a[i] > max_val) max_val = a[i];
//     }
//     long long range = max_val - min_val;

//     // 2. Phase 1: Forward Stalin Filter
//     int writeIndex = 1;
//     for (int i = 1; i < n; ++i) {
//         long long expected_max = min_val + (range * i) / n + (range / 50);
        
//         if ((++comparison && a[i] >= a[writeIndex - 1]) && (++comparison && a[i] <= expected_max)) {
//             a[writeIndex++] = a[i]; 
//         } else {
//             if (writeIndex == 1 || ((++comparison && a[i] >= a[writeIndex - 2]) && (++comparison && a[i] <= expected_max))) {
//                 purged[purgeCount++] = a[writeIndex - 1];
//                 a[writeIndex - 1] = a[i]; 
//             } else {
//                 purged[purgeCount++] = a[i];
//             }
//         }
//     }

//     if (purgeCount == 0) {
//         purgeCnt = 0;
//         delete [] purged;
//         return;
//     }

//     // 3. Phase 2: Full-Fledged Backward Salvage Pass
//     int* double_purged = new int[purgeCount];
//     int dpCount = 0;
//     int* salvaged = new int[purgeCount];
//     int salvageCount = 0;

//     // Initial anchor
//     salvaged[salvageCount++] = purged[purgeCount - 1]; 

//     for (int i = purgeCount - 2; i >= 0; --i) {
//         // Reverse Dynamic Threshold: Creating a mathematical floor 
//         long long expected_min = min_val + (range * i) / purgeCount - (range / 50);
        
//         if ((++comparison && purged[i] <= salvaged[salvageCount - 1]) && (++comparison && purged[i] >= expected_min)) {
//             salvaged[salvageCount++] = purged[i];
//         } else {
//             // 1-step look-back (which is forward in this context) to heal bad anchors
//             if (salvageCount == 1 || ((++comparison && purged[i] <= salvaged[salvageCount - 2]) && (++comparison && purged[i] >= expected_min))) {
//                 double_purged[dpCount++] = salvaged[salvageCount - 1]; // Evict the false anchor
//                 salvaged[salvageCount - 1] = purged[i]; // Establish the true sequence
//             } else {
//                 double_purged[dpCount++] = purged[i]; // True anomaly
//             }
//         }
//     }

//     purgeCnt = dpCount; // Update CSV tracker to show true anomalies

//     // 4. Phase 3: The 3-Way Merge
//     int* merge = new int[n];
    
//     // Stage A: Linear Merge of Array A and Salvaged Array
//     int* valid_merge = new int[writeIndex + salvageCount];
//     int p = 0, pA = 0;
//     int pS = salvageCount - 1; // Read the salvaged array backwards to make it ascending again

//     while (pA < writeIndex && pS >= 0) {
//         if (++comparison && a[pA] <= salvaged[pS]) {
//             valid_merge[p++] = a[pA++];
//         } else {
//             valid_merge[p++] = salvaged[pS--];
//         }
//     }
//     while (pA < writeIndex) valid_merge[p++] = a[pA++];
//     while (pS >= 0) valid_merge[p++] = salvaged[pS--];
    
//     int valid_count = p;

//     // Stage B: Min-Heap Merge for true anomalies
//     if (dpCount > 0) {
//         buildMinHeap(double_purged, dpCount, comparison);
//     }

//     int k = 0, v = 0;
//     while (v < valid_count && dpCount > 0) {
//         if (++comparison && valid_merge[v] <= double_purged[0]) {
//             merge[k++] = valid_merge[v++];
//         } else {
//             merge[k++] = double_purged[0];
//             double_purged[0] = double_purged[dpCount - 1];
//             dpCount--;
//             if (dpCount > 0) heapifyMin(double_purged, dpCount, 0, comparison);
//         }
//     }

//     while (v < valid_count) merge[k++] = valid_merge[v++];
    
//     while (dpCount > 0) {
//         merge[k++] = double_purged[0];
//         double_purged[0] = double_purged[dpCount - 1];
//         dpCount--;
//         if (dpCount > 0) heapifyMin(double_purged, dpCount, 0, comparison);
//     }

//     std::copy(merge, merge + n, a);
    
//     delete [] valid_merge;
//     delete [] double_purged;
//     delete [] salvaged;
//     delete [] purged;
//     delete [] merge;
// }

void emaHeapStalinSort(int a[], int n) {
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
    }

    long long range = max_val - min_val;
    long long tolerance = range / 50; // 2% floating buffer

    // EMA buffer
    int writeIndex = 1;
    long long ema = min_val; 
    
    for (int i = 1; i < n; ++i) {
        // expected mathematical ceiling
        long long expected_max = ema + tolerance;
        
        if (a[i] >= a[writeIndex - 1] && a[i] <= expected_max) {
            a[writeIndex++] = a[i]; 
            
            // update the EMA toward the valid number
            ema = ema + ((a[i] - ema) / 32); 
        } else {
            // 1-look back error correction
            if (writeIndex == 1 || ((a[i] >= a[writeIndex - 2]) && (a[i] <= expected_max))) {
                purged[purgeCount++] = a[writeIndex - 1]; // Evict the false spike
                a[writeIndex - 1] = a[i]; 
                
                // correct the EMA to track the fixed sequence
                ema = ema + ((a[i] - ema) / 32); 
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

void emaHeapStalinSort(int a[], int n, long long& comparison, long long& purgeCnt) {
    comparison = 0;
    int purgeCount = 0;
    int *purged = new int[n];

    // 1. O(N) boundary scan to find min and max values
    int min_val = a[0], max_val = a[0];
    long long reverseCount = 0;
    for (int i = 1; i < n; ++i) {
        if (++comparison && a[i] < min_val) min_val = a[i];
        else if (++comparison && a[i] > max_val) max_val = a[i];
    }

    // reverse the array if it is mostly in descending order
    float reverseRatio = (float)reverseCount / n;
    if (reverseRatio > 0.8) {
        std::reverse(a, a + n);
    }

    long long range = max_val - min_val;
    long long tolerance = range / 50; // 2% floating buffer

    // EMA buffer
    int writeIndex = 1;
    long long ema = min_val; 
    
    for (int i = 1; i < n; ++i) {
        // expected mathematical ceiling
        long long expected_max = ema + tolerance;
        
        if ((++comparison && a[i] >= a[writeIndex - 1]) && (++comparison && a[i] <= expected_max)) {
            a[writeIndex++] = a[i]; 
            
            // update the EMA toward the valid number
            ema = ema + ((a[i] - ema) / 32); 
        } else {
            // 1-look back error correction
            if (writeIndex == 1 || ((++comparison && a[i] >= a[writeIndex - 2]) && (++comparison && a[i] <= expected_max))) {
                purged[purgeCount++] = a[writeIndex - 1]; // Evict the false spike
                a[writeIndex - 1] = a[i]; 
                
                // correct the EMA to track the healed sequence
                ema = ema + ((a[i] - ema) / 32); 
            } else {
                purged[purgeCount++] = a[i]; // true anomaly
            }
        }
    }

    purgeCnt = purgeCount;

    if (purgeCount == 0) {
        delete [] purged;
        return;
    }

    // min-heap merge
    buildMinHeap(purged, purgeCount, comparison);

    int* merge = new int[n];
    int k = 0, v = 0;

    while (v < writeIndex && purgeCount > 0) {
        if (++comparison && a[v] <= purged[0]) {
            merge[k++] = a[v++];
        } else {
            merge[k++] = purged[0];
            purged[0] = purged[purgeCount - 1];
            purgeCount--;
            if (purgeCount > 0) heapifyMin(purged, purgeCount, 0, comparison);
        }
    }

    while (v < writeIndex) merge[k++] = a[v++];
    
    while (purgeCount > 0) {
        merge[k++] = purged[0];
        purged[0] = purged[purgeCount - 1];
        purgeCount--;
        if (purgeCount > 0) heapifyMin(purged, purgeCount, 0, comparison);
    }

    std::copy(merge, merge + n, a);
    
    delete [] purged;
    delete [] merge;
}


void testSubject(int a[], int n) {
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
    }

    // EMA buffer
    int writeIndex = 1;
    long long ema = min_val; 

    long long range = max_val - min_val;
    long long avg_gap = range / n; 
    if (avg_gap == 0) avg_gap = 1; // Prevent zero-gap on flat lines

    // The hybrid tolerance formula
    long long tolerance = (range / 500) + (128 * avg_gap);

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

void testSubject(int a[], int n, long long& comparison, long long& purgeCnt) {
    comparison = 0;
    int purgeCount = 0;
    int *purged = new int[n];

    // 1. O(N) boundary scan to find min and max values
    int min_val = a[0], max_val = a[0];
    long long reverseCount = 0;
    for (int i = 1; i < n; ++i) {
        if (++comparison && a[i] < min_val) min_val = a[i];
        else if (++comparison && a[i] > max_val) max_val = a[i];
    }

    // reverse the array if it is mostly in descending order
    float reverseRatio = (float)reverseCount / n;
    if (reverseRatio > 0.8) {
        std::reverse(a, a + n);
    }

    // EMA buffer
    int writeIndex = 1;
    long long ema = min_val; 

    long long range = max_val - min_val;
    long long avg_gap = range / n; 
    if (avg_gap == 0) avg_gap = 1; // Prevent zero-gap on flat lines

    // The hybrid tolerance formula
    long long tolerance = (range / 500) + (128 * avg_gap);

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
            if (writeIndex == 1 || ++comparison &&  (a[i] >= a[writeIndex - 2] && 
                                    ++comparison && a[i] <= ema + tolerance)) {
                
                purged[purgeCount++] = a[writeIndex - 1]; // Evict the false spike
                a[writeIndex - 1] = a[i]; 
                
                ema = ema + ((a[i] - ema) / 32);
                consecutiveFall = 0;
            } else {
                purged[purgeCount++] = a[i]; // true anomaly
            }
        }
    }

    purgeCnt = purgeCount;

    if (purgeCount == 0) {
        delete [] purged;
        return;
    }

    // min-heap merge
    buildMinHeap(purged, purgeCount, comparison);

    int* merge = new int[n];
    int k = 0, v = 0;

    while (v < writeIndex && purgeCount > 0) {
        if (++comparison && a[v] <= purged[0]) {
            merge[k++] = a[v++];
        } else {
            merge[k++] = purged[0];
            purged[0] = purged[purgeCount - 1];
            purgeCount--;
            if (purgeCount > 0) heapifyMin(purged, purgeCount, 0, comparison);
        }
    }

    while (v < writeIndex) merge[k++] = a[v++];
    
    while (purgeCount > 0) {
        merge[k++] = purged[0];
        purged[0] = purged[purgeCount - 1];
        purgeCount--;
        if (purgeCount > 0) heapifyMin(purged, purgeCount, 0, comparison);
    }

    std::copy(merge, merge + n, a);
    
    delete [] purged;
    delete [] merge;
}