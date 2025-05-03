#include <iostream>
#include <chrono>
#include <iomanip>

int main() {
    int iterations = 1000000000;
    double pi = 0.0;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; i++) {
        if (i % 2 == 0) {
            pi += 1.0 / (2 * i + 1);
        } else {
            pi -= 1.0 / (2 * i + 1);
        }
    }
    pi *= 4;
    auto elapsedTime = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start).count();
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "\nC++ speaking here. Approximation of Pi: " << pi << ", Execution time (ms): " << elapsedTime << "\n" << std::endl;

    return 0;
}