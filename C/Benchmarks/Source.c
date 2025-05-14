#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define MATRIX_SIZE 300
#define ARRAY_SIZE 1000000
#define MAX_VERTICES 1000

double benchmark_disk_write() {
    FILE* fp = fopen("benchmark_output.txt", "w");
    if (!fp) return -1;

    clock_t start = clock();
    for (int i = 0; i < 10000000; i++) {
        fprintf(fp, "Benchmark line %d\n", i);
    }
    fclose(fp);
    remove("benchmark_output.txt");
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double benchmark_matrix_mult() {
    double A[MATRIX_SIZE][MATRIX_SIZE];
    double B[MATRIX_SIZE][MATRIX_SIZE];
    double C[MATRIX_SIZE][MATRIX_SIZE] = { 0 };

    srand((unsigned int)time(NULL));
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = rand() / (double)RAND_MAX;
            B[i][j] = rand() / (double)RAND_MAX;
        }

    clock_t start = clock();
    for (int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            for (int k = 0; k < MATRIX_SIZE; k++)
                C[i][j] += A[i][k] * B[k][j];

    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double benchmark_memory_alloc() {
    char* blocks[1000];

    clock_t start = clock();
    for (int i = 0; i < 1000; i++) {
        blocks[i] = (char*)malloc(1024 * 1024); // 1MB
    }

    for (int i = 0; i < 1000; i++) {
        free(blocks[i]);
    }

    return (double)(clock() - start) / CLOCKS_PER_SEC;
}

double benchmark_string() {
    char* str = (char*)malloc(10000001);
    memset(str, 'a', 10000000);
    str[10000000] = '\0';

    clock_t start = clock();

    bool found = false;
    for (int i = 0; i < 10000000 - 2; i++) {
        if (str[i] == 'a' && str[i + 1] == 'a' && str[i + 2] == 'a') {
            found = true;
            break;
        }
    }

    char buffer[1001];
    strncpy_s(buffer, sizeof(buffer), str + 1000, 1000);
    buffer[1000] = '\0';

    int maxStreak = 0, currentStreak = 0;
    for (int i = 0; i < 10000000; i++) {
        if (str[i] == 'a') {
            currentStreak++;
            if (currentStreak >= 10) {
                maxStreak = currentStreak;
                break;
            }
        }
        else {
            currentStreak = 0;
        }
    }

    clock_t end = clock();
    free(str);

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

double benchmark_quicksort() {
    int* arr = (int*)malloc(sizeof(int) * ARRAY_SIZE);
    srand((unsigned int)time(NULL));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand();
    }

    clock_t start = clock();
    qsort(arr, ARRAY_SIZE, sizeof(int), compare_ints);
    clock_t end = clock();

    free(arr);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int min_distance(int dist[], bool sptSet[], int V) {
    int min = INT_MAX, min_index = -1;
    for (int v = 0; v < V; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX_VERTICES][MAX_VERTICES], int src, int dist[MAX_VERTICES], int V) {
    bool sptSet[MAX_VERTICES] = { false };

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = min_distance(dist, sptSet, V);
        if (u == -1) break;
        sptSet[u] = true;

        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph[u][v] != INT_MAX && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

double benchmark_dijkstra() {
    int graph[MAX_VERTICES][MAX_VERTICES];
    int dist[MAX_VERTICES];
    int V = MAX_VERTICES;
    srand((unsigned int)time(NULL));

    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = (i != j && (rand() % 100 < 1)) ? (rand() % 10 + 1) : INT_MAX;

    clock_t start = clock();
    dijkstra(graph, 0, dist, V);
    clock_t end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    printf("Press Enter to start...\n");
    getchar();

    double string = benchmark_string();
    printf("String Processing Benchmark: %.55f s\n", string);
    double quicksort = benchmark_quicksort();
    printf("Quicksort Benchmark: %.3f s\n", quicksort);
    double dijkstra_time = benchmark_dijkstra();
    printf("Dijkstra Benchmark: %.3f s\n", dijkstra_time);

    FILE* out = fopen("C:\\Users\\Axiss\\Desktop\\CodingLocal\\test_resultsC3.txt", "w");
    if (out) {
        fprintf(out, "String Processing Benchmark: %.3f s\n", string);
        fprintf(out, "Quicksort Benchmark: %.3f s\n", quicksort);
        fprintf(out, "Dijkstra Benchmark: %.3f s\n", dijkstra_time);
        fclose(out);
    }

    return 0;
}
