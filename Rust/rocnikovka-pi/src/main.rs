use std::time::Instant;

fn main() {
    count_pi();
}

fn count_pi() {
    let iterations: i32 = 1_000_000_000;
    let mut pi: f64 = 0.0;

    let start= Instant::now();
    for i in 0..iterations {
        if i % 2 == 0 {
            pi += 1.0 / (2.0 * i as f64 + 1.0);
        } else {
            pi -= 1.0 / (2.0 * i as f64 + 1.0);
        }
    }
    pi *= 4.0;
    let duration = start.elapsed();

    println!("Rust speaking here. Approximation of Pi: {}, Execution time (ms) {}\n", pi, duration.as_millis());
}