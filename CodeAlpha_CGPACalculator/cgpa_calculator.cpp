/*
    Project     : CGPA Calculator
    Internship  : CodeAlpha - C++ Programming
    Description : Takes course grades and credit hours as input, calculates
                   GPA for the semester and overall CGPA, and displays a
                   summary report to the user.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Stores the details of a single course entered by the student
struct Course {
    string name;
    char grade;
    double creditHours;
    double gradePoint;      // numeric value of the letter grade (e.g. A = 4.0)
    double qualityPoints;   // gradePoint * creditHours
};

// Converts a letter grade (A, B, C, D, F with optional + / -) into a
// standard 4.0 scale grade point. Returns -1 if the grade is invalid.
double gradeToPoint(char grade) {
    switch (toupper(grade)) {
        case 'A': return 4.0;
        case 'B': return 3.0;
        case 'C': return 2.0;
        case 'D': return 1.0;
        case 'F': return 0.0;
        default:  return -1.0; // invalid grade marker
    }
}

// Clears bad input from cin so the program does not get stuck in an
// infinite loop if the user types letters instead of numbers.
void clearInputError() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Reads a positive integer from the user with validation.
int readPositiveInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Invalid input. Please enter a positive whole number.\n";
            clearInputError();
        } else {
            clearInputError(); // remove leftover newline
            return value;
        }
    }
}

// Reads a positive double (used for credit hours) with validation.
double readPositiveDouble(const string &prompt) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cout << "Invalid input. Please enter a positive number.\n";
            clearInputError();
        } else {
            clearInputError();
            return value;
        }
    }
}

// Reads a valid letter grade (A, B, C, D, F). Keeps asking until valid.
char readValidGrade(const string &prompt) {
    char grade;
    while (true) {
        cout << prompt;
        cin >> grade;
        clearInputError();
        if (gradeToPoint(grade) < 0) {
            cout << "Invalid grade. Allowed grades: A, B, C, D, F.\n";
        } else {
            return toupper(grade);
        }
    }
}

// Collects details for one semester: number of courses, then for each
// course its name, grade and credit hours.
vector<Course> inputSemesterCourses(int semesterNumber) {
    cout << "\n----- Semester " << semesterNumber << " -----\n";
    int numCourses = readPositiveInt("Enter number of courses this semester: ");

    vector<Course> courses;
    for (int i = 0; i < numCourses; i++) {
        Course c;
        cout << "\nCourse " << (i + 1) << ":\n";

        cout << "  Enter course name: ";
        getline(cin, c.name);
        if (c.name.empty()) c.name = "Course " + to_string(i + 1);

        c.grade = readValidGrade("  Enter grade (A/B/C/D/F): ");
        c.creditHours = readPositiveDouble("  Enter credit hours: ");

        c.gradePoint = gradeToPoint(c.grade);
        c.qualityPoints = c.gradePoint * c.creditHours;

        courses.push_back(c);
    }
    return courses;
}

// Prints a formatted table of the courses in one semester along with the
// GPA for that semester. Returns the total credits and quality points
// through reference parameters so they can be added to the CGPA totals.
double displaySemesterReport(const vector<Course> &courses, int semesterNumber,
                              double &totalCreditsOut, double &totalQualityPointsOut) {
    double totalCredits = 0.0, totalQualityPoints = 0.0;

    cout << "\n===== Semester " << semesterNumber << " Report =====\n";
    cout << left << setw(20) << "Course" << setw(10) << "Grade"
         << setw(15) << "Credit Hrs" << setw(15) << "Quality Pts" << "\n";
    cout << string(60, '-') << "\n";

    for (const auto &c : courses) {
        cout << left << setw(20) << c.name << setw(10) << c.grade
             << setw(15) << c.creditHours << setw(15) << c.qualityPoints << "\n";
        totalCredits += c.creditHours;
        totalQualityPoints += c.qualityPoints;
    }

    double gpa = (totalCredits > 0) ? (totalQualityPoints / totalCredits) : 0.0;
    cout << string(60, '-') << "\n";
    cout << fixed << setprecision(2);
    cout << "Semester GPA: " << gpa << "\n";

    totalCreditsOut = totalCredits;
    totalQualityPointsOut = totalQualityPoints;
    return gpa;
}

int main() {
    cout << "=========================================\n";
    cout << "         CGPA CALCULATOR (CodeAlpha)      \n";
    cout << "=========================================\n";

    int numSemesters = readPositiveInt("Enter number of semesters to calculate CGPA for: ");

    double overallCredits = 0.0;
    double overallQualityPoints = 0.0;

    for (int s = 1; s <= numSemesters; s++) {
        vector<Course> courses = inputSemesterCourses(s);

        double semCredits = 0.0, semQualityPoints = 0.0;
        displaySemesterReport(courses, s, semCredits, semQualityPoints);

        overallCredits += semCredits;
        overallQualityPoints += semQualityPoints;
    }

    cout << "\n=========================================\n";
    cout << "              FINAL RESULT                \n";
    cout << "=========================================\n";
    cout << fixed << setprecision(2);

    if (overallCredits > 0) {
        double cgpa = overallQualityPoints / overallCredits;
        cout << "Total Credit Hours : " << overallCredits << "\n";
        cout << "Total Quality Points: " << overallQualityPoints << "\n";
        cout << "Overall CGPA        : " << cgpa << " / 4.00\n";
    } else {
        cout << "No valid credit hours entered. CGPA cannot be calculated.\n";
    }

    cout << "=========================================\n";
    cout << "Thank you for using the CGPA Calculator!\n";

    return 0;
}
