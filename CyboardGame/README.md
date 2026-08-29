# CyboardGame

A console-based grid game where two players place and then move pawns ('X'/'O') on a board, trying to line up a full row or column.

**Author:** Sotiris Petsas
**Written:** 17/11/2024

## What it does

The game has two stages:

1. **Placement stage** — each player takes turns placing their pawn on any empty cell, until every player has placed one pawn per row (`boardsize` pawns each).
2. **Movement stage** — players alternate turns sliding a pawn one step (up/down/left/right) into an adjacent empty cell, trying to get all their pawns to line up in a single row or column. If a player has no legal moves available, they lose their turn.

Only **Human vs Human** mode is implemented. Human vs Computer and Computer vs Computer are listed in the menu but not yet built, and there's no graphical version — it's entirely console-based.

## Classes

- `Position` — a simple (row, column) pair
- `Cell` — a single board square; holds a pawn character or is empty
- `Board` — the grid of cells; handles placing, moving, printing, and win-checking
- `Player` — prompts a human player for input and validates their moves
- `Game` — runs the placement and movement stages, alternating turns until someone wins
- `TestGame` — entry point; asks for game mode and board size (3–5), then starts the game

## Dependencies

Uses Princeton's `StdIn` (from `stdlib.jar`) for reading console input. Grab it from [Princeton's introcs library](https://introcs.cs.princeton.edu/java/stdlib/) and add it to your classpath.

## How to run

```bash
cd src
javac -cp .:stdlib.jar *.java
java -cp .:stdlib.jar TestGame
```

(On Windows PowerShell, use `;` instead of `:` in the classpath.)

You'll be prompted for a game mode (choose `1` for Human vs Human) and a board size between 3 and 5.
