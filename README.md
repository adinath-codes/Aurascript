# AuraScript : High-Performance Programming Language for the GENZ
*(Python was popular because its syntax was similar to English during the BOOMER ERA. AuraScript will be popular because its syntax is similar to English during the GENZ ERA)* *The best programming language of the era since it's named after Gen-Z slang.*<br/>
**AURASCRIPT THE** high-performance programming language for the GENZ is faster than Python even though AuraScript is also an interpreted language built with C++. But why?

## AuraScript vs Python

| Feature | AuraScript | Python |
|---|---|---|
| Execution Speed | Sub-millisecond (AST Walker) | ~2-5ms (VM Overhead) |
| Memory Footprint | Tiny (Raw C++ types) | Massive (PyObjects) |
| Startup Time | Instant (Native Binary) | Sluggish (Interpreter Load) |
| Ecosystem | None (You are on your own) | Infinite (PyPI) |

# Table of Contents
1. [Showcase](https://github.com/adinath-codes/Aurascript/tree/main#showcase)
2. [Purpose](https://github.com/adinath-codes/Aurascript/tree/main#purpose)
3. [Features](https://github.com/adinath-codes/Aurascript/tree/main#features)
4. [Installation](https://github.com/adinath-codes/Aurascript/tree/main#installation)
5. [Style Guide](https://github.com/adinath-codes/Aurascript/tree/main#style-guide)

# Showcase
```cpp
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

Actually 2 more are there ig,
- *To be faster than Python*
- *To teach you Gen-Z slang before programming syntax*

Basically, I took some C++ code, and sillyfied it. Here's an example:
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
```cpp
// we still keep logic!!
lowkey health becomes 100 fr
health > 0 {
    health becomes health - 10 fr
}
```

Lastly, rearrange everything and hide the exact control flow statements (`if` -> `sus`)
```cpp
lowkey health becomes 100 fr
sus (health > 0) {
    lowkey health becomes health - 10 fr
}
```

You don't like not having an `else` keyword? Does that make you annoyed? Have a `flop`.
```cpp
lowkey health becomes 100 fr
sus (health > 0) {
    lowkey health becomes health - 10 fr
} flop {
    yap "you are dead fr" fr
}
```

You want to add a loop? And do math? Your greed is insulting.
```cpp
lowkey health becomes 100 fr
keepgrinding (health > 0) {
    lowkey health becomes health - 10 fr
    yap health fr
}
```

If you can't comprehend true and false booleans, you can use the `nocap` and `cap` keywords.
```cpp
lowkey is_alive becomes nocap fr
```

"Oh but how does it know when one statement ends and one begins! I don't have my semicolons!". This system works on hopes and dreams and is flawless. Just say `fr`.
```cpp
lowkey your_iq becomes 5 fr 
lowkey my_iq becomes 200 fr 
lowkey your_iq becomes your_iq - my_iq fr
```

> [!NOTE]
> `fr` is required to guide the AST walker to flush the statement node. Don't forget it!

## More examples
Take some normal C++ code, for example a print statement.
```cpp
int age = 19;
std::cout << "My age is " << age << std::endl;
```
(do everything above)

And done! Ideal AuraScript code!
```cpp
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
```cpp
// this is one of the tests in this project
keepgrinding (boss_hp > 0) {
    lowkey boss_hp becomes boss_hp - 1 fr
}
```

Builtins (from everywhere):
```cpp
yap "hello" fr
```

Parentheses (invented by Lisp):
```cpp
(5 + 5)
```

## If Statements

```cpp
sus (thing) {
    // true logic
} flop {
    // false logic
}
```

> [!NOTE]
> If you want an "else if", you have to nest the `sus` inside the `flop` block. We don't do `elif` here.

## Variables and Printing
Strings and ints share the same syntax, so they are dynamically typed at execution.
```cpp
// THIS IS FINE
lowkey health becomes 100 fr
lowkey slur_count becomes 9857 fr

// REASSIGNING THEM REUSES THE KEYWORD
lowkey health becomes 90 fr
```

Also from literally anywhere, builtins:
`yap`: Uses C++'s memory-mapped string buffering to print instantly.


# Installation

> [!IMPORTANT]
> A Windows machine is recommended to use this project out of the box.
> You do NOT need C++ installed if you use the precompiled binaries.

## Quick Start (Windows)
1. Go to the **Releases** tab on GitHub.
2. Download the `release.zip` archive.
3. Extract the folder to your desktop.
4. Open Command Prompt inside that folder.
5. double-click the `setup.bat` and run it , finally press enter to close when asked to `press any key...`
6. Run the engine directly against the examples:
   ```cmd
   aura examples\demo.aura
   ```

## Examples Included
- `fibonacci.aura`: Calculate a target Fibonacci number
- `factorial.aura`: Calculate a target factorial number
- `timestable.aura`: Prints a 7 times table
- `demo.aura`: A sub-millisecond boss fight simulation. **This is the BIG one you SHOULD TEST.**

# Style Guide
Fuck around and find out or DM me from my profile.
