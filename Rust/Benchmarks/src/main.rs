use std::fs::{File, remove_file};
use std::io::{BufWriter, Write};
use std::time::Instant;
use rand::Rng;
use regex::Regex;

fn main() {
    println!("Running Rust Benchmarks...");

    let disk_write = disk_write_benchmark();
    println!("Disk Write Benchmark: {:.2?}", disk_write);

    let matrix_mult = matrix_multiplication_benchmark();
    println!("Matrix Multiplication Benchmark: {:.2?}", matrix_mult);

    let memory_alloc = memory_allocation_benchmark();
    println!("Memory Allocation Benchmark: {:.2?}", memory_alloc);

    let string_proc = string_processing_benchmark();
    println!("String Processing Benchmark: {:.2?}", string_proc);

    let quicksort = quicksort_benchmark();
    println!("Quicksort Benchmark: {:.2?}", quicksort);

    let dijkstra = dijkstra_benchmark();
    println!("Dijkstra Benchmark: {:.2?}", dijkstra);

    // Write results to a file
    let mut file = File::create("test_resultsRust.txt").expect("Unable to create results file");
    writeln!(file, "Disk Write: {:.4?}", disk_write).unwrap();
    writeln!(file, "Matrix Multiplication: {:.4?}", matrix_mult).unwrap();
    writeln!(file, "Memory Allocation: {:.4?}", memory_alloc).unwrap();
    writeln!(file, "String Processing: {:.4?}", string_proc).unwrap();
    writeln!(file, "Quicksort: {:.4?}", quicksort).unwrap();
    writeln!(file, "Dijkstra: {:.4?}", dijkstra).unwrap();
}

fn disk_write_benchmark() -> std::time::Duration {
    let path = "benchmark_output.txt";
    let start = Instant::now();
    let file = File::create(path).unwrap();
    let mut writer = BufWriter::new(file);
    for i in 0..10_000_000 {
        writeln!(writer, "Benchmark line {}", i).unwrap();
    }
    writer.flush().unwrap();
    let duration = start.elapsed();
    remove_file(path).unwrap();
    duration
}

fn matrix_multiplication_benchmark() -> std::time::Duration {
    let size = 300;
    let mut rng = rand::thread_rng();

    let a: Vec<Vec<f64>> = (0..size).map(|_| (0..size).map(|_| rng.gen()).collect()).collect();
    let b: Vec<Vec<f64>> = (0..size).map(|_| (0..size).map(|_| rng.gen()).collect()).collect();
    let mut c = vec![vec![0.0; size]; size];

    let start = Instant::now();
    for i in 0..size {
        for j in 0..size {
            for k in 0..size {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    start.elapsed()
}

fn memory_allocation_benchmark() -> std::time::Duration {
    let mut blocks: Vec<Vec<u8>> = Vec::new();
    let start = Instant::now();
    for _ in 0..1000 {
        blocks.push(vec![0u8; 1024 * 1024]); // 1 MB
    }
    drop(blocks);
    start.elapsed()
}

fn string_processing_benchmark() -> std::time::Duration {
    let s = "a".repeat(10_000_000);
    let start = Instant::now();

    let _contains = s.contains("aaa");
    let _parsed = &s[1000..2000];
    let re = Regex::new(r"a{10,}").unwrap();
    let _match = re.find(&s);

    start.elapsed()
}

fn quicksort_benchmark() -> std::time::Duration {
    let mut rng = rand::thread_rng();
    let mut data: Vec<i32> = (0..1_000_000).map(|_| rng.gen_range(0..1_000_000)).collect();
    let start = Instant::now();
    data.sort_unstable(); // equivalent to Array.Sort in C#
    start.elapsed()
}

fn dijkstra_benchmark() -> std::time::Duration {
    const V: usize = 1000;
    let mut rng = rand::thread_rng();
    let mut graph = vec![vec![None; V]; V];

    for i in 0..V {
        for j in 0..V {
            if i != j && rng.gen_bool(0.01) {
                graph[i][j] = Some(rng.gen_range(1..10));
            }
        }
    }

    let start = Instant::now();
    dijkstra(&graph, 0);
    start.elapsed()
}

fn dijkstra(graph: &Vec<Vec<Option<usize>>>, start: usize) -> Vec<usize> {
    let mut dist = vec![usize::MAX; graph.len()];
    dist[start] = 0;

    let mut visited = vec![false; graph.len()];
    for _ in 0..graph.len() {
        let mut min = usize::MAX;
        let mut u = 0;
        for i in 0..graph.len() {
            if !visited[i] && dist[i] < min {
                min = dist[i];
                u = i;
            }
        }

        visited[u] = true;
        for v in 0..graph.len() {
            if let Some(w) = graph[u][v] {
                if dist[u] != usize::MAX && dist[u] + w < dist[v] {
                    dist[v] = dist[u] + w;
                }
            }
        }
    }
    dist
}
