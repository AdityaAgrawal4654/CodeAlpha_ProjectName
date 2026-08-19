# CGPA Calculator

**Internship:** CodeAlpha – C++ Programming Internship
**Task:** Task 1 – CGPA Calculator

---

## 1. Project Title
CGPA Calculator (Console-based, C++)

## 2. Objective
To build a console application that calculates a student's Grade Point Average (GPA) for each semester and their overall Cumulative Grade Point Average (CGPA) across multiple semesters, based on grades and credit hours entered by the user.

## 3. Problem Statement
Manually calculating CGPA across multiple semesters and courses is repetitive and error-prone. This program automates the process: it collects course-wise grades and credit hours, computes semester GPA, and combines all semesters into a final CGPA — while validating every input along the way.

## 4. Features
- Supports multiple semesters and a variable number of courses per semester.
- Converts letter grades (A, B, C, D, F) into standard 4.0-scale grade points.
- Calculates **Quality Points** (grade point × credit hours) per course.
- Calculates **Semester GPA** and **Overall CGPA**.
- Displays a clean, formatted table for each semester's report.
- Validates all user input (rejects negative numbers, non-numeric entries, and invalid grades).

## 5. C++ Concepts Used
- `struct` for grouping related data (a `Course`)
- Functions and modular program design
- Loops (`for`, `while`) and conditionals
- Vectors (`std::vector`) for dynamic-sized course lists
- Input validation using `cin.fail()` and stream state handling
- `iomanip` for formatted table output (`setw`, `setprecision`, `fixed`)
- Pass-by-reference (`&`) to return multiple values from a function

## 6. Requirements
- A C++ compiler supporting C++17 (e.g. `g++`)
- Any OS (Windows/Linux/Mac) with a terminal
- VS Code (recommended) or any C++ IDE

## 7. Algorithm / Working
1. Ask the user how many semesters to calculate.
2. For each semester:
   a. Ask how many courses were taken.
   b. For each course, take the course name, grade (A–F), and credit hours.
   c. Convert the grade to a grade point (A=4, B=3, C=2, D=1, F=0).
   d. Calculate Quality Points = grade point × credit hours.
3. After all courses in a semester are entered, calculate:
   `Semester GPA = (sum of Quality Points) / (sum of Credit Hours)`
4. Add the semester's totals to running overall totals.
5. After all semesters are processed, calculate:
   `Overall CGPA = (total Quality Points across all semesters) / (total Credit Hours across all semesters)`
6. Display the final CGPA.

## 8. Complete C++ Source Code
See [`cgpa_calculator.cpp`](./cgpa_calculator.cpp) in this folder.

## 9. Detailed Explanation of the Code
- **`gradeToPoint()`** converts a letter grade into its numeric value on a 4.0 scale. Returns `-1` for invalid grades so the caller can detect bad input.
- **`readPositiveInt()` / `readPositiveDouble()` / `readValidGrade()`** are reusable input functions that loop until the user provides valid data — this is what makes the program "crash-proof" against bad input like letters typed where a number is expected.
- **`inputSemesterCourses()`** collects all course data for one semester and returns it as a `vector<Course>`.
- **`displaySemesterReport()`** prints a formatted table of that semester's courses and returns the semester's GPA, while also passing back the semester's total credits and quality points (via reference parameters) so `main()` can add them to the running CGPA totals.
- **`main()`** ties everything together: it loops through each semester, collects and displays data, accumulates totals, and finally computes and prints the overall CGPA.

## 10. Sample Input
```
Enter number of semesters to calculate CGPA for: 1

----- Semester 1 -----
Enter number of courses this semester: 2

Course 1:
  Enter course name: DSA
  Enter grade (A/B/C/D/F): A
  Enter credit hours: 4

Course 2:
  Enter course name: Maths
  Enter grade (A/B/C/D/F): B
  Enter credit hours: 3
```

## 11. Sample Output
```
===== Semester 1 Report =====
Course              Grade     Credit Hrs     Quality Pts
------------------------------------------------------------
DSA                 A         4              16
Maths               B         3              9
------------------------------------------------------------
Semester GPA: 3.57

=========================================
              FINAL RESULT
=========================================
Total Credit Hours : 7.00
Total Quality Points: 25.00
Overall CGPA        : 3.57 / 4.00
```
*(This exact output was produced during actual testing of the program — see Section 13 note.)*

## 12. Test Cases

| # | Input Scenario | Expected Result | Actual Result (Tested) |
|---|---|---|---|
| 1 | 1 semester, 2 courses (A/4cr, B/3cr) | CGPA = 3.57 | ✅ Passed |
| 2 | Invalid grade entered (e.g. "Z") | Program re-prompts for a valid grade | ✅ Passed |
| 3 | Negative or non-numeric credit hours | Program re-prompts for a valid positive number | ✅ Passed |
| 4 | Multiple semesters | Overall CGPA correctly combines all semesters | ✅ Passed |
| 5 | 0 courses requested | Rejected — must be a positive number | ✅ Passed |

## 13. Possible Errors and How to Handle Them
- **Non-numeric input for credit hours/semesters/courses:** Handled by `cin.fail()` checks that clear the error state and re-prompt.
- **Invalid grade letters:** Handled by `gradeToPoint()` returning `-1`, which `readValidGrade()` detects and rejects.
- **Division by zero (0 total credits):** Guarded with an `if (totalCredits > 0)` check before dividing, both at semester and CGPA level.
- **Empty course name:** Defaults to "Course N" if the user just presses Enter.

## 14. Advantages
- Removes manual calculation errors.
- Reusable across any number of semesters/courses.
- Clear, tabular output that's easy to read and explain.
- Strong input validation makes it hard to crash.

## 15. Limitations
- Only supports letter grades A–F (no +/- grades like A- or B+).
- Assumes a standard 4.0 grading scale (doesn't support 10-point or percentage scales).
- Data is not saved between runs (no file storage).
- Console-only interface (no GUI).

## 16. Future Enhancements
*(These are my own recommended additions — not requirements from the CodeAlpha PDF.)*
- Add support for +/- grades (A-, B+, etc.) with a finer point scale.
- Save/load student records to a file so CGPA history persists across runs.
- Add a simple GUI using Qt or a web frontend.
- Allow editing/deleting a previously entered course before final calculation.

## 17. Conclusion
This project demonstrates core C++ fundamentals — loops, functions, structs, vectors, and robust input validation — applied to a real, relatable problem every student faces. It satisfies CodeAlpha's Task 1 requirements in full: course-wise grade/credit input, GPA and CGPA calculation, and a clear final display.
