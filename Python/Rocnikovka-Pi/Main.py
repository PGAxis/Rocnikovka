from datetime import datetime

def calculate_pi(iterations):
    pi = 0.0
    start_time = datetime.now()
    for i in range(iterations):
        if i % 2 == 0:
            pi += 1 / (2 * i + 1)
        else:
            pi -= 1 / (2 * i + 1)
    pi *= 4
    current_time = datetime.now()
    timeItTook = current_time - start_time
    return pi, timeItTook

iterations = 1_000_000_000
pi, TakenTime = calculate_pi(iterations)
print(f"Approximation of Pi: {pi}, time it took to calculate: {TakenTime}")
