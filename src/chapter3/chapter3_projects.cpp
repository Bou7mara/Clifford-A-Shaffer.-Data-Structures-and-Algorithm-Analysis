// ============================================================================
// Chapter 3 - Projects
// From: "Data Structures and Algorithm Analysis" by Clifford A. Shaffer
// ============================================================================

#include <iostream>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iomanip>

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
// Main — menu to select which project to run
// ============================================================================

int main() {
    std::cout << "========================================================\n";
    std::cout << " Chapter 3 — Projects\n";
    std::cout << "========================================================\n";
    std::cout << "  [1] Project 3.1 — Boolean Access Time Comparison\n";
    // Future projects:
    // std::cout << "  [2] Project 3.2 — ...\n";
    // std::cout << "  [3] Project 3.3 — ...\n";
    std::cout << "  [0] Exit\n";
    std::cout << "========================================================\n";
    std::cout << " Select project: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            project_3_1();
            break;
        // case 2:
        //     project_3_2();
        //     break;
        // case 3:
        //     project_3_3();
        //     break;
        case 0:
            std::cout << "Exiting.\n";
            return 0;
        default:
            std::cout << "Invalid selection.\n";
            return 1;
    }

    return 0;
}
