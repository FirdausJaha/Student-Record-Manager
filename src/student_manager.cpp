#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iomanip>
#include <emscripten/bind.h>

using namespace std;

const int MAX_STUDENTS = 100;

// ============================================================
// STUDENT DATA
// Fixed-size arrays are used as required for the C++ lab.
// ============================================================

int rollNo[MAX_STUDENTS];
string studentName[MAX_STUDENTS];
float marks[MAX_STUDENTS];

int studentCount = 0;


// ============================================================
// STRING FUNCTIONS
// ============================================================

string trim(const string& text) {

    size_t start = text.find_first_not_of(" \t\n\r");

    if (start == string::npos)
        return "";

    size_t end = text.find_last_not_of(" \t\n\r");

    return text.substr(start, end - start + 1);
}


string toLowerCase(string text) {

    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c) {
            return static_cast<char>(tolower(c));
        }
    );

    return text;
}


// ============================================================
// VALIDATION
// ============================================================

bool validName(const string& name) {

    if (name.empty() || name.size() > 80)
        return false;

    for (unsigned char c : name) {

        if (!(isalpha(c) ||
              isspace(c) ||
              c == '.' ||
              c == '-' ||
              c == '\'')) {

            return false;
        }
    }

    return true;
}


bool validMarks(float value) {

    return value >= 0.0f && value <= 100.0f;
}


// ============================================================
// SEARCH BY ROLL NUMBER
// Linear Search using the student arrays.
// ============================================================

int findByRoll(int roll) {

    for (int i = 0; i < studentCount; ++i) {

        if (rollNo[i] == roll)
            return i;
    }

    return -1;
}


// ============================================================
// ADD STUDENT
// ============================================================

int addStudentResult(
    int roll,
    const string& nameInput,
    float mark
) {

    string name = trim(nameInput);

    // Maximum capacity reached
    if (studentCount >= MAX_STUDENTS)
        return 4;

    // Invalid roll number
    if (roll <= 0)
        return 1;

    // Duplicate roll number
    if (findByRoll(roll) != -1)
        return 2;

    // Invalid name
    if (!validName(name))
        return 3;

    // Invalid marks
    if (!validMarks(mark))
        return 5;

    // Store data in arrays
    rollNo[studentCount] = roll;
    studentName[studentCount] = name;
    marks[studentCount] = mark;

    ++studentCount;

    return 0;
}


bool addStudent(
    int roll,
    const string& nameInput,
    float mark
) {

    return addStudentResult(
        roll,
        nameInput,
        mark
    ) == 0;
}


// ============================================================
// UPDATE STUDENT
// ============================================================

int updateStudentResult(
    int roll,
    const string& nameInput,
    float mark
) {

    int index = findByRoll(roll);

    string name = trim(nameInput);

    // Student not found
    if (index == -1)
        return 1;

    // Invalid name
    if (!validName(name))
        return 2;

    // Invalid marks
    if (!validMarks(mark))
        return 3;

    // Update arrays
    studentName[index] = name;
    marks[index] = mark;

    return 0;
}


bool updateStudent(
    int roll,
    const string& nameInput,
    float mark
) {

    return updateStudentResult(
        roll,
        nameInput,
        mark
    ) == 0;
}


// ============================================================
// DELETE STUDENT
// Array shifting is used after deletion.
// ============================================================

bool deleteStudent(int roll) {

    int index = findByRoll(roll);

    if (index == -1)
        return false;

    // Shift remaining records to the left
    for (
        int i = index;
        i < studentCount - 1;
        ++i
    ) {

        rollNo[i] = rollNo[i + 1];

        studentName[i] =
            studentName[i + 1];

        marks[i] =
            marks[i + 1];
    }

    --studentCount;

    return true;
}


// ============================================================
// RECORD FORMATTING
// Used to transfer records between C++ and JavaScript.
// ============================================================

string formatRecord(int index) {

    ostringstream out;

    out << rollNo[index]
        << "~"
        << studentName[index]
        << "~"
        << fixed
        << setprecision(2)
        << marks[index];

    return out.str();
}


// ============================================================
// GET ALL RECORDS
// ============================================================

string getRecords() {

    string result;

    for (
        int i = 0;
        i < studentCount;
        ++i
    ) {

        if (!result.empty())
            result += "|";

        result += formatRecord(i);
    }

    return result;
}


