# Sudoku Solver

**Internship:** CodeAlpha – C++ Programming Internship
**Task:** Task 3 – Sudoku Solver

---

## 1. Project Title
Sudoku Solver using Backtracking (Console-based, C++)

## 2. Objective
To implement a program that solves any valid 9×9 Sudoku puzzle automatically using a backtracking algorithm on a 2D array, respecting all Sudoku rules (row, column, and 3×3 subgrid constraints), as specified in the CodeAlpha task.

## 3. Problem Statement
Solving a Sudoku puzzle by hand can be slow and error-prone for harder puzzles. This program takes a partially-filled 9×9 grid (with 0s for empty cells) and automatically fills in all the missing numbers so the completed grid follows every Sudoku rule.

## 4. Features
- Represents the puzzle as a 2D array (`int grid[9][9]`).
- Solves the puzzle using **recursive backtracking**.
- Validates row, column, and 3×3 subgrid constraints before placing any number.
- Detects and rejects an already-invalid starting puzzle (e.g. duplicate numbers).
- Detects and reports if a puzzle has **no solution**.
- Offers a built-in sample puzzle for a quick demo, or manual entry of a custom puzzle.
- Clean, grid-formatted console output with subgrid separators.

## 5. C++ Concepts Used
- **2D arrays** (`int grid[9][9]`) — exactly as specified in the task.
- **Recursion and backtracking** — the core algorithm.
- Functions with **pass-by-reference** (`int &row, int &col`) to return multiple values.
- Nested loops for row/column/subgrid checking.
- Input validation for grid entries.

## 6. Requirements
- C++17-compatible compiler (e.g. `g++`)
- Terminal / console
- VS Code (recommended)

## 7. Algorithm / Working (Backtracking Explained Simply)
1. **Find an empty cell.** If there isn't one, the puzzle is already solved — done.
2. **Try numbers 1 through 9** in that empty cell, one at a time.
3. For each number, **check if it's valid**: not already used in the same row, same column, or same 3×3 box.
4. If valid, **place it** and **recursively try to solve the rest of the grid**.
5. If the recursive attempt eventually gets stuck (no valid number fits some later cell), **undo (backtrack)** — erase the number just placed and try the next candidate number.
6. If none of 1–9 work in a cell, return `false` so the *previous* call also backtracks and tries a different number.
7. This "try, recurse, undo if it fails" process repeats until the entire grid is filled correctly.

## 8. Complete C++ Source Code
See [`sudoku_solver.cpp`](./sudoku_solver.cpp) in this folder.

## 9. Detailed Explanation of the Code
- **`isValidPlacement()`** checks all three Sudoku constraints (row, column, 3×3 box) for a candidate number at a given cell — this is called before every placement attempt.
- **`findEmptyCell()`** scans the grid top-to-bottom, left-to-right for the next cell containing `0`. If none is found, the grid is complete.
- **`solveSudoku()`** is the recursive backtracking engine: it finds an empty cell, tries digits 1–9, and recurses. If a full solve isn't reachable down a branch, it resets the cell to `0` (backtracks) and tries the next digit.
- **`isInitialGridValid()`** runs before solving to check the *user's original input* doesn't already violate Sudoku rules — this prevents wasting time trying to "solve" an impossible puzzle and gives a clear error instead.
- **`inputGrid()`** reads 9 numbers per row with validation (must be 0–9), or `loadSamplePuzzle()` loads a hardcoded classic puzzle for demo purposes.
- **`printGrid()`** displays the grid with `.` for empty cells and `|`/`-` separators between the 3×3 boxes, matching a real Sudoku's visual layout.

## 10. Sample Input
```
Choice: 2  (Use a sample puzzle)
```
Or manual entry, e.g. row 1: `5 3 0 0 7 0 0 0 0`

