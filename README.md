# Task Manager & Daily Habit Tracker

A clean, modular **C-based** Task and Habit Management System with Calendar view.

---

## Features

- Add / View / Complete / Delete Tasks
- Search tasks by date
- Colorful Calendar view (priority based coloring)
- Daily Habits tracking
- Streak counter & Performance report
- Data saved permanently using file handling

---

## Project Structure
main.c          → Task management + Main Dashboard
habits.c / .h   → Habit tracking module
calendar.c / .h → Calendar view


---

## How to Use (For Users)

### 1. Clone the Repository

```bash
git clone https://github.com/mugdha-sarker81/to-do-list-app-in-C.git

cd to-do-list-app-in-C

gcc main.c tasks.c habits.c calendar.c -o todo

./todo

<<<<<<< HEAD
```
How the App Works
=======

```
**How the App Works**

>>>>>>> 3c90ad65a54d149c93ee1c075b3373e0b8ea38b9
After running, you will see the main menu:

text 1. Add Task

2. View All pending Tasks

3. Search Task by Date

4. Mark a Task done

5. Delete Task

6. Daily Habits dashboard

7. Show Calendar

8. Exit


**Calendar Colors**

**Red**    → High priority pending tasks
**Yellow** → Medium priority
**Green**  → Low priority


