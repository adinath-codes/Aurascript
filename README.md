# AuraScript : high-performance programming Language for the GENZ

*The best programming language of the era since it's named after Gen-Z slang*
aurascript are faster than python even though aurascript is also an interpreted language build with the same c++.but why?


## AuraScript vs Python

| Feature | AuraScript | Python |
|---|---|---|
| Execution Speed | Sub-millisecond (AST Walker) | ~2-5ms (VM Overhead) |
| Memory Footprint | Tiny (Raw C++ types) | Massive (PyObjects) |
| Startup Time | Instant (Native Binary) | Sluggish (Interpreter Load) |
| Developer Speed | Slow (Write the compiler first) | Instant (Batteries Included) |
| Ecosystem | None (You are on your own) | Infinite (PyPI) |

# Table of Contents
1. [Showcase](https://github.com/adinath-codes/Aurascript/edit/main/README.md#showcase)
2. [Purpose](https://github.com/adinath-codes/Aurascript/edit/main/README.md#purpose)
3. [Features](https://github.com/adinath-codes/Aurascript/edit/main/README.md#features)
4. [Installation](https://github.com/adinath-codes/Aurascript/edit/main/README.md#installation)
5. [Editor Setup](https://github.com/adinath-codes/Aurascript/edit/main/README.md#editor-setup)
6. [Usage](https://github.com/adinath-codes/Aurascript/edit/main/README.md#usage)
7. [Style Guide](https://github.com/adinath-codes/Aurascript/edit/main/README.md#style-guide)

# Showcase
```text
lowkey boss_hp becomes 15 fr
lowkey my_aura becomes 0 fr

yap "--- FINAL BOSS FIGHT INITIATED ---" fr

keepgrinding (boss_hp > 0) {
    sus (my_aura > 5) {
        yap "CRITICAL STRIKE!" fr
        lowkey boss_hp becomes boss_hp - 4 fr
        lowkey my_aura becomes 0 fr
    } flop {
        yap "Basic Attack..." fr
        lowkey boss_hp becomes boss_hp - 2 fr
        lowkey my_aura becomes my_aura + 3 fr
    }
}

yap "GG NOCAP! BOSS DEFEATED." fr
```

# Purpose
AuraScript was made for one reason:
- *The silly factor*

Basically i took some C++ code, and sillyfied it. Heres an example
```cpp
int health = 100;
if (health > 0) {
    health -= 10;
}
```

First, remove anything that doesn't have to be there in order to function. This includes standard types and basic logic.
```cpp
health = 100
health > 0 {
    health -= 10
}
```

Next, replace the variable declarations with absolute brainrot.
```text
// we still keep logic!!
lowkey health becomes 100 fr
health > 0 {
    health becomes health - 10 fr
}
```

Lastly, rearrange everything and hide the exact control flow statements (`if` -> `sus`)
```text
lowkey health becomes 100 fr
sus (health > 0) {
    lowkey health becomes health - 10 fr
}
```

You don't like not having an else keyword? Does that make you annoyed? Have a flop.
```text
lowkey health becomes 100 fr
sus (health > 0) {
    lowkey health becomes health - 10 fr
} flop {
    yap "you are dead fr" fr
}
```

You want to add a loop? And do math? Your greed is insulting.
```text
lowkey health becomes 100 fr
keepgrinding (health > 0) {
    lowkey health becomes health - 10 fr
    yap health fr
}
```

If you're insecure about the size of your math operations, you should be, but also AuraScript is perfect for you!
```text
lowkey health becomes health ----- 10 fr
```

If you can't comprehend true and false booleans, you can use the `nocap` and `cap` keywords.
```text
lowkey is_alive becomes nocap fr
```

"Oh but how does it know when one statement ends and one begins! I don't have my fucking semicolons!". This system works on hopes and dreams and is flawless. Just say `fr`.
```text
lowkey your_iq becomes 5 fr lowkey my_iq becomes 200 fr lowkey your_iq becomes your_iq - my_iq fr
```

But you can add extra `fr`s if you want i guess.
```text
lowkey your_iq becomes 5 fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr fr
```

> [!NOTE]
> `fr` can be used to guide the AST walker since its stupid and needs them to flush the node sometimes :(

## More examples
Take some normal C++ code, for example a print statement.
```cpp
int age = 19;
std::cout << "My age is " << age << std::endl;
```
(do everything above)

And done! Ideal AuraScript code!
```text
lowkey age becomes 19 fr
yap "My age is " fr
yap age fr
```
The Pratt parser will not trust you after this one.

# Features
## Types
- Integers (Standard math)
- Strings (`"like this"`)
- Booleans (`nocap` and `cap`)

These syntax aliases since you'll forget them somehow:
- `lowkey`: `let`, `int`, `var`
- `becomes`: `=`, `->`

## Plagiarized
Some sub-millisecond execution speed you can probably pull off (from C++):
```text
// this is one of the tests in this projects
keepgrinding (boss_hp > 0) {
    lowkey boss_hp becomes boss_hp - 1 fr
}
```

Builtins (from everywhere):
```text
yap "hello" fr
```

Parentheses (invented by Lisp):
```text
(5 + 5)
```

`fr` (invented by Gen Z because i hate semicolons and i hate C++):
```text
// scroll up to the part about fr i hate talking about them more than i need too
```

## If Statements

```text
sus (thing) {
} flop {
}
```


> [!NOTE]
>
> `flop` is required due to technical limitations (AST branching).
> Getting rid of `sus` is fine though. Wait no it isn't. ;)

## Variables and Printing
also strings and ints share the same syntax so they have to be declared in their declaration
```text
// THIS IS FINE
lowkey health becomes 100 fr
lowkey slur_count becomes 9857 fr

// THIS WONT WORK
health = 100
slur_count = 9001

// I THINK REASSIGNING THEM IS FINE THOUGH
lowkey health becomes 90 fr
```

Also from literally anywhere, builtins:
`yap`: Uses C++'s memory-mapped string buffering to print instantly.

## the AST walker is begging for its dear life
Basically anytime you see something that doesn't need to be there you can probably remove it. Or add extra.
```text
// example: math operators
lowkey my_math becomes 5 ++++++++++ 5 fr
```

## Voiding Values
When you do logic, it's sub-millisecond. If you don't need the terminal to lag, just buffer it:
```text
yap "It prints instantly because I bypassed std::cout" fr
```


# Installation

> [!IMPORTANT]
> A Windows machine is recommended to use this project out of the box.
> You do NOT need C++ installed if you use the precompiled binaries.

## Windows
1. Go to the latest release on GitHub.
2. Download the `release.zip` archive.
3. Extract the folder to a permanent location.
4. run the setup.bat (double click it)
5. **Option A: Run from current directory**
	```powershell
	aura examples\demogame.aura
   ```

## Examples
- `fibonacci.aura`: Calculate a target fibonacci number
- `factorial.aura`: Calculate a target factorial number
- `timetable.aura`: Prints a 7 times table
- `demo.aura`: A sub-millisecond boss fight simulation, this is the BIG one you SHOULD TEST


# Style Guide
fuck around and find out
