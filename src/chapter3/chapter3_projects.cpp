// ============================================================================
// Chapter 3 - Projects
// From: "Data Structures and Algorithm Analysis" by Clifford A. Shaffer
// ============================================================================

#include <iostream>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
#include <fstream>
#include <string>
#include <cassert>

// ============================================================================
// Project 3.1 - Boolean Access Time Comparison
//
// Compare access times for 32 Boolean values stored as:
//   (a) Single bit field (uint32_t with bit manipulation)
//   (b) Array of char
//   (c) Array of short
//   (d) Array of long
// ============================================================================

// Number of iterations — must be large enough to produce meaningful timing.
// Each iteration performs 32 reads + 32 writes = 64 accesses.
static const long long ITERATIONS = 100'000'000LL;

static void project_3_1() {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << " Project 3.1 — Boolean Access Time Comparison\n";
    std::cout << "========================================================\n";
    std::cout << " Storing 32 Boolean values in four different ways and\n";
    std::cout << " measuring the time to read+write all 32 values.\n";
    std::cout << " Iterations: " << ITERATIONS << "\n";
    std::cout << "========================================================\n\n";

    // We use volatile to prevent the compiler from optimizing away accesses.
    // The sink variable collects read results so they can't be discarded.
    volatile int sink = 0;

    // ---- (a) Bit field: store 32 bools in a single uint32_t ----
    {
        volatile uint32_t bitfield = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for (long long i = 0; i < ITERATIONS; i++) {
            // Write all 32 bits
            for (int b = 0; b < 32; b++) {
                bitfield |= (1U << b);        // set bit b
            }
            // Read all 32 bits
            uint32_t tmp = 0;
            for (int b = 0; b < 32; b++) {
                tmp += (bitfield >> b) & 1U;   // read bit b
            }
            sink = tmp;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        double accesses = (double)ITERATIONS * 64.0;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  Bit field (uint32_t):\n";
        std::cout << "    Total time:          " << ms << " ms\n";
        std::cout << "    Accesses:            " << std::scientific << std::setprecision(2) << accesses << "\n";
        std::cout << "    Time per access:     " << std::fixed << std::setprecision(4) << (ms / accesses * 1e6) << " ns\n\n";
    }

    // ---- (b) Array of char (1 byte per Boolean) ----
    {
        volatile char bools[32];
        for (int b = 0; b < 32; b++) bools[b] = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for (long long i = 0; i < ITERATIONS; i++) {
            // Write all 32 values
            for (int b = 0; b < 32; b++) {
                bools[b] = 1;
            }
            // Read all 32 values
            int tmp = 0;
            for (int b = 0; b < 32; b++) {
                tmp += bools[b];
            }
            sink = tmp;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        double accesses = (double)ITERATIONS * 64.0;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  char array (1 byte each):\n";
        std::cout << "    Total time:          " << ms << " ms\n";
        std::cout << "    Accesses:            " << std::scientific << std::setprecision(2) << accesses << "\n";
        std::cout << "    Time per access:     " << std::fixed << std::setprecision(4) << (ms / accesses * 1e6) << " ns\n\n";
    }

    // ---- (c) Array of short (2 bytes per Boolean) ----
    {
        volatile short bools[32];
        for (int b = 0; b < 32; b++) bools[b] = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for (long long i = 0; i < ITERATIONS; i++) {
            // Write all 32 values
            for (int b = 0; b < 32; b++) {
                bools[b] = 1;
            }
            // Read all 32 values
            int tmp = 0;
            for (int b = 0; b < 32; b++) {
                tmp += bools[b];
            }
            sink = tmp;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        double accesses = (double)ITERATIONS * 64.0;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  short array (2 bytes each):\n";
        std::cout << "    Total time:          " << ms << " ms\n";
        std::cout << "    Accesses:            " << std::scientific << std::setprecision(2) << accesses << "\n";
        std::cout << "    Time per access:     " << std::fixed << std::setprecision(4) << (ms / accesses * 1e6) << " ns\n\n";
    }

    // ---- (d) Array of long (4 or 8 bytes per Boolean) ----
    {
        volatile long bools[32];
        for (int b = 0; b < 32; b++) bools[b] = 0;

        auto start = std::chrono::high_resolution_clock::now();

        for (long long i = 0; i < ITERATIONS; i++) {
            // Write all 32 values
            for (int b = 0; b < 32; b++) {
                bools[b] = 1;
            }
            // Read all 32 values
            long tmp = 0;
            for (int b = 0; b < 32; b++) {
                tmp += bools[b];
            }
            sink = (int)tmp;
        }

        auto end = std::chrono::high_resolution_clock::now();
        double ms = std::chrono::duration<double, std::milli>(end - start).count();
        double accesses = (double)ITERATIONS * 64.0;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "  long array (" << sizeof(long) << " bytes each):\n";
        std::cout << "    Total time:          " << ms << " ms\n";
        std::cout << "    Accesses:            " << std::scientific << std::setprecision(2) << accesses << "\n";
        std::cout << "    Time per access:     " << std::fixed << std::setprecision(4) << (ms / accesses * 1e6) << " ns\n\n";
    }

    // Prevent sink from being optimized away entirely
    if (sink == -999) std::cout << sink;

    std::cout << "========================================================\n";
    std::cout << " Summary\n";
    std::cout << "========================================================\n";
    std::cout << " Bit fields require extra shift/mask operations per\n";
    std::cout << " access, making them slower despite compact storage.\n";
    std::cout << " char/short/long arrays trade memory for simpler access\n";
    std::cout << " patterns that the CPU handles more efficiently.\n";
    std::cout << "========================================================\n";
}

// ============================================================================
// Project 3.2 - Sequential Search vs Binary Search
//
// Implement sequential and binary search, time them on arrays of size
// n = 10^i (i = 1..8), using random search keys. Report a table and
// output CSV data for graphing. Identify the crossover point.
// ============================================================================

// Sequential search: O(n) — scan left to right until found
static int sequential_search(const int* arr, int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

// Binary search: O(log n) — halve the search space each step
static int binary_search(const int* arr, int n, int key) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

static void project_3_2() {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << " Project 3.2 — Sequential vs Binary Search\n";
    std::cout << "========================================================\n";
    std::cout << " Timing both algorithms on sorted arrays of size 10^i.\n";
    std::cout << " Each size uses many random queries for stable averages.\n";
    std::cout << "========================================================\n\n";

    // Random number generator
    std::mt19937 rng(42);

    // We'll test sizes 10^1 through 10^8
    // For each size, we pick a number of queries that gives meaningful timing
    // without making the total runtime too long.
    struct SizeConfig {
        long long n;
        long long num_queries;
    };

    std::vector<SizeConfig> configs = {
        {         10LL, 10'000'000LL },
        {        100LL, 10'000'000LL },
        {      1'000LL, 10'000'000LL },
        {     10'000LL,  5'000'000LL },
        {    100'000LL,  1'000'000LL },
        {  1'000'000LL,    500'000LL },
        { 10'000'000LL,    100'000LL },
        {100'000'000LL,     50'000LL },
    };

    // Storage for results (for CSV output)
    struct Result {
        long long n;
        double seq_ms;
        double bin_ms;
        double seq_per_query_ns;
        double bin_per_query_ns;
    };
    std::vector<Result> results;

    // Table header
    std::cout << std::fixed;
    std::cout << "  " << std::left
              << std::setw(14) << "Array Size"
              << std::setw(14) << "Queries"
              << std::setw(16) << "Seq Total(ms)"
              << std::setw(16) << "Bin Total(ms)"
              << std::setw(16) << "Seq/query(ns)"
              << std::setw(16) << "Bin/query(ns)"
              << "Winner"
              << "\n";
    std::cout << "  " << std::string(108, '-') << "\n";

    volatile int sink = 0;

    for (auto& cfg : configs) {
        long long n = cfg.n;
        long long nq = cfg.num_queries;

        // Build sorted array [0, 1, 2, ..., n-1]
        std::vector<int> arr(n);
        for (long long i = 0; i < n; i++) arr[i] = (int)i;

        // Generate random query keys in [0, n-1]
        std::uniform_int_distribution<int> dist(0, (int)(n - 1));
        std::vector<int> queries(nq);
        for (long long i = 0; i < nq; i++) queries[i] = dist(rng);

        // ---- Time sequential search ----
        double seq_ms;
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (long long q = 0; q < nq; q++) {
                sink = sequential_search(arr.data(), (int)n, queries[q]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            seq_ms = std::chrono::duration<double, std::milli>(end - start).count();
        }

        // ---- Time binary search ----
        double bin_ms;
        {
            auto start = std::chrono::high_resolution_clock::now();
            for (long long q = 0; q < nq; q++) {
                sink = binary_search(arr.data(), (int)n, queries[q]);
            }
            auto end = std::chrono::high_resolution_clock::now();
            bin_ms = std::chrono::duration<double, std::milli>(end - start).count();
        }

        double seq_ns = (seq_ms * 1e6) / (double)nq;
        double bin_ns = (bin_ms * 1e6) / (double)nq;
        const char* winner = (seq_ns < bin_ns) ? "Sequential" : "Binary";

        std::cout << "  " << std::left
                  << std::setw(14) << n
                  << std::setw(14) << nq
                  << std::setw(16) << std::setprecision(2) << seq_ms
                  << std::setw(16) << std::setprecision(2) << bin_ms
                  << std::setw(16) << std::setprecision(2) << seq_ns
                  << std::setw(16) << std::setprecision(2) << bin_ns
                  << winner
                  << "\n";

        results.push_back({n, seq_ms, bin_ms, seq_ns, bin_ns});
    }

    // Prevent sink from being optimized away
    if (sink == -999) std::cout << sink;

    // ---- Write CSV for graphing ----
    std::string csv_path = "project_3_2_results.csv";
    std::ofstream csv(csv_path);
    if (csv.is_open()) {
        csv << "array_size,sequential_ns_per_query,binary_ns_per_query\n";
        for (auto& r : results) {
            csv << r.n << ","
                << std::fixed << std::setprecision(2) << r.seq_per_query_ns << ","
                << std::fixed << std::setprecision(2) << r.bin_per_query_ns << "\n";
        }
        csv.close();
        std::cout << "\n  Results written to: " << csv_path << "\n";
    }

    // ---- Analysis ----
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << " Analysis\n";
    std::cout << "========================================================\n";

    // Find crossover point
    long long crossover = -1;
    for (size_t i = 0; i < results.size(); i++) {
        if (results[i].bin_per_query_ns < results[i].seq_per_query_ns) {
            crossover = results[i].n;
            break;
        }
    }

    std::cout << " Sequential search is O(n): time grows linearly with n.\n";
    std::cout << " Binary search is O(log n): time grows logarithmically.\n";
    std::cout << "\n";
    if (crossover > 0) {
        std::cout << " Binary search becomes faster at n = " << crossover << ".\n";
        std::cout << " For very small arrays, sequential search wins because\n";
        std::cout << " it has no overhead from computing midpoints and has\n";
        std::cout << " better cache/branch-prediction behavior.\n";
    } else {
        std::cout << " Sequential search was faster at all tested sizes.\n";
        std::cout << " (This is unusual — try larger array sizes.)\n";
    }
    std::cout << "========================================================\n";
}

// ============================================================================
// Project 3.3 - Fibonacci: Recursive vs Iterative
//
// Compare the running times of the recursive and iterative Fibonacci
// functions from Exercise 2.11 for n = 1..46 (largest value fitting in
// a long). The recursive version is O(2^n), the iterative is O(n).
// Output a table and CSV for graphing.
// ============================================================================

// Recursive Fibonacci generator — O(2^n) exponential time
// fibr(46) is the largest value that fits in a long
static long fibr(int n) {
    assert((n > 0) && (n < 47) && "Input out of range");
    if ((n == 1) || (n == 2)) return 1;   // Base cases
    return fibr(n - 1) + fibr(n - 2);     // Recursion
}

// Iterative Fibonacci generator — O(n) linear time
// fibi(46) is the largest value that fits in a long
static long fibi(int n) {
    assert((n > 0) && (n < 47) && "Input out of range");
    long past, prev, curr;
    past = prev = curr = 1;               // initialize
    for (int i = 3; i <= n; i++) {         // Compute next value
        past = prev;                       // past holds fibi(i-2)
        prev = curr;                       // prev holds fibi(i-1)
        curr = past + prev;               // curr now holds fibi(i)
    }
    return curr;
}

static void project_3_3() {
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << " Project 3.3 — Fibonacci: Recursive vs Iterative\n";
    std::cout << "========================================================\n";
    std::cout << " Timing fibr(n) [O(2^n)] vs fibi(n) [O(n)].\n";
    std::cout << " Recursive is only run for small n (it gets very slow).\n";
    std::cout << "========================================================\n\n";

    // We run the iterative version for n = 1..46.
    // We run the recursive version for n = 1..MAX_RECURSIVE_N.
    // Beyond ~40-42 the recursive version takes minutes/hours.
    const int MAX_N = 46;
    const int MAX_RECURSIVE_N = 42; // ~1-2 seconds at n=42

    // For small n, we repeat many times to get measurable timings.
    // For the recursive version at large n, one call is enough.

    struct Result {
        int n;
        double recursive_us;  // microseconds
        double iterative_us;
        long fib_value;
    };
    std::vector<Result> results;

    // Table header
    std::cout << std::fixed;
    std::cout << "  " << std::left
              << std::setw(6)  << "n"
              << std::setw(22) << "Fib(n)"
              << std::setw(20) << "Recursive (us)"
              << std::setw(20) << "Iterative (us)"
              << "Ratio (R/I)"
              << "\n";
    std::cout << "  " << std::string(80, '-') << "\n";

    volatile long sink = 0;

    for (int n = 1; n <= MAX_N; n++) {
        double rec_us = -1.0;
        double iter_us = 0.0;

        // --- Iterative timing ---
        // For small n, repeat many times to get meaningful measurements
        {
            long long reps;
            if (n <= 10)      reps = 10'000'000LL;
            else if (n <= 30) reps = 1'000'000LL;
            else              reps = 100'000LL;

            auto start = std::chrono::high_resolution_clock::now();
            for (long long r = 0; r < reps; r++) {
                sink = fibi(n);
            }
            auto end = std::chrono::high_resolution_clock::now();
            double total_us = std::chrono::duration<double, std::micro>(end - start).count();
            iter_us = total_us / (double)reps;
        }

        // --- Recursive timing ---
        if (n <= MAX_RECURSIVE_N) {
            // Adjust repetitions: for small n many reps, for large n just a few
            long long reps;
            if (n <= 15)      reps = 1'000'000LL;
            else if (n <= 20) reps = 100'000LL;
            else if (n <= 25) reps = 10'000LL;
            else if (n <= 30) reps = 1'000LL;
            else if (n <= 35) reps = 100LL;
            else if (n <= 38) reps = 10LL;
            else              reps = 1LL;

            auto start = std::chrono::high_resolution_clock::now();
            for (long long r = 0; r < reps; r++) {
                sink = fibr(n);
            }
            auto end = std::chrono::high_resolution_clock::now();
            double total_us = std::chrono::duration<double, std::micro>(end - start).count();
            rec_us = total_us / (double)reps;
        }

        long fib_val = fibi(n);

        // Print row
        std::cout << "  " << std::left << std::setw(6) << n
                  << std::setw(22) << fib_val;

        if (rec_us >= 0) {
            std::cout << std::setw(20) << std::setprecision(3) << rec_us;
        } else {
            std::cout << std::setw(20) << "--- (skipped)";
        }

        std::cout << std::setw(20) << std::setprecision(3) << iter_us;

        if (rec_us >= 0 && iter_us > 0) {
            std::cout << std::setprecision(1) << (rec_us / iter_us) << "x";
        } else {
            std::cout << "---";
        }
        std::cout << "\n";

        results.push_back({n, rec_us, iter_us, fib_val});
    }

    // Prevent sink from being optimized away
    if (sink == -999) std::cout << sink;

    // ---- Write CSV for graphing ----
    std::string csv_path = "project_3_3_results.csv";
    std::ofstream csv(csv_path);
    if (csv.is_open()) {
        csv << "n,fib_value,recursive_us,iterative_us\n";
        for (auto& r : results) {
            csv << r.n << "," << r.fib_value << ",";
            if (r.recursive_us >= 0)
                csv << std::fixed << std::setprecision(3) << r.recursive_us;
            else
                csv << "";
            csv << "," << std::fixed << std::setprecision(3) << r.iterative_us << "\n";
        }
        csv.close();
        std::cout << "\n  Results written to: " << csv_path << "\n";
    }

    // ---- Analysis ----
    std::cout << "\n";
    std::cout << "========================================================\n";
    std::cout << " Analysis\n";
    std::cout << "========================================================\n";
    std::cout << " The recursive Fibonacci has O(2^n) time complexity.\n";
    std::cout << " Each call spawns two sub-calls, leading to exponential\n";
    std::cout << " growth. At n=42 it already takes seconds.\n";
    std::cout << "\n";
    std::cout << " The iterative Fibonacci has O(n) time complexity.\n";
    std::cout << " It uses a simple loop with three variables, completing\n";
    std::cout << " in nanoseconds even for n=46.\n";
    std::cout << "\n";
    std::cout << " The ratio (recursive/iterative) grows exponentially,\n";
    std::cout << " showing the dramatic cost of redundant recomputation\n";
    std::cout << " in the naive recursive approach.\n";
    std::cout << "========================================================\n";
}

// ============================================================================
// Main — menu to select which project to run
// ============================================================================

int main() {
    std::cout << "========================================================\n";
    std::cout << " Chapter 3 — Projects\n";
    std::cout << "========================================================\n";
    std::cout << "  [1] Project 3.1 — Boolean Access Time Comparison\n";
    std::cout << "  [2] Project 3.2 — Sequential vs Binary Search\n";
    std::cout << "  [3] Project 3.3 — Fibonacci: Recursive vs Iterative\n";
    std::cout << "  [0] Exit\n";
    std::cout << "========================================================\n";
    std::cout << " Select project: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            project_3_1();
            break;
        case 2:
            project_3_2();
            break;
        case 3:
            project_3_3();
            break;
        case 0:
            std::cout << "Exiting.\n";
            return 0;
        default:
            std::cout << "Invalid selection.\n";
            return 1;
    }

    return 0;
}
