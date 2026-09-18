#include "sorting.h"

vector<string> algos = {"ema-heap-stalin-sort", "heap-stalin-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort"};
// vector<string> algos = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort",
//      "shell-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", 
//      "flash-sort", "heap-stalin-sort"};
vector<string> output_parameters = {"-time", "-comp", "-both"};
vector<string> input_orders = {"-rand", "-sorted", "-rev", "-nsorted"};

void runAllBenchmarks(string csvFilename, int runs);

struct Stats {
    double avg;
    long long min;
    long long max;
    double stddev;
};

Stats getStats(const vector<long long>& v) {
    Stats s = {0.0, 0, 0, 0.0};
    if (v.empty()) return s;
    
    s.min = *min_element(v.begin(), v.end());
    s.max = *max_element(v.begin(), v.end());
    
    double sum = accumulate(v.begin(), v.end(), 0.0);
    s.avg = sum / v.size();
    
    double variance = 0;
    for (auto val : v) {
        variance += (val - s.avg) * (val - s.avg);
    }
    s.stddev = sqrt(variance / v.size()); 
    return s;
}

//function to check if a string is a number
bool isNumber(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

void genAndWrite(string filename, int n, int dataType) {
    ofstream file;
    file.open(filename);
    if (!file) {
        cout << "Error: Cannot open " << filename << "\n";
        return;
    }
    int *a = new int[n];
    GenerateData(a, n, dataType);
    file << n << "\n";
    for (int i = 0; i < n; i++) {
        file << a[i] << " ";
    }
    file.close();
    delete[] a; 
}

void processSort(vector<string> algs, string input_file, string output_params, int flag = 0) {

    vector<Record> result;

    for (int i = 0; i < algs.size(); ++i) {
        
        ifstream file;
        file.open(input_file);
        int n;
        file >> n;
        int *a = new int[n];
        for (int i = 0; i < n; i++) {
            file >> a[i];
        }
        file.close();

        string alg = algs[i];
        Record record;
        if (alg == "selection-sort") {
            record = getRecord(a, n, selectionSort, selectionSort);
        }
        if (alg == "insertion-sort") {
            record = getRecord(a, n, insertionSort, insertionSort);
        }
        if (alg == "bubble-sort") {
            record = getRecord(a, n, bubbleSort, bubbleSort);
        }
        if (alg == "shaker-sort") {
            record = getRecord(a, n, shakerSort, shakerSort);
        }
        if (alg == "shell-sort") {
            record = getRecord(a, n, shellSort, shellSort);
        }
        if (alg == "heap-sort") {
            record = getRecord(a, n, heapSort, heapSort);
        }
        if (alg == "merge-sort") {
            record = getRecord(a, n, mergeSort, mergeSort);
        }
        if (alg == "quick-sort") {
            record = getRecord(a, n, quickSort, quickSort);
        }
        if (alg == "counting-sort") {
            record = getRecord(a, n, countingSort, countingSort);
        }
        if (alg == "radix-sort") {
            record = getRecord(a, n, radixSort, radixSort);
        }
        if (alg == "flash-sort") {
            record = getRecord(a, n, flashSort, flashSort);
        }
        if (alg == "tim-sort") {
            record = getRecord(a, n, timSort, timSort);
        }
        result.push_back(record);

        if (algs.size() == 1 && flag == 0) {
            ofstream ofs;
            ofs.open("output.txt");
            ofs << n << "\n";
            for (int i = 0; i < n; i++) {
                ofs << a[i] << " ";
            }
        }

        delete[] a;
    }

    if (output_params == "-time" || output_params == "-both" || output_params == "") {
        cout << "Running time: ";
        for (int i = 0; i < result.size(); i++) {
            if (i != result.size() - 1) cout << result[i].time << " | "; else cout << result[i].time;
        }
        cout << "\n";
    }

    if (output_params == "-comp" || output_params == "-both" || output_params == "") {
        cout << "Comparisons: ";
        for (int i = 0; i < result.size(); i++) {
            if (i != result.size() - 1) cout << result[i].comparison << " | "; else cout << result[i].comparison;
        }
        cout << "\n\n";
    }
    
}

void processArg(int argc, char* argv[]) {
    string mode = "";
    vector<string> algs;
    int input_size = 0;
    int runs = 1; // Default number of runs for benchmarking
    bool do_benchmark = false;

    string input_order = "";
    string input_path = ""; // use this if input_size and input_order not specified
    string output_params = ""; // only apply to mode -a

    // intercept the benchmark and run count arguments
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
            runs = stoi(argv[i+1]);
        }
        if (strcmp(argv[i], "-benchmark") == 0) {
            do_benchmark = true;
        }
    }
    
    // trigger the benchmark and exit if requested
    if (do_benchmark) {
        runAllBenchmarks("benchmark_results_compare_33%.csv", runs);
        return; 
    }

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0) mode = "-c";
        else if (strcmp(argv[i], "-a") == 0) mode = "-a";

        else if (find(algos.begin(), algos.end(), argv[i]) != algos.end()) {
            algs.push_back(argv[i]);
        }

        else if (find(output_parameters.begin(), output_parameters.end(), argv[i]) != output_parameters.end()) {
            output_params = argv[i];
        }

        else if (isNumber(argv[i])) {
            input_size = stoi(argv[i]);
        }

        else if (find(input_orders.begin(), input_orders.end(), argv[i]) != input_orders.end()) {
            input_order = argv[i];
        } 
        
        else if (i != 0) {
            input_path = argv[i];
        }
    }

    if (mode == "") {
        cout << "Error: No mode specified\n";
        return;
    }

    if (algs.empty()) {
        cout << "Error: No algorithm specified\n";
        return;
    }

    if (mode == "-a") {
        cout << "ALGORITHM MODE\n";
    } else {
        cout << "COMPARISON MODE\n";
    }

    // output algs list
    cout << "Algorithms: ";
    for (int i = 0; i < algs.size(); i++) {
        if (i != algs.size() - 1) cout << algs[i] << " | "; else cout << algs[i];
    }
    cout << "\n";


    if (input_size != 0) {
    cout << "Input size: " << input_size << "\n";
    if (input_order != "") {
        cout << "Input order: " << input_order << "\n";
        cout << "--------------------\n";
        genAndWrite("input.txt", input_size, distance(input_orders.begin(), find(input_orders.begin(), input_orders.end(), input_order)));
        processSort(algs, "input.txt", output_params);
    } else {
        // run all orders, each order output to input_x.txt with x is datatype
        for (int i = 0; i < input_orders.size(); i++) {
            cout << "Input order: " << input_orders[i] << "\n";
            cout << "--------------------\n";
            int j;
            if (i == 0) j = 1; //random
            if (i == 1) j = 3; //sorted
            if (i == 2) j = 4; //rev
            if (i == 3) j = 2; //nsorted
            genAndWrite("input_" + to_string(j) + ".txt", input_size, i);
            processSort(algs, "input_" + to_string(j) + ".txt", output_params, 1);
        }
    }
    } else { // no input size, run from file
        ifstream file;
        file.open(input_path);
        if (!file) {
            cout << "Error: File not found\n";
            return;
        }
        int n; file >> n;
        file.close();
        cout << "Input file: " << input_path << "\n";
        cout << "Input size: " << n << "\n";
        cout << "--------------------\n";
        processSort(algs, input_path, output_params);
    }
    return;
}


