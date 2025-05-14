using System;
using System.Diagnostics;
using System.IO;
using System.Text.RegularExpressions;
using System.Collections.Generic;

namespace Tests
{    
    internal class Program
    {
        static void Main()
        {
            Console.ReadLine();

            TimeSpan diskWrite = DiskWriteBenchmark();
            Console.WriteLine("Disk Write Benchmark: " + diskWrite);

            TimeSpan matrixMult = MatrixMultiplication();
            Console.WriteLine("Matrix Multiplication Benchmark: " + matrixMult);

            TimeSpan memAloc = MemoryAllocation();
            Console.WriteLine("Memory Allocation Benchmark: " + memAloc);

            TimeSpan strBench = StringBenchmark();
            Console.WriteLine("String Processing Benchmark: " + strBench);

            TimeSpan sortBench = QuicksortBenchmark();
            Console.WriteLine("Quicksort Benchmark: " + sortBench);

            TimeSpan dijkstraBench = DijkstraBenchmark();
            Console.WriteLine("Dijkstra Benchmark: " + dijkstraBench);

            string path = "C:\\Users\\Axiss\\Desktop\\CodingLocal\\test_resultsCS2.txt";
            using (var writer = new StreamWriter(path))
            {
                writer.WriteLine("Disk Write: " + diskWrite);
                writer.WriteLine("Matrix Multiplication Benchmark: " + matrixMult);
                writer.WriteLine("Memory Allocation Benchmark: " + memAloc);
                writer.WriteLine("String Processing Benchmark: " + strBench);
                writer.WriteLine("Quicksort Benchmark: " + sortBench);
                writer.WriteLine("Dijkstra Benchmark: " + dijkstraBench);
            }
        }

        static TimeSpan DiskWriteBenchmark()
        {
            string path = "benchmark_output.txt";
            var sw = Stopwatch.StartNew();
            using (var writer = new StreamWriter(path))
            {
                for (int i = 0; i < 10_000_000; i++)
                    writer.WriteLine("Benchmark line " + i);
            }
            sw.Stop();
            File.Delete(path);
            return sw.Elapsed;
        }

        static TimeSpan MatrixMultiplication()
        {
            int N = 300;
            double[,] A = new double[N, N];
            double[,] B = new double[N, N];
            double[,] C = new double[N, N];

            Random rand = new Random();
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                {
                    A[i, j] = rand.NextDouble();
                    B[i, j] = rand.NextDouble();
                }

            var sw = Stopwatch.StartNew();
            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    for (int k = 0; k < N; k++)
                        C[i, j] += A[i, k] * B[k, j];
            sw.Stop();
            return sw.Elapsed;
        }

        static TimeSpan MemoryAllocation()
        {
            var sw = Stopwatch.StartNew();
            List<byte[]> blocks = new List<byte[]>();
            for (int i = 0; i < 1000; i++)
            {
                var block = new byte[1024 * 1024]; // 1 MB
                blocks.Add(block);
            }
            blocks.Clear();
            GC.Collect();
            sw.Stop();
            return sw.Elapsed;
        }

        static TimeSpan StringBenchmark()
        {
            string test = new string('a', 10_000_000);
            var sw = Stopwatch.StartNew();

            bool found = test.Contains("aaa");
            string parsed = test.Substring(1000, 1000);
            var match = Regex.Match(test, @"a{10,}");

            sw.Stop();
            return sw.Elapsed;
        }

        static TimeSpan QuicksortBenchmark()
        {
            int[] arr = new int[1_000_000];
            Random rand = new Random();
            for (int i = 0; i < arr.Length; i++)
                arr[i] = rand.Next();

            var sw = Stopwatch.StartNew();
            Array.Sort(arr);
            sw.Stop();
            return sw.Elapsed;
        }

        static TimeSpan DijkstraBenchmark()
        {
            int V = 1000;
            int[,] graph = new int[V, V];
            Random rand = new Random();

            for (int i = 0; i < V; i++)
                for (int j = 0; j < V; j++)
                    graph[i, j] = (i != j && rand.NextDouble() < 0.01) ? rand.Next(1, 10) : int.MaxValue;

            var sw = Stopwatch.StartNew();
            Dijkstra(graph, 0);
            sw.Stop();
            return sw.Elapsed;
        }

        static int[] Dijkstra(int[,] graph, int src)
        {
            int V = graph.GetLength(0);
            int[] dist = new int[V];
            bool[] sptSet = new bool[V];

            for (int i = 0; i < V; i++)
                dist[i] = int.MaxValue;
            dist[src] = 0;

            for (int count = 0; count < V - 1; count++)
            {
                int u = MinDistance(dist, sptSet);
                sptSet[u] = true;

                for (int v = 0; v < V; v++)
                    if (!sptSet[v] && graph[u, v] != int.MaxValue && dist[u] != int.MaxValue &&
                        dist[u] + graph[u, v] < dist[v])
                        dist[v] = dist[u] + graph[u, v];
            }

            return dist;
        }

        static int MinDistance(int[] dist, bool[] sptSet)
        {
            int min = int.MaxValue, min_index = -1;
            for (int v = 0; v < dist.Length; v++)
                if (!sptSet[v] && dist[v] <= min)
                {
                    min = dist[v];
                    min_index = v;
                }
            return min_index;
        }
    }
}
