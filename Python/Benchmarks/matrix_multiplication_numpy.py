import numpy as np
import time

def measure_time(fn):
    start = time.time()
    fn()
    return time.time() - start

def matrix_multiplication():
    N = 300
    A = np.random.rand(N, N)
    B = np.random.rand(N, N)

    def multiply():
        C = np.dot(A, B)

    duration = measure_time(multiply)
    return duration

print(f"Matrix multiplication using NumPy: {matrix_multiplication()} s")   # Matrix multiplication using NumPy: 0.0019752979278564453 s
