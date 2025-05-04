function calculatePi(iterations) {
    let pi = 0;
    for (let i = 0; i < iterations; i++) {
        if (i % 2 === 0) {
            pi += 1 / (2 * i + 1);
        } else {
            pi -= 1 / (2 * i + 1);
        }
    }
    return pi * 4;
}

const iterations = 1000000000;
const start = performance.now();
const pi = calculatePi(iterations);
const end = performance.now();

console.log("JavaScript speaking here. Approximation of Pi: " + pi + ", Execution time (ms): " + (end - start));

setTimeout(() => {}, 1000000);
