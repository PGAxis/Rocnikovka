#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

double calcpi(int iterationsNum, double *elapsedTime) {
    double iterations = iterationsNum;
    double pi = 0.0;

    clock_t start = clock();
    for (int i = 0; i < iterations; i++) {
        if (i % 2 == 0) {
            pi += 1.0 / (2 * i + 1);
        } else {
            pi -= 1.0 / (2 * i + 1);
        }
    }
    pi *= 4;
    *elapsedTime = (double)(clock() - start) / CLOCKS_PER_SEC * 1000;

    //printf("C speaking here. Approximation of Pi: %.15f, Execution time (ms): %.2f\n", pi, elapsedTime);
    //printf("Execution time (ms): %f\n", elapsedTime);

    return pi;
}

int main() {
    double iterations = 1000000000;
    double elapsedTime;
    double pi = 0.0;
    while (true) {
        pi = calcpi(iterations, &elapsedTime);
        printf("C speaking here. Approximation of Pi: %.15f, Execution time (ms): %.2f\n", pi, elapsedTime);

        printf("\nPress any key to exit or press R to repeat\n");

        char choice = getchar();
        while (getchar() != '\n');
        if(tolower(choice) != 'r')
            return 0;
        
        printf("Calculating again...\n");
    }
}
