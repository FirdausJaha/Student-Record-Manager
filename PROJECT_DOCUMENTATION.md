# Student Record Manager — Project Documentation

## 1. Problem statement

Maintaining student records manually takes time and makes searching and mark analysis difficult. A simple record manager can make it easier to add, view, search, update and analyze student information.

## 2. Objectives

- Store student records using arrays.
- Enter and display multiple records.
- Search using roll number or name.
- Find highest and lowest scores.
- Demonstrate string handling.
- Provide a simple menu-like set of operations through a user-friendly interface.
- Add practical record-management features without moving the core logic away from C++.

## 3. Data representation

The core program uses three parallel arrays:

```cpp
int rollNo[100];
string studentName[100];
float marks[100];
```

`studentCount` stores the number of active records.

For a student at index `i`:

- `rollNo[i]` is the roll number.
- `studentName[i]` is the name.
- `marks[i]` is the score.

## 4. C++ functionality

### Add student

Checks capacity, positive roll number, valid name, valid score and duplicate roll number before storing the record at `studentCount`.

### Search by roll number

Uses a linear search from index 0 to `studentCount - 1` and returns the matching record.

### Search by name

Converts both the query and stored names to lowercase and checks whether the query occurs inside a student's name. This demonstrates practical string handling.

### Highest and lowest score

The program scans the marks array and keeps the index of the largest or smallest value.

### Average score

All stored scores are added and divided by `studentCount`.

### Update

The matching roll number is located and the student's name and score are replaced after validation.

### Delete

After locating a record, later elements are shifted one position to the left. `studentCount` is then decreased.

### Sorting

An index array is sorted instead of rearranging the actual student arrays. This keeps the original data structure simple while supporting name and score ordering for display.

## 5. Browser interface

The interface contains four screens:

- Dashboard — summary statistics, recent records and quick actions.
- Students — complete record table with search, sorting, update and delete.
- Search — dedicated roll-number/name search.
- Analysis — highest, lowest, average and score distribution.

The add/update form opens only when the user requests it.

The interface does not display implementation labels such as C++/WebAssembly or hosting details; those are implementation details for the project documentation and viva.

## 6. Persistence

The core record operations remain in C++. After a successful C++ operation, the browser stores the C++ record serialization in local browser storage. On the next load, the saved records are passed back to the C++ `importRecords()` function. This allows the application to survive refreshes without introducing a server or SQL database.

The stored data is browser/device-specific; it is not a shared cloud database.

## 7. Validation

The application prevents:

- Empty student names.
- Names containing unsupported characters.
- Roll number 0 or negative values.
- Scores outside 0–100.
- Duplicate roll numbers.
- More than 100 records.

## 8. Suggested viva questions

**Q: Why did you use arrays?**

A: The project specifically requires student data to be stored using arrays. Parallel arrays keep the implementation straightforward and demonstrate indexed record storage.

**Q: What searching technique is used?**

A: Linear search. Each stored record is checked sequentially until a matching roll number or name is found.

**Q: How do you find the highest mark?**

A: Start with the first record as the current maximum and scan the remaining marks, updating the maximum index whenever a larger value is found.

**Q: How is name search made case-insensitive?**

A: Both the stored name and search query are converted to lowercase before comparison.

**Q: How does delete work with arrays?**

A: The record after the deleted position is shifted left repeatedly, then the active record count is reduced.

**Q: Why is the maximum 100?**

A: A fixed maximum keeps the array-based implementation simple and predictable for the lab project.

**Q: Why is the website used?**

A: It provides a clear user interface for demonstrating the C++ functions. The record-management logic remains in C++.

**Q: Is SQL used?**

A: No. This is intentionally an array-based C++ lab project. Browser storage is used only to preserve the current records between sessions.


### Final C++ enhancements
- Hand-written selection sort is used for score ordering to demonstrate array-based sorting logic.
- Add/update operations return specific validation status codes so the interface can show meaningful feedback.
- Clear-all is available with confirmation and persistence is updated immediately.
