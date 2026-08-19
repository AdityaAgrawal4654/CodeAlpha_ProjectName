/*
    Project     : Sudoku Solver
    Internship  : CodeAlpha - C++ Programming
    Description : Solves a 9x9 Sudoku puzzle using a backtracking algorithm.
                   The grid is represented as a 2D array where 0 means an
                   empty cell. The program checks row, column and 3x3
                   subgrid constraints before placing each number.
*/

#include <iostream>
#include <iomanip>

using namespace std;

const int SIZE = 9;      // Standard Sudoku grid is 9x9
const int EMPTY = 0;     // 0 represents an empty cell

// Prints the Sudoku grid in a readable format with subgrid separators.
void printGrid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        if (row % 3 == 0 && row != 0) {
            cout << "------+-------+------\n";
        }
        for (int col = 0; col < SIZE; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << "| ";
            }
            if (grid[row][col] == EMPTY) {
                cout << ". ";
            } else {
                cout << grid[row][col] << " ";
            }
        }
        cout << "\n";
    }
}

// Checks whether placing 'num' at grid[row][col] follows Sudoku rules:
// the number must not already exist in the same row, column, or 3x3 box.
bool isValidPlacement(int grid[SIZE][SIZE], int row, int col, int num) {
    // Check the row
    for (int c = 0; c < SIZE; c++) {
        if (grid[row][c] == num) {
            return false;
        }
    }

    // Check the column
    for (int r = 0; r < SIZE; r++) {
        if (grid[r][col] == num) {
            return false;
        }
    }

    // Check the 3x3 subgrid that contains (row, col)
    int boxRowStart = (row / 3) * 3;
    int boxColStart = (col / 3) * 3;
    for (int r = boxRowStart; r < boxRowStart + 3; r++) {
        for (int c = boxColStart; c < boxColStart + 3; c++) {
            if (grid[r][c] == num) {
                return false;
            }
        }
    }

    return true;
}

// Finds the next empty cell (marked with EMPTY/0) in the grid.
// Returns true and sets row/col if an empty cell is found.
// Returns false if the grid is completely filled (puzzle solved).
bool findEmptyCell(int grid[SIZE][SIZE], int &row, int &col) {
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if (grid[row][col] == EMPTY) {
                return true;
            }
        }
    }
    return false;
}

// The core backtracking algorithm:
// 1. Find an empty cell. If none exists, the puzzle is solved.
// 2. Try numbers 1-9 in that cell.
// 3. If a number is valid, place it and recursively try to solve the rest.
// 4. If the recursive call fails, undo the placement (backtrack) and try
//    the next number.
// 5. If no number from 1-9 works, return false to trigger backtracking
//    in the previous call.
bool solveSudoku(int grid[SIZE][SIZE]) {
    int row, col;

    if (!findEmptyCell(grid, row, col)) {
        return true; // No empty cells left -> puzzle solved
    }

    for (int num = 1; num <= 9; num++) {
        if (isValidPlacement(grid, row, col, num)) {
            grid[row][col] = num; // Place the number (try it)

            if (solveSudoku(grid)) {
                return true; // Successfully solved with this placement
            }

            grid[row][col] = EMPTY; // Backtrack: undo and try next number
        }
    }

    return false; // No valid number works here -> trigger backtracking
}

// Validates that the initial puzzle itself does not already break any
// Sudoku rule (e.g. duplicate numbers already placed by the user).
bool isInitialGridValid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int num = grid[row][col];
            if (num == EMPTY) continue;

            // Temporarily clear the cell so isValidPlacement can check
            // whether this number conflicts with the rest of the grid.
            grid[row][col] = EMPTY;
            bool valid = isValidPlacement(grid, row, col, num);
            grid[row][col] = num;

            if (!valid) {
                return false;
            }
        }
    }
    return true;
}

// Reads a 9x9 grid from the user, row by row (9 numbers per row,
// space-separated, using 0 for empty cells). Validates each entry is 0-9.
void inputGrid(int grid[SIZE][SIZE]) {
    cout << "Enter the Sudoku puzzle row by row.\n";
    cout << "Use 0 for empty cells. Enter 9 numbers per row separated by spaces.\n\n";

    for (int row = 0; row < SIZE; row++) {
        while (true) {
            cout << "Row " << (row + 1) << ": ";
            bool rowValid = true;
            int tempRow[SIZE];

            for (int col = 0; col < SIZE; col++) {
                if (!(cin >> tempRow[col]) || tempRow[col] < 0 || tempRow[col] > 9) {
                    rowValid = false;
                    cin.clear();
                    cin.ignore(10000, '\n');
                    break;
                }
            }

            if (!rowValid) {
                cout << "Invalid row. Please enter exactly 9 numbers between 0 and 9.\n";
                continue;
            }

            for (int col = 0; col < SIZE; col++) {
                grid[row][col] = tempRow[col];
            }
            break;
        }
    }
}

// Loads a built-in sample puzzle (useful for a quick demo without manual entry).
void loadSamplePuzzle(int grid[SIZE][SIZE]) {
    int sample[SIZE][SIZE] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    for (int r = 0; r < SIZE; r++)
        for (int c = 0; c < SIZE; c++)
            grid[r][c] = sample[r][c];
}

int main() {
    int grid[SIZE][SIZE];
    int choice;

    cout << "=========================================\n";
    cout << "         SUDOKU SOLVER (CodeAlpha)        \n";
    cout << "=========================================\n";
    cout << "1. Enter my own puzzle\n";
    cout << "2. Use a sample puzzle (for quick demo)\n";
    cout << "Enter your choice (1-2): ";
    cin >> choice;

    if (choice == 1) {
        inputGrid(grid);
    } else {
        loadSamplePuzzle(grid);
        cout << "\nSample puzzle loaded.\n";
    }

    cout << "\nOriginal Puzzle:\n";
    printGrid(grid);

    if (!isInitialGridValid(grid)) {
        cout << "\nError: The entered puzzle already breaks Sudoku rules ";
        cout << "(a number repeats in a row, column, or 3x3 box).\n";
        cout << "Please restart the program and check your input.\n";
        return 1;
    }

    cout << "\nSolving...\n";
    if (solveSudoku(grid)) {
        cout << "\nSolved Puzzle:\n";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the given puzzle.\n";
    }

    return 0;
}
