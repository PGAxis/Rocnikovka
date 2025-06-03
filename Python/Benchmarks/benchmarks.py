import time
import os
import random
import heapq
import re
import numpy as np


# Function to measure execution time
def measure_time(fn):
    start = time.time()
    fn()
    return time.time() - start


# Disk Write Benchmark
def disk_write_benchmark():
    path = './benchmark_output.txt'
    lines = []
    for i in range(10_000_000):
        lines.append(f"Benchmark line {i}")
    content = "\n".join(lines)
    duration = measure_time(lambda: open(path, 'w').write(content))
    os.remove(path)
    return duration


# Matrix Multiplication Benchmark
def matrix_multiplication():
    N = 300
    A = np.random.rand(N, N)
    B = np.random.rand(N, N)
    C = np.zeros((N, N))

    def multiply():
        #global C
        for i in range(N):
            for j in range(N):
                for k in range(N):
                    C[i, j] += A[i, k] * B[k, j]

    duration = measure_time(multiply)
    return duration


# Memory Allocation Benchmark
def memory_allocation():
    blocks = []

    def allocate():
        for _ in range(1000):
            blocks.append(bytearray(1024 * 1024))

    duration = measure_time(allocate)
    blocks.clear()
    return duration


# String Processing Benchmark
def string_processing():
    test_string = 'a' * 10_000_000

    def process():
        found = 'aaa' in test_string
        parsed = test_string[1000:2000]
        match = re.search(r'a{10,}', test_string)

    duration = measure_time(process)
    return duration


# Quicksort Benchmark
def quicksort_benchmark():
    arr = [random.randint(0, 10 ** 6) for _ in range(1_000_000)]

    def quicksort(arr):
        arr.sort()

    duration = measure_time(lambda: quicksort(arr))
    return duration


# Dijkstra's Algorithm Benchmark
def dijkstra_benchmark():
    V = 1000
    graph = {i: {} for i in range(V)}
    for i in range(V):
        for j in range(V):
            if i != j and random.random() < 0.01:
                graph[i][j] = random.randint(1, 10)

    def dijkstra(graph, start):
        distances = {vertex: float('infinity') for vertex in graph}
        distances[start] = 0
        pq = [(0, start)]

        while pq:
            current_distance, current_vertex = heapq.heappop(pq)

            if current_distance > distances[current_vertex]:
                continue

            for neighbor, weight in graph[current_vertex].items():
                distance = current_distance + weight

                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    heapq.heappush(pq, (distance, neighbor))

        return distances

    duration = measure_time(lambda: dijkstra(graph, 0))
    return duration


# Main function to run all benchmarks
def run_benchmarks():
    text = ""

    allTimes: list[list] = [[],[],[]]

    for i in range(0,3):
        diskwrite = disk_write_benchmark()
        allTimes[i].append(diskwrite)
        print(f'Disk Write Benchmark: {diskwrite} seconds')

        matrix = matrix_multiplication()
        allTimes[i].append(matrix)
        print(f'Matrix Multiplication Benchmark: {matrix} seconds')

        mem = memory_allocation()
        allTimes[i].append(mem)
        print(f'Memory Allocation Benchmark: {mem} seconds')

        strink = string_processing()
        allTimes[i].append(strink)
        print(f'String Processing Benchmark: {strink} seconds')

        sort = quicksort_benchmark()
        allTimes[i].append(sort)
        print(f'Quicksort Benchmark: {sort} seconds')

        dj_jiskra = dijkstra_benchmark()
        allTimes[i].append(dj_jiskra)
        print(f'Dijkstra Benchmark: {dj_jiskra} seconds')

    avrgTimes: list = []

    for i in range(0,6):
        avrgTimes.append((allTimes[0][i] + allTimes[1][i] + allTimes[2][i]) / 3)

    text = f"Disk write: {avrgTimes[0]} s\nMatrix mult: {avrgTimes[1]} s\nMemory allocation: {avrgTimes[2]} s\nString processing: {avrgTimes[3]} s\nQuck sort: {avrgTimes[4]} s\nDijkstra: {avrgTimes[5]} s\n"

    open("test_results.txt", "w").write(text)


if __name__ == "__main__":
    run_benchmarks()
