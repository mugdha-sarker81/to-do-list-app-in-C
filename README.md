Project Title

Task Manager & Daily Habit Tracker

Short Description:
A menu-driven **C-based Task and Habit Management System** that allows users to manage tasks, track daily habits, monitor progress, and save records using file handling. An upgraded **Calendar/Task View** will organize tasks by date for easier daily planning.

How the Project Covers Lab Topics:

Variables & Data Types: Task IDs, dates, priorities, statuses, habit times, streaks, and percentages are stored using int and char variables throughout.

Arrays: tasks[], habits[], and logs[] arrays store all task, habit, and habit-log records in memory.

Strings/Character Arrays: Task titles, dates, priorities, statuses, habit names, and time strings (HH:MM) are handled with char arrays and string functions (strcmp, strcpy, strcspn, sscanf).

Structures: struct Task, Habit, and HabitLog group related fields (e.g., a task's date, title, priority, and status) into single records.

Functions: The program is broken into many user-defined functions — addTask(), viewTasks(), searchByDate(), completeTask(), deleteTask(), addHabit(), toggleHabit(), showPerformance(), etc. — each handling one responsibility.

Loops: for and while loops drive the main dashboard/habit-board menus, iterate over tasks/habits/logs when searching or displaying, and control input re-prompting until valid data is entered.

Conditional Statements & Switch-Case: if-else validates dates, times, and priorities; switch statements power the main dashboard menu and the habit-board sub-menu.

File Handling: tasks.txt, habits.txt, and habit_log.txt are read with fscanf/fopen and written with fprintf, so data survives after the program closes.

Sorting: qsort() with a custom comparator (cmpByDate) sorts tasks chronologically; a manual bubble sort (sortHabitsByTime) keeps habits ordered by scheduled time.

Date & Time Handling (time.h): time_t, struct tm, mktime(), localtime(), and strftime() compute today's date, convert between date strings and time values, and calculate habit streaks day-by-day.

Macros (#define): Constants like MAX_TASKS, MAX_HABITS, MAX_LOGS, TREND_DAYS, and IGNORED_THRESHOLD define fixed limits and thresholds used across the program.

Input Validation: Custom functions (validDate, validTime) check user input format before accepting it, preventing corrupted records.
