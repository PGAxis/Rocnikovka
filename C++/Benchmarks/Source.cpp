#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <regex>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
using namespace chrono;

void waitForEnter() {
    cout << "Press Enter to start..." << endl;
    cin.get();
}

duration<double> DiskWriteBenchmark() {
    ofstream file("benchmark_output.txt");
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 10'000'000; ++i)
        file << "Benchmark line " << i << "\n";
    file.close();
    remove("benchmark_output.txt");
    return high_resolution_clock::now() - start;
}

duration<double> MatrixMultiplication() {
    const int N = 300;
    vector<vector<double>> A(N, vector<double>(N));
    vector<vector<double>> B(N, vector<double>(N));
    vector<vector<double>> C(N, vector<double>(N, 0));

    srand(time(nullptr));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            A[i][j] = rand() / (double)RAND_MAX;
            B[i][j] = rand() / (double)RAND_MAX;
        }

    auto start = high_resolution_clock::now();
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return high_resolution_clock::now() - start;
}

duration<double> MemoryAllocation() {
    vector<char*> blocks;
    auto start = high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        blocks.push_back(new char[1024 * 1024]); // 1MB
    }
    for (auto b : blocks) delete[] b;
    return high_resolution_clock::now() - start;
}

duration<double> StringBenchmark() {
    string s(10'000'000, 'a');
    auto start = high_resolution_clock::now();
    bool found = s.find("aaa") != string::npos;
    string substr = s.substr(1000, 1000);
    regex re("a{10}");
    smatch match;
    regex_search(s, match, re);
    return high_resolution_clock::now() - start;
}

duration<double> QuicksortBenchmark() {
    vector<int> arr(1'000'000);
    srand(time(nullptr));
    for (auto& val : arr) val = rand();

    auto start = high_resolution_clock::now();
    sort(arr.begin(), arr.end());
    return high_resolution_clock::now() - start;
}

int MinDistance(const vector<int>& dist, const vector<bool>& sptSet) {
    int min = INT_MAX, min_index = -1;
    for (size_t v = 0; v < dist.size(); ++v)
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

vector<int> Dijkstra(const vector<vector<int>>& graph, int src) {
    int V = graph.size();
    vector<int> dist(V, INT_MAX);
    vector<bool> sptSet(V, false);
    dist[src] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = MinDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < V; ++v)
            if (!sptSet[v] && graph[u][v] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    return dist;
}

duration<double> DijkstraBenchmark() {
    const int V = 1000;
    vector<vector<int>> graph(V, vector<int>(V, INT_MAX));
    srand(time(nullptr));

    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            if (i != j && (rand() % 100) < 1)
                graph[i][j] = rand() % 10 + 1;

    auto start = high_resolution_clock::now();
    Dijkstra(graph, 0);
    return high_resolution_clock::now() - start;
}

int main() {
    waitForEnter();

    auto disk = DiskWriteBenchmark();
    cout << "Disk " << disk.count() << endl;
    auto mat = MatrixMultiplication();
    cout << "Matrix " << mat.count() << endl;
    auto mem = MemoryAllocation();
    cout << "Memory " << mem.count() << endl;
    auto str = StringBenchmark();
    cout << "String " << str.count() << endl;
    auto sort = QuicksortBenchmark();
    cout << "Quicksort " << sort.count() << endl;
    auto dijk = DijkstraBenchmark();
    cout << "Dijkstra " << dijk.count() << endl;

    ofstream result("test_results.txt");
    result << "Disk Write: " << disk.count() << "s\n";
    result << "Matrix Multiplication: " << mat.count() << "s\n";
    result << "Memory Allocation: " << mem.count() << "s\n";
    result << "String Benchmark: " << str.count() << "s\n";
    result << "Quicksort Benchmark: " << sort.count() << "s\n";
    result << "Dijkstra Benchmark: " << dijk.count() << "s\n";
    result.close();

    return 0;
}
