# Task Manager & Daily Habit Tracker

A menu-driven **C-based Task and Habit Management System** that allows users to manage tasks, track daily habits, monitor progress, and save records using file handling.  
An upgraded **Calendar/Task View** organizes tasks by date for easier daily planning.

---

## CSE-1102 Lab Contents Used in the Project

- **Basic Operators**: Used for task IDs, calculations, comparisons, and performance percentages.
- **Arrays**: Used to store multiple tasks, habits, and habit logs.
- **Strings & String Functions**: Used for task titles, dates, priorities, statuses, habit names, and string comparison/copying.
- **User-Defined Data Types**: `struct` and `typedef` are used to create task, habit, and habit-log records.
- **Pointers**: Used for passing data, accessing structures, arrays, and file operations.
- **File Handling**: Used to save and load tasks, habits, and habit records permanently.
- **Command-Line Parameters**: Used to provide startup options or configuration when launching the program.
- **Multiple C Files**: The project is divided into multiple `.c` and `.h` files, with different modules working together.
- **Dynamic Memory Allocation**: `malloc()` / `free()` are used to dynamically manage tasks and other records when required.
- **Extra Functions/Libraries**: Additional standard C libraries and built-in functions are used for date and time management, task sorting, string processing, input validation, file data processing, screen control, and safe program termination.

---

## Features

- Add / View / Complete / Delete Tasks
- Search tasks by date
- Colorful Calendar view (priority-based coloring)
- Daily Habits tracking
- Streak counter & Performance report
- Data saved permanently using file handling
- Command-line arguments support

---

## Project Structure

main.c          → Main program + Dashboard + Command-line handling
tasks.c / .h    → Task management module (with dynamic memory)
habits.c / .h   → Habit tracking module
calendar.c / .h → Calendar view


---

## How to Build & Run

```bash
git clone https://github.com/mugdha-sarker81/to-do-list-app-in-C.git
cd to-do-list-app-in-C

gcc main.c tasks.c habits.c calendar.c -o todo
./todo

```
**Command-line Options**
```
./todo --help              # Show help
./todo --clear             # Clear all saved data
./todo --date DD-MM-YYYY   # Show tasks of a specific date
./todo --habit             # Open Daily Habits dashboard directly
```
How the App Works
After running, you will see the main menu:
text
```
1. Add Task
2. View All pending Tasks
3. Search Task by Date
4. Mark a Task done
5. Delete Task
6. Daily Habits dashboard
7. Show Calendar
8. Exit
```
**Calendar Colors**
```
Color    Meaning

Red      High priority pending tasks
Yellow   Medium priority
Green    Low priority
```
Data Files
The program automatically creates and uses these files:
```
tasks.txt – stores all tasks
habits.txt – stores habits
habit_log.txt – stores daily habit completion logs
```




