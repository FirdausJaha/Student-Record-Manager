# Student Record Manager

## 🚀 Live Demo

👉 [Open Student Record Manager](https://firdausjaha.github.io/Student-Record-Manager/)

A complete C++ lab project presented through a modern web interface.

## Project focus

The **C++ program is the core of the application**. Student records are managed with fixed-size arrays, functions, string handling, searching, sorting, validation, and mark analysis. The web interface is only a user-friendly presentation layer; JavaScript is used as a small bridge to call the compiled C++ functions in the browser.

## Main features

- Add student records
- View all records
- Search by roll number
- Search by student name (case-insensitive partial search)
- Update student records
- Delete student records
- Find highest and lowest scores
- Calculate average score
- Count students meeting a pass threshold of 40
- Sort by name and score
- Validate roll number, name, score, and duplicate records
- Dashboard statistics and recent records
- Responsive multi-screen interface
- Browser persistence so records survive refresh/reopening on the same browser

## C++ data structure

```cpp
int rollNo[100];
string studentName[100];
float marks[100];
```

The record-management operations are implemented in `src/student_manager.cpp`.

## Web build

GitHub Actions uses Emscripten to compile the C++ source to WebAssembly and deploy the static site to GitHub Pages. The workflow deliberately uses the non-modularized Emscripten build so the browser bridge can initialize the global `Module` reliably.

## Local development

The source code can be compiled as a normal C++ program after removing the Emscripten binding block. For the website, the repository workflow is the recommended build path because it provides the Emscripten compiler automatically.

## Viva focus

Be ready to explain:

1. Why arrays are used.
2. How the roll-number search works.
3. How name search uses strings and case conversion.
4. How highest/lowest marks are found.
5. How average marks are calculated.
6. How update and delete shift records in the arrays.
7. How sorting is performed using an index array.
8. Why a fixed maximum of 100 records is used.
9. What validation prevents invalid or duplicate records.
10. How the browser calls the C++ functions.


### Final C++ enhancements
- Hand-written selection sort is used for score ordering to demonstrate array-based sorting logic.
- Add/update operations return specific validation status codes so the interface can show meaningful feedback.
- Clear-all is available with confirmation and persistence is updated immediately.
