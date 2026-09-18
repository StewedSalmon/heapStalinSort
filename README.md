# HEAP STALIN SORT

Heap Stalin Sort is a hybrid heuristic sorting algorithm inspired by the "Stalin Sort" meme. The intuition for development comes from the question: Is there a way to exploit Stalin Sort's ability to cheaply extract an increasing run while making the algorithm lossless? To achieve this,  a modified Stalin pass is combined with a Min-Heap to sort and merge the purged anomalies back into the sequence.

## DEVELOPMENT

The algorithm evolved through several distinct phases to solve a fundamental flaw in single-pass linear filters: cascading failure mode, where the number of purged elements grows exponentially.

* **v1: Vanilla Heap Stalin Sort:** Scans the array for strictly out-of-order elements and sends them to a Min-Heap, and merges them back. While it works perfectly on sorted data, the purge rate cascades immediately when as few as 10 anomalies are introduced. 
* **v2: 1-Step Look-Back (Local Cascade Prevention):** If an element fails the check, the algorithm checks `i-2` to see if the previous anchor was actually a false spike. This reduces the purge rate dramatically on very small swaps but still cascades when anomaly density scales with N.
* **v3: Linear Threshold (Global Cascade Prevention):** Attempts to attack a different failure mode by projecting a global mathematical ceiling over the array based on the index. Initially, this performed equally badly because it lacked the local logic to fix sequence breaks.
* **v4: Combination (Local + Global Prevention):** By fusing the 1-step look-back with a 2% linear threshold, the algorithm can fix micro-clusters while maintaining a global boundary. The purge rate scales excellently on low swap rates (<5%) and in smaller sizes, effectively decoupling the purge count from the array size.
* **v5: EMA Threshold (Final Architecture):** Linear threshold collapses at higher entropies (10-20% swaps) due to dense anomaly clusters. In v5, it is replaced with a bit-shifted Exponential Moving Average (EMA). This threshold adapts around dense clusters, resulting in a major performance improvement at higher swap rates (10-20%) and massive array sizes (500k+).

## ALGORITHM OVERVIEW AND ANALYSIS

### 1. Main Phases of the Algorithm

The final v5 architecture operates in four distinct phases:

1. **Boundary Scan:** An initial scan to find the minimum and maximum values of the dataset, determining the tolerance baseline.
2. **The EMA Stalin Filter:** The algorithm tracks the actual shape of the valid sequence using a  bit-shifted Exponential Moving Average. True anomalies are extracted to a secondary `purged` array, while 1 look-back mechanism locally fixes false spikes.
3. **Heapify:** The k elements in the `purged` array are transformed into a Min-Heap.
4. **Min-Heap Merge:** A standard 2-way merge stitches the valid primary sequence and the Min-Heap back together.

### 2. Time and Space Complexity

* **Time Complexity:** `O(N) + O(k log k)` *(where `k` is the number of purged elements)*.
* **Best Case (Sorted Data):** `O(N)` No elements are purged, so the heap construction phase is skipped.
* **Adaptive Case (Partially Sorted Data):** `O(N + k log k)` The algorithm adapts its reconstruction cost to the amount of disorder detected in the input. In experiments with randomly swapped partially sorted data, the purge rate was often around twice the swap rate in the lower-disorder regime, while the algorithm continued to operate in the adaptive regime at substantially higher swap rates.
* **Worst Case (Random / Reversed Data):** `O(n log n)` When k approaches N, the heap construction dominates and the algorithm degrades toward the complexity of Heap Sort.

* **Space Complexity:** `O(N)`. The algorithm requires contiguous auxiliary memory to hold the `purged` buffer and the final `merge` array.

---

## RESULTS ANALYSIS

### 1. Comparison to Standard Sorts

*(Insert generated chart comparing v5 to Heap, Merge, Quick here)*

In randomly sorted and reverse sorted arrays, EMA Heap Stalin Sort demonstrates execution times similar to Heap Sort, but with slightly higher comparison counts across all data sizes. This occurs because the algorithm degrades to a standard Heap Sort when its heuristics fail; in highly disordered data, the EMA threshold is exceeded, resulting in nearly 100% of the array being purged to the Min-Heap. Compared to Quick Sort, the algorithm’s metrics are approximately 2 times higher in randomly sorted data and up to 7 times higher in reverse sorted data.

In sorted data, EMA Heap Stalin Sort is significantly faster than all benchmarked algorithms, yielding a comparison count of exactly 4N - 4. Because zero elements are purged (k = 0), the Min-Heap and merge phases are bypassed, resulting in an optimal O(N) run time.

In partially sorted datasets (especially on lower disorders), EMA Heap Stalin Sort matches the execution time of Quick Sort across all tested sizes while maintaining the lowest comparison count among the evaluated algorithms.


### 2. v4 vs v5

*(Insert generated charts for 2%, 5%, 10%, and 20% comparisons here)*

v4 and v5 exhibit identical performance in arrays with 2% swaps. However, at 5% and 10% swaps, their metrics diverge significantly at the 500k size. v4 shows approximately a 25% higher execution time and a 40% higher comparison count at 5% swaps; these differences increase to 118% and 161%, respectively, at 10%. At 20% swaps, v4's linear threshold heuristic purges over 93% of the dataset and executes in nearly twice the time of v5.

This divergence highlights the limitation of a rigid linear threshold. While effective for isolated anomalies at 2% disorder, the strict threshold in v4 cannot adapt to the denser anomaly clusters present at 10% and 20%. On the other hand, v5 adapts dynamically to the data's shape and remains more resistant to cascade failure observed in v4. It retains more valid elements in the primary sequence, maintaining a significantly lower purge count.

## LIMITATIONS

* **Input-Dependent Performance:** The algorithm's performance depends heavily on the structure of the input and the resulting number of purged elements `k`. Inputs with similar levels of disorder can still produce different purge rates.

* **No Guaranteed Purge Rate:** Although experiments showed a strong relationship between swap rate and purge rate in partially ordered inputs, the observed relationship is empirical rather than a theoretical guarantee. In particular, the purge rate can vary depending on the positions and interactions of the swaps.

* **Threshold Sensitivity:** The adaptive threshold and its tolerance parameter affect the balance between retaining elements and purging them. Poorly chosen parameters can increase the purge rate significantly.

* **Limited Benchmark Scope:** Current results are based primarily on sorted, reversed, random, and randomly swapped inputs. Other forms of structured disorder may produce different behavior and require further investigation.

## CONCLUSION

The Heap Stalin Sort is best categorized as a high-performance adaptive heuristic sorting algorithm. While the algorithm falls behind standard O(n log n) sorting algorithms in random or reversed data, it excels in sorted data and data with small-to-medium swap rates.