// ============================================================
// SEARCH BY ROLL NUMBER
// ============================================================

string searchByRoll(int roll) {

    int index = findByRoll(roll);

    if (index == -1)
        return "";

    return formatRecord(index);
}


// ============================================================
// SEARCH BY NAME
// Case-insensitive linear search.
// ============================================================

string searchByName(
    const string& queryInput
) {

    string query =
        toLowerCase(
            trim(queryInput)
        );

    if (query.empty())
        return "";

    string result;

    for (
        int i = 0;
        i < studentCount;
        ++i
    ) {

        string name =
            toLowerCase(
                studentName[i]
            );

        if (
            name.find(query)
            != string::npos
        ) {

            if (!result.empty())
                result += "|";

            result +=
                formatRecord(i);
        }
    }

    return result;
}


// ============================================================
// HIGHEST MARK
// ============================================================

int highestIndex() {

    if (studentCount == 0)
        return -1;

    int best = 0;

    for (
        int i = 1;
        i < studentCount;
        ++i
    ) {

        if (
            marks[i]
            > marks[best]
        ) {

            best = i;
        }
    }

    return best;
}


// ============================================================
// LOWEST MARK
// ============================================================

int lowestIndex() {

    if (studentCount == 0)
        return -1;

    int best = 0;

    for (
        int i = 1;
        i < studentCount;
        ++i
    ) {

        if (
            marks[i]
            < marks[best]
        ) {

            best = i;
        }
    }

    return best;
}


// ============================================================
// AVERAGE MARKS
// ============================================================

float averageMarks() {

    if (studentCount == 0)
        return 0.0f;

    float total = 0.0f;

    for (
        int i = 0;
        i < studentCount;
        ++i
    ) {

        total += marks[i];
    }

    return total / studentCount;
}


// ============================================================
// PASS COUNT
// ============================================================

int passCount(float passMark) {

    int count = 0;

    for (
        int i = 0;
        i < studentCount;
        ++i
    ) {

        if (
            marks[i]
            >= passMark
        ) {

            ++count;
        }
    }

    return count;
}


// ============================================================
// COMPLETE ANALYSIS
//
// Format:
// Highest | Lowest | Average
// ============================================================

string getAnalysis() {

    if (studentCount == 0)
        return "";

    int hi = highestIndex();

    int lo = lowestIndex();

    ostringstream out;

    out << formatRecord(hi)
        << "|"
        << formatRecord(lo)
        << "|"
        << fixed
        << setprecision(2)
        << averageMarks();

    return out.str();
}


// ============================================================
// SORT BY MARKS
// Uses an index array so original student arrays remain intact.
// ============================================================

string sortByMarks(bool descending) {

    int order[MAX_STUDENTS];

    for (
        int i = 0;
        i < studentCount;
        ++i
    ) {

        order[i] = i;
    }

    sort(
        order,
        order + studentCount,

        [descending](int a, int b) {

            // Same marks -> alphabetical order
            if (
                marks[a]
                == marks[b]
            ) {

                return
                    studentName[a]
                    < studentName[b];
            }

            if (descending) {

                return
                    marks[a]
                    > marks[b];

            } else {

                return
                    marks[a]
                    < marks[b];
            }
        }
    );

    string result;

    for (
        int k = 0;
        k < studentCount;
        ++k
    ) {

        if (!result.empty())
            result += "|";

        result +=
            formatRecord(
                order[k]
            );
    }

    return result;
}


// ============================================================
// SELECTION SORT BY MARKS
// Manual sorting algorithm for C++ lab demonstration.
// ============================================================

string selectionSortByMarks(
    bool descending
) {

    int order[MAX_STUDENTS];

    for (
        int i = 0;
        i < studentCount;
        ++i
    ) {

        order[i] = i;
    }


    for (
        int i = 0;
        i < studentCount - 1;
        ++i
    ) {

        int selected = i;

        for (
            int j = i + 1;
            j < studentCount;
            ++j
        ) {

            bool better;

            if (
                marks[order[j]]
                == marks[order[selected]]
            ) {

                better =
                    studentName[order[j]]
                    <
                    studentName[order[selected]];

            } else if (descending) {

                better =
                    marks[order[j]]
                    >
                    marks[order[selected]];

            } else {

                better =
                    marks[order[j]]
                    <
                    marks[order[selected]];
            }

            if (better)
                selected = j;
        }


        if (selected != i) {

            int temp = order[i];

            order[i] =
                order[selected];

            order[selected] =
                temp;
        }
    }


    string result;

    for (
        int k = 0;
        k < studentCount;
        ++k
    ) {

        if (!result.empty())
            result += "|";

        result +=
            formatRecord(
                order[k]
            );
    }

    return result;
}