template <class T>
void HoanVi(T &a, T &b) {
	T x = a;
	a = b;
	b = x;
}

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n) {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = ((rand() << 15) | rand()) % n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n) {
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
    int swap = n / 3; // Swap 10% of the elements
	for (int i = 0; i < swap; i ++)
	{
		int r1 = ((rand() << 15) | rand()) % n;
        int r2 = ((rand() << 15) | rand()) % n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType) {
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

void runAllBenchmarks(string csvFilename, int runs = 1) {
    vector<int> data_sizes = {10000, 30000, 50000, 100000, 300000, 500000}; 
    
    ofstream csv(csvFilename);
    if (!csv) {
        cout << "Error: Cannot open " << csvFilename << " for writing.\n";
        return;
    }
    
    // CSV header
    csv << "Algorithm,Data Size,Data Order,Runs,"
        << "Time Avg (ms),Time Min,Time Max,Time Std,"
        << "Comp Avg,Comp Min,Comp Max,Comp Std,"
        << "Purge Avg,Purge Min,Purge Max,Purge Std\n";
    
    for (int size : data_sizes) {
        for (int orderIdx = 0; orderIdx < input_orders.size(); orderIdx++) { 
            if (orderIdx != 3) continue;
            cout << "Benchmarking Size: " << size << " | Order: " << input_orders[orderIdx] << " (" << runs << " runs)...\n";
            
            // Dictionaries to accumulate metrics across multiple runs
            map<string, vector<long long>> time_map, comp_map, purge_map;
            
            for (int r = 0; r < runs; r++) {
                // fresh data for each run to capture true variance
                int* masterArr = new int[size];
                GenerateData(masterArr, size, orderIdx);
                
                for (const string& algName : algos) { 
                    int* a = new int[size];
                    for(int k = 0; k < size; k++) a[k] = masterArr[k]; 
                    
                    Record record;
                    if (algName == "selection-sort") record = getRecord(a, size, selectionSort, selectionSort);
                    else if (algName == "insertion-sort") record = getRecord(a, size, insertionSort, insertionSort);
                    else if (algName == "bubble-sort") record = getRecord(a, size, bubbleSort, bubbleSort);
                    else if (algName == "shaker-sort") record = getRecord(a, size, shakerSort, shakerSort);
                    else if (algName == "shell-sort") record = getRecord(a, size, shellSort, shellSort);
                    else if (algName == "heap-sort") record = getRecord(a, size, heapSort, heapSort);
                    else if (algName == "merge-sort") record = getRecord(a, size, mergeSort, mergeSort);
                    else if (algName == "quick-sort") record = getRecord(a, size, quickSort, quickSort);
                    else if (algName == "counting-sort") record = getRecord(a, size, countingSort, countingSort);
                    else if (algName == "radix-sort") record = getRecord(a, size, radixSort, radixSort);
                    else if (algName == "flash-sort") record = getRecord(a, size, flashSort, flashSort);
                    else if (algName == "tim-sort") record = getRecord(a, size, timSort, timSort);
                    else if (algName == "heap-stalin-sort") {
                        int *b = new int[size];
                        for (int k = 0; k < size; k++) b[k] = a[k]; 
                        heapStalinSort(a, size, record.comparison, record.purgeCount);
                        auto start = high_resolution_clock::now();
                        long long dummyComp, dummyPurge;
                        heapStalinSort(b, size, dummyComp, dummyPurge);
                        auto stop = high_resolution_clock::now();
                        record.time = duration_cast<milliseconds>(stop - start).count();
                        delete[] b;
                    }
                    else if (algName == "double-heap-stalin-sort") {
                        int *b = new int[size];
                        for (int k = 0; k < size; k++) b[k] = a[k]; 
                        doubleHeapStalinSort(a, size, record.comparison, record.purgeCount);
                        auto start = high_resolution_clock::now();
                        long long dummyComp, dummyPurge;
                        doubleHeapStalinSort(b, size, dummyComp, dummyPurge);
                        auto stop = high_resolution_clock::now();
                        record.time = duration_cast<milliseconds>(stop - start).count();
                        delete[] b;
                    }
                    else if (algName == "ema-heap-stalin-sort") {
                        int *b = new int[size];
                        for (int k = 0; k < size; k++) b[k] = a[k]; 
                        emaHeapStalinSort(a, size, record.comparison, record.purgeCount);
                        auto start = high_resolution_clock::now();
                        long long dummyComp, dummyPurge;
                        emaHeapStalinSort(b, size, dummyComp, dummyPurge);
                        auto stop = high_resolution_clock::now();
                        record.time = duration_cast<milliseconds>(stop - start).count();
                        delete[] b;
                    }
                    else {
                        cout << "Error: unknown algorithm " << algName << "!\n";
                        delete[] a;
                        continue;
                    }
                    
                    // push metrics into the mapping for this specific run
                    time_map[algName].push_back(record.time);
                    comp_map[algName].push_back(record.comparison);
                    purge_map[algName].push_back(record.purgeCount);
                    
                    delete[] a;
                }
                delete[] masterArr;
            }
            
            // calculate and output stats for the CSV
            for (const string& algName : algos) {
                Stats t_stats = getStats(time_map[algName]);
                Stats c_stats = getStats(comp_map[algName]);
                Stats p_stats = getStats(purge_map[algName]);
                
                csv << algName << "," << size << "," << input_orders[orderIdx] << "," << runs << ","
                    << t_stats.avg << "," << t_stats.min << "," << t_stats.max << "," << t_stats.stddev << ","
                    << c_stats.avg << "," << c_stats.min << "," << c_stats.max << "," << c_stats.stddev << ","
                    << p_stats.avg << "," << p_stats.min << "," << p_stats.max << "," << p_stats.stddev << "\n";
            }
        }
    }
    csv.close();
    cout << "\nBenchmark complete! Results saved to " << csvFilename << "\n";
}