## 11. Sample Output
```
Original Puzzle:
5 3 . | . 7 . | . . .
6 . . | 1 9 5 | . . .
. 9 8 | . . . | . 6 .
------+-------+------
8 . . | . 6 . | . . 3
4 . . | 8 . 3 | . . 1
7 . . | . 2 . | . . 6
------+-------+------
. 6 . | . . . | 2 8 .
. . . | 4 1 9 | . . 5
. . . | . 8 . | . 7 9

Solved Puzzle:
5 3 4 | 6 7 8 | 9 1 2
6 7 2 | 1 9 5 | 3 4 8
1 9 8 | 3 4 2 | 5 6 7
------+-------+------
8 5 9 | 7 6 1 | 4 2 3
4 2 6 | 8 5 3 | 7 9 1
7 1 3 | 9 2 4 | 8 5 6
------+-------+------
9 6 1 | 5 3 7 | 2 8 4
2 8 7 | 4 1 9 | 6 3 5
3 4 5 | 2 8 6 | 1 7 9
```
*(This is real output from an actual compiled test run — this solution matches the well-known solved form of this classic puzzle.)*

## 12. Test Cases

| # | Scenario | Expected Result | Actual Result (Tested) |
|---|---|---|---|
| 1 | Classic sample puzzle | Correctly solved, valid grid | ✅ Passed |
| 2 | Invalid starting grid (duplicate 5s in a row) | Rejected with clear error, no solving attempted | ✅ Passed |
| 3 | Non-numeric / out-of-range cell input (e.g. 15) | Row re-prompted until valid | ✅ Passed |
| 4 | Fully empty grid (all 0s) | Solves to any valid completed Sudoku | Logically verified (algorithm guarantees correctness for any solvable grid) |
| 5 | Unsolvable puzzle | Reports "No solution exists" | Logically verified via `solveSudoku()` returning `false` |

## 13. Possible Errors and How to Handle Them
- **Invalid starting puzzle (rule already broken):** Checked upfront with `isInitialGridValid()` before attempting to solve — avoids a misleading "no solution" message when the real issue is bad input.
- **Non-numeric or out-of-range grid values:** `inputGrid()` validates each number is between 0–9 and re-prompts the whole row if not.
- **Unsolvable but validly-entered puzzle:** `solveSudoku()` returns `false` and the program clearly reports "No solution exists" instead of crashing or looping forever.
- **Deep recursion:** Backtracking recursion depth is bounded by the 81 cells of the grid, so stack overflow is not a practical concern for a standard 9×9 Sudoku.

## 14. Advantages
- Solves any valid, uniquely-solvable Sudoku puzzle correctly.
- Demonstrates a real, classic algorithmic technique (backtracking) clearly.
- Validates input thoroughly before solving.
- Simple, readable recursive code — good for explaining step-by-step in a video.

## 15. Limitations
- Console-only; no graphical Sudoku board (the PDF marks a GUI as *optional*, so this is intentionally left out to keep the project focused and beginner-friendly).
- Only supports standard 9×9 Sudoku (not 4×4, 16×16, or irregular variants).
- For puzzles with multiple valid solutions, it returns only the first one it finds (this is standard behavior for basic backtracking solvers).
- Manual row-by-row input can be tedious for a full 9×9 grid — the sample puzzle option exists specifically to make demoing easier.

## 16. Future Enhancements
*(My own recommended additions — not CodeAlpha requirements. The PDF does mention a GUI as an optional idea.)*
- Add a simple GUI (e.g. using a graphics library or a web frontend) for visual input/output, as suggested optionally in the task PDF.
- Add a "load puzzle from file" option instead of manual row entry.
- Add a solve-speed/step counter to show how many backtracks occurred (nice for a video demo).
- Support importing puzzles from an image using OCR (advanced).

## 17. Conclusion
This project fulfills CodeAlpha's Task 3 requirements precisely: a 2D array grid, a backtracking algorithm, full row/column/3×3-box rule checking, and recursive number placement until solved. The optional GUI was intentionally skipped to keep the submission clean and beginner-appropriate, as allowed by the task description. Testing on a classic puzzle confirmed a correct solve.
