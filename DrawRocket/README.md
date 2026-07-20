# DrawRocket

My very first university project — a Java console program that draws an ASCII-art rocket, built with `for` loops and `if` statements.

**Author:** Sotiris Petsas
**Written:** 01/10/2024

## What it does

The program takes two command-line arguments:
1. An integer, which controls the size of the rocket.
2. A flag (`0` or `1`) — if set to `1`, random `#` glitches are sprinkled into the drawing for a bit of visual noise.

It then prints the rocket in four pieces:
- A pyramid shape used for the nose and base
- A horizontal divider line
- Two upward-facing pyramid segments
- Two downward-facing pyramid segments

The loops calculate exactly where each piece needs to be printed based on the input size.

## How to run

This started as an Eclipse project (the `.project`/`.classpath`/`.settings` files are kept for that), but it can also be compiled and run from the command line:

```bash
cd src
javac DrawRocket.java
java DrawRocket <size> <flag>
```

For example:

```bash
java DrawRocket 3 1
```
