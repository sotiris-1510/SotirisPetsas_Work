# PatternMatching

A C program that searches for a DNA pattern inside a larger DNA sequence, using either brute-force or Karp-Rabin string matching.

**Author:** Sotiris Petsas
**Written:** 10/10/2025

## What it does

Reads a DNA sequence and a pattern from two text files (containing only `a`, `c`, `g`, `t`), then counts how many times the pattern occurs in the sequence — using either:

- **Brute Force (`-bf`)** — checks every position character-by-character
- **Karp-Rabin (`-kr`)** — hashes each window and rehashes incrementally as it slides, avoiding a full character comparison at every position

Both algorithms were verified against each other and against a manual count on the included sample files, and agree exactly.

## How to run

```bash
gcc patternMatching.c -o patternMatching -lm
./patternMatching -bf dnaSequence.txt patSequence.txt
./patternMatching -kr swinefluDNA.txt patSequence.txt
```

Errors are reported for: wrong number of arguments, a file that can't be opened, an unrecognized algorithm flag, a sequence/pattern that's too large (over 512,000 characters), an illegal character in the input, or a pattern longer than the sequence.

## Documentation

This project is set up for [Doxygen](https://www.doxygen.nl/) — `README.dox` is the project's main page, and `Doxyfile` is the Doxygen config (originally `as1.conf`). Generate HTML docs with:

```bash
doxygen Doxyfile
```

## Files

- `patternMatching.c` — the program
- `README.dox` — Doxygen main-page documentation
- `Doxyfile` — Doxygen configuration
- `dnaSequence.txt`, `patSequence.txt` — small sample sequence/pattern pair
- `swinefluDNA.txt` — a larger real-world DNA sequence for testing at scale
