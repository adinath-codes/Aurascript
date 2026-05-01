import time

def run_boss_fight():
    boss_hp = 15000
    my_aura = 0

    print("--- FINAL BOSS FIGHT INITIATED ---")

    while boss_hp > 0:
        if my_aura > 5:
            print("CRITICAL STRIKE!")
            boss_hp -= 4
            my_aura = 0
        else:
            print("Basic Attack...")
            boss_hp -= 2
            my_aura += 3
        
        print("Boss HP remaining:")
        print(boss_hp)
        print("---")

    print("GG NOCAP! BOSS DEFEATED.")

# Measure the time
start_time = time.perf_counter()
run_boss_fight()
end_time = time.perf_counter()

# Convert to milliseconds
ms_runtime = (end_time - start_time) * 1000
print(f"\n[PYTHON ENGINE]: Process finished in {ms_runtime:.4f}ms.")