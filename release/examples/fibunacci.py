import time
start_time = time.perf_counter()
n = 10
a = 0
b = 1

print("--- Fibonacci Sequence ---")

while n > 0:
    print(a)
    temp = a + b
    a = b
    b = temp
    n = n - 1

end_time = time.perf_counter()
ms_runtime = (end_time - start_time) * 1000
print(f"\n[PYTHON ENGINE]: Process finished in {ms_runtime:.4f}ms.")