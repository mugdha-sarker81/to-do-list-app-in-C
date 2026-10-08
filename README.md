# Task Manager & Daily Habit Tracker

A menu-driven **C-based Task and Habit Management System** that allows users to manage tasks, track daily habits, monitor progress, and save records using file handling.  
An upgraded **Calendar/Task View** organizes tasks by date for easier daily planning.

---

## CSE-1102 Lab Contents Used in the Project

- **Basic Operators:** Used for task IDs, calculations, comparisons, and performance percentages.
- **Arrays:** Used to store multiple tasks, habits, and habit logs.
- **Strings & String Functions:** Used for task titles, dates, priorities, statuses, habit names, and string comparison/copying.
- **User-Defined Data Types:** `struct` and `typedef` are used to create task, habit, and habit-log records.
- **Pointers:** Used for passing data, accessing structures, arrays, and file operations.
- **File Handling:** Used to save and load tasks, habits, and habit records permanently.
- **Command-Line Parameters:** Used to provide startup options or configuration when launching the program.
- **User-Defined Functions:** Separate functions are used for task, habit, calendar, and other operations, and are called through the program's menu flow.
- **Multiple C Files:** The project is divided into multiple `.c` and `.h` files, with different modules working together.
- **Makefile:** A Makefile is used to compile and link the project's multiple C source files efficiently.
- **Dynamic Memory Allocation:** `malloc()` / `free()` are used to dynamically manage tasks and other records when required.
- **Extra Functions/Libraries:** Additional standard C libraries and built-in functions are used for date and time management, task sorting, string processing, input validation, file data processing, screen control, and safe program termination.

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

make
make run
```

To pass command-line options through `make`, use `make run ARGS="--help"`.
Use `make run ARGS="--tut"` to print a quick guide to using the application.
You can also compile directly with `gcc main.c tasks.c habits.c calendar.c export.c -o todo`.

### Windows (PowerShell)

PowerShell does not include `make`. Install GNU Make and GCC (for example, with MSYS2), or use `mingw32-make` if that is the command provided by your MinGW installation:

```powershell
mingw32-make
mingw32-make run
```

If GCC is installed but Make is not, build and run directly:

```powershell
gcc main.c tasks.c habits.c calendar.c export.c -o todo.exe
.\todo.exe
```

**Command-line Options**
```
./todo --help              # Show help
./todo --tut               # Show a quick application tutorial
./todo --data              # Show where your progress is saved
./todo --report            # Generate and open the HTML task report
./todo --clear             # Clear all saved data
./todo --date DD-MM-YYYY   # Show tasks of a specific date
./todo --habit             # Open Daily Habits dashboard directly
```

`--report` creates `report.html` from your saved tasks and opens it with the
default browser (Windows, macOS, or Linux). If it cannot be opened
automatically, open `report.html` manually from the project directory.

### Command-Line Tutorial (`--tut`)

Run the tutorial at any time from a terminal:

```bash
./todo --tut
```

On Windows PowerShell, use:

```powershell
.\todo.exe --tut
```

The tutorial prints a quick guide without opening the interactive menu. To use
the application, run `./todo` (or `.\todo.exe` on Windows) without an option,
then choose from the main menu:

1. **Add a task:** enter its date in `DD-MM-YYYY` format, title, and priority
   (`High`, `Medium`, or `Low`).
2. **View or find tasks:** choose the pending-task list or search by date. You
   can also run `./todo --date 26-09-2026` to list tasks for a date directly.
3. **Complete or delete a task:** use its task ID when prompted.
4. **Track habits:** open the habits dashboard to add habits and mark today's
   habits complete. `./todo --habit` opens this dashboard directly.
5. **Plan and export:** view a month in the calendar or export tasks to
   `report.html`.
6. **Exit:** choose the exit option in the main menu.

The application saves task and habit data in `tasks.txt`, `habits.txt`, and
`habit_log.txt` in the current directory. The `--clear` option deletes those
saved data files, so use it only when you intend to erase the saved data.

### How the App Works
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
8. Export tasks to HTML
9. Exit
```
### Calendar Colors
```
Color    Meaning

Red      High priority pending tasks
Yellow   Medium priority
Green    Low priority
```
### Data Files
The program automatically creates and uses these files:
```
tasks.txt – stores all tasks
habits.txt – stores habits
habit_log.txt – stores daily habit completion logs
```
