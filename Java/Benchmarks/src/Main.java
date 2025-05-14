import java.time.Instant;
import java.time.Duration;

import java.io.*;
import java.util.*;
import java.util.regex.*;

public class Main {

    public static void main(String[] args) throws IOException {
        System.out.println("Press Enter to start...");
        var read = System.in.read();

        long[] times1 = new long[6];
        long[] times2 = new long[6];
        long[] times3 = new long[6];

        long[][] allTimes = new long[][] { times1, times2, times3 };

        for(byte i = 0; i < 3; i++)
        {
            long diskWrite = benchmarkDiskWrite();
            System.out.println("Disk Write Benchmark: " + diskWrite + " ms");
            allTimes[i][0] = diskWrite;

            long matrixMult = benchmarkMatrixMultiplication();
            System.out.println("Matrix Multiplication Benchmark: " + matrixMult + " ms");
            allTimes[i][1] = matrixMult;

            long memoryAlloc = benchmarkMemoryAllocation();
            System.out.println("Memory Allocation Benchmark: " + memoryAlloc + " ms");
            allTimes[i][2] = memoryAlloc;

            long stringBench = benchmarkStringProcessing();
            System.out.println("String Processing Benchmark: " + stringBench + " ms");
            allTimes[i][3] = stringBench;

            long quicksortBench = benchmarkQuicksort();
            System.out.println("Quicksort Benchmark: " + quicksortBench + " ms");
            allTimes[i][4] = quicksortBench;

            long dijkstraBench = benchmarkDijkstra();
            System.out.println("Dijkstra Benchmark: " + dijkstraBench + " ms");
            allTimes[i][5] = dijkstraBench;
        }

        long[] avrgTimes = new long[6];

        for(byte i = 0; i < 6; i++)
        {
            avrgTimes[i] = (allTimes[0][i] + allTimes[1][i] + allTimes[2][i]) / 3;
        }

        try (PrintWriter writer = new PrintWriter("C:\\Users\\Axiss\\Desktop\\CodingLocal\\test_resultsJava.txt")) {
            writer.println("Disk Write Benchmark: " + avrgTimes[0] + " ms");
            writer.println("Matrix Multiplication Benchmark: " + avrgTimes[1] + " ms");
            writer.println("Memory Allocation Benchmark: " + avrgTimes[2] + " ms");
            writer.println("String Processing Benchmark: " + avrgTimes[3] + " ms");
            writer.println("Quicksort Benchmark: " + avrgTimes[4] + " ms");
            writer.println("Dijkstra Benchmark: " + avrgTimes[5] + " ms");
        }
    }

    static long benchmarkDiskWrite() throws IOException {
        File file = new File("benchmark_output.txt");
        long start = System.currentTimeMillis();
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            for (int i = 0; i < 10_000_000; i++) {
                writer.write("Benchmark line " + i);
                writer.newLine();
            }
        }
        file.delete();
        return System.currentTimeMillis() - start;
    }

    static long benchmarkMatrixMultiplication() {
        int N = 300;
        double[][] A = new double[N][N];
        double[][] B = new double[N][N];
        double[][] C = new double[N][N];
        Random rand = new Random();

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                A[i][j] = rand.nextDouble();
                B[i][j] = rand.nextDouble();
            }

        long start = System.currentTimeMillis();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    C[i][j] += A[i][k] * B[k][j];
        return System.currentTimeMillis() - start;
    }

    static long benchmarkMemoryAllocation() {
        List<byte[]> blocks = new ArrayList<>();
        long start = System.currentTimeMillis();
        for (int i = 0; i < 1000; i++) {
            blocks.add(new byte[1024 * 1024]); // 1 MB
        }
        blocks.clear();
        System.gc();
        return System.currentTimeMillis() - start;
    }

    static long benchmarkStringProcessing() {
        char[] chars = new char[10_000_000];
        Arrays.fill(chars, 'a');
        String test = new String(chars);

        long start = System.currentTimeMillis();

        boolean contains = test.contains("aaa");
        String parsed = test.substring(1000, 2000);
        Pattern pattern = Pattern.compile("a{10,}");
        Matcher matcher = pattern.matcher(test);
        boolean matched = matcher.find();

        long end = System.currentTimeMillis();
        return end - start;
    }

    static long benchmarkQuicksort() {
        int[] arr = new int[1_000_000];
        Random rand = new Random();
        for (int i = 0; i < arr.length; i++)
            arr[i] = rand.nextInt();

        long start = System.currentTimeMillis();
        Arrays.sort(arr);
        return System.currentTimeMillis() - start;
    }

    static long benchmarkDijkstra() {
        int V = 1000;
        int[][] graph = new int[V][V];
        Random rand = new Random();

        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                graph[i][j] = (i != j && rand.nextDouble() < 0.01) ? rand.nextInt(9) + 1 : Integer.MAX_VALUE;

        long start = System.currentTimeMillis();
        dijkstra(graph, 0);
        return System.currentTimeMillis() - start;
    }

    static int[] dijkstra(int[][] graph, int src) {
        int V = graph.length;
        int[] dist = new int[V];
        boolean[] sptSet = new boolean[V];

        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[src] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = minDistance(dist, sptSet);
            if (u == -1) break;
            sptSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (!sptSet[v] && graph[u][v] != Integer.MAX_VALUE &&
                        dist[u] != Integer.MAX_VALUE &&
                        dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
        return dist;
    }

    static int minDistance(int[] dist, boolean[] sptSet) {
        int min = Integer.MAX_VALUE, minIndex = -1;
        for (int v = 0; v < dist.length; v++) {
            if (!sptSet[v] && dist[v] <= min) {
                min = dist[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
}