// ============================================================
// SORT BY NAME
// ============================================================

string sortByName() {

    int order[MAX_STUDENTS];

    for (
        int i = 0;
        i < studentCount;
        ++i
    ) {

        order[i] = i;
    }


    sort(
        order,
        order + studentCount,

        [](int a, int b) {

            string left =
                toLowerCase(
                    studentName[a]
                );

            string right =
                toLowerCase(
                    studentName[b]
                );


            if (left == right) {

                return
                    rollNo[a]
                    <
                    rollNo[b];
            }

            return left < right;
        }
    );


    string result;

    for (
        int k = 0;
        k < studentCount;
        ++k
    ) {

        if (!result.empty())
            result += "|";

        result +=
            formatRecord(
                order[k]
            );
    }

    return result;
}


// ============================================================
// CLEAR ALL RECORDS
// ============================================================

bool clearAll() {

    studentCount = 0;

    return true;
}


// ============================================================
// IMPORT RECORDS
//
// Used when browser localStorage sends saved records
// back into the C++ arrays.
// ============================================================

bool importRecords(
    const string& serialized
) {

    clearAll();

    if (serialized.empty())
        return true;

    string row;

    stringstream rows(
        serialized
    );


    while (
        getline(
            rows,
            row,
            '|'
        )
    ) {

        size_t a =
            row.find('~');

        size_t b =
            row.find(
                '~',
                a == string::npos
                    ? 0
                    : a + 1
            );


        if (
            a == string::npos ||
            b == string::npos
        ) {

            continue;
        }


        try {

            int roll =
                stoi(
                    row.substr(
                        0,
                        a
                    )
                );


            string name =
                row.substr(
                    a + 1,
                    b - a - 1
                );


            float mark =
                stof(
                    row.substr(
                        b + 1
                    )
                );


            addStudent(
                roll,
                name,
                mark
            );

        }
        catch (...) {

            // Ignore malformed saved records.
        }
    }


    return true;
}


// ============================================================
// COUNT STUDENTS
//
// IMPORTANT:
// This is a normal C++ function instead of a lambda.
// This fixes the Emscripten compilation error.
// ============================================================

int countStudents() {

    return studentCount;
}


// ============================================================
// EMSCRIPTEN BINDINGS
//
// These functions make the C++ functionality available
// to the HTML/CSS/JavaScript interface.
// ============================================================

EMSCRIPTEN_BINDINGS(student_manager) {

    emscripten::function(
        "addStudent",
        &addStudent
    );


    emscripten::function(
        "addStudentResult",
        &addStudentResult
    );


    emscripten::function(
        "updateStudent",
        &updateStudent
    );


    emscripten::function(
        "updateStudentResult",
        &updateStudentResult
    );


    emscripten::function(
        "deleteStudent",
        &deleteStudent
    );


    emscripten::function(
        "getRecords",
        &getRecords
    );


    emscripten::function(
        "searchByRoll",
        &searchByRoll
    );


    emscripten::function(
        "searchByName",
        &searchByName
    );


    emscripten::function(
        "getAnalysis",
        &getAnalysis
    );


    emscripten::function(
        "sortByMarks",
        &sortByMarks
    );


    emscripten::function(
        "selectionSortByMarks",
        &selectionSortByMarks
    );


    emscripten::function(
        "sortByName",
        &sortByName
    );


    emscripten::function(
        "averageMarks",
        &averageMarks
    );


    emscripten::function(
        "passCount",
        &passCount
    );


    emscripten::function(
        "countStudents",
        &countStudents
    );


    emscripten::function(
        "clearAll",
        &clearAll
    );


    emscripten::function(
        "importRecords",
        &importRecords
    );
}
