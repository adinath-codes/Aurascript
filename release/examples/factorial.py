import time
start_time = time.perf_counter()
num = 20
result = 1

print("--- Factorial of 20 ---")

while num > 0:
    result = result * num
    num = num - 1

print(result)
end_time = time.perf_counter()
ms_runtime = (end_time - start_time) * 1000
print(f"\n[PYTHON ENGINE]: Process finished in {ms_runtime:.4f}ms.")