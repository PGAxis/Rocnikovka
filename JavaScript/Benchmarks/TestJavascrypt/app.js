const fs = require('fs');
const { performance } = require('perf_hooks');

function measureTime(fn) {
    const start = performance.now();
    fn();
    return performance.now() - start;
}

function diskWriteBenchmark() {
    const path = './benchmark_output.txt';
    const lines = [];
    for (let i = 0; i < 10_000_000; i++) {
        lines.push(`Benchmark line ${i}`);
    }
    const content = lines.join('\n');
    const duration = measureTime(() => {
        fs.writeFileSync(path, content);
    });
    fs.unlinkSync(path); // Clean up
    return duration;
}

function matrixMultiplication() {
    const N = 300;
    const A = Array.from({ length: N }, () => Array.from({ length: N }, () => Math.random()));
    const B = Array.from({ length: N }, () => Array.from({ length: N }, () => Math.random()));
    const C = Array.from({ length: N }, () => Array(N).fill(0));

    return measureTime(() => {
        for (let i = 0; i < N; i++) {
            for (let j = 0; j < N; j++) {
                for (let k = 0; k < N; k++) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
    });
}

function memoryAllocation() {
    let blocks = [];
    const duration = measureTime(() => {
        for (let i = 0; i < 1000; i++) {
            blocks.push(Buffer.alloc(1024 * 1024)); // 1 MB
        }
    });
    blocks = null;
    return duration;
}

function stringBenchmark() {
    const test = 'a'.repeat(10_000_000);
    return measureTime(() => {
        const found = test.includes("aaa");
        const parsed = test.substring(1000, 2000);
        const match = test.match(/a{10}/);
    });
}

function quicksortBenchmark() {
    const arr = Array.from({ length: 1_000_000 }, () => Math.floor(Math.random() * 1_000_000));
    return measureTime(() => {
        arr.sort((a, b) => a - b);
    });
}

function dijkstraBenchmark() {
    const V = 1000;
    const graph = Array.from({ length: V }, () =>
        Array.from({ length: V }, () => Infinity)
    );

    for (let i = 0; i < V; i++) {
        for (let j = 0; j < V; j++) {
            if (i !== j && Math.random() < 0.01) {
                graph[i][j] = Math.floor(Math.random() * 9) + 1;
            }
        }
    }

    function dijkstra(graph, src) {
        const dist = Array(V).fill(Infinity);
        const sptSet = Array(V).fill(false);
        dist[src] = 0;

        for (let count = 0; count < V - 1; count++) {
            let min = Infinity;
            let u = -1;
            for (let v = 0; v < V; v++) {
                if (!sptSet[v] && dist[v] <= min) {
                    min = dist[v];
                    u = v;
                }
            }
            sptSet[u] = true;

            for (let v = 0; v < V; v++) {
                if (!sptSet[v] && graph[u][v] !== Infinity &&
                    dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }

        return dist;
    }

    return measureTime(() => {
        dijkstra(graph, 0);
    });
}

// Run all benchmarks
console.log("Running benchmarks...\n");

const results = {
    diskWrite: diskWriteBenchmark(),
    matrixMult: matrixMultiplication(),
    memoryAlloc: memoryAllocation(),
    stringProc: stringBenchmark(),
    quicksort: quicksortBenchmark(),
    dijkstra: dijkstraBenchmark()
};

for (const [name, time] of Object.entries(results)) {
    console.log(`${name}: ${time.toFixed(2)} ms`);
}

fs.writeFileSync("test_results.txt", Object.entries(results).map(([k, v]) => `${k}: ${v.toFixed(2)} ms`).join('\n'));

require("readline").createInterface({ input: process.stdin, output: process.stdout }).question("Press Enter to exit...", () => process.exit());
