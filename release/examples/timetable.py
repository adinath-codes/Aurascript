import time
start_time = time.perf_counter()
base = 7
multiplier = 1

print("--- 7 Times Table ---")


# Convert to milliseconds
while multiplier <= 10:
    print(base * multiplier)
    multiplier = multiplier + 1

print("--- DONE ---")
end_time = time.perf_counter()
ms_runtime = (end_time - start_time) * 1000
print(f"\n[PYTHON ENGINE]: Process finished in {ms_runtime:.4f}ms.")