```markdown
# Task Manager

### Dashboard

```
=====================================
            TASK MANAGER
=====================================
1. Add Task
2. View All pending Tasks
3. Search Task by Date
4. Mark a Task done
5. Delete Task
6. Exit
=====================================
Enter your choice:
```

### Date View (Search by Date)

```
=======Tasks for 20-09-2026:=========

1 | C Project | Priority: High | Status: Pending
2 | Lab Report | Priority: Medium | Status: Done
3 | DSA Assignment | Priority: High | Status: Pending

=====================================
            want to customize ?
=====================================
1. Add Task
2. Mark a Task done
3. Delete Task
4. back to dashboard
=====================================
Enter your choice:
```

### Task Manager Flow

```
                    ┌──────────────┐
                    │  DASHBOARD   │
                    └──────┬───────┘
                           │
        ┌──────────┬───────┼──────────┬──────────┬──────────┐
        ↓          ↓       ↓          ↓          ↓          ↓
    Add Task   View All  Search     Mark Task  Delete     Exit
               Pending   by Date    as Done     Task
                          │
                          ↓
                  ┌──────────────┐
                  │ Search Date  │
                  │ DD-MM-YYYY   │
                  └──────┬───────┘
                         ↓
                  ┌──────────────┐
                  │  DATE PAGE   │
                  │ 20-09-2026   │
                  └──────┬───────┘
                         ↓
             ┌─────────────────────────┐
             │ Tasks on this date      │
             ├─────────────────────────┤
             │ 1. C Project | Pending  │
             │ 2. Lab Report | Done    │
             │ 3. DSA Assignment       │
             └──────────┬──────────────┘
                        ↓
               ┌────────────────┐
               │ 1. Add Task    │
               │ 2. Mark Done   │
               │ 3. Delete      │
               │ 4. Back        │
               └───────┬────────┘
                       ↓
                Modify tasks[]
                       ↓
                  saveTasks()
                       ↓
             ┌─────────────────┐
             │ Refreshed Date  │
             │      Page       │
             └─────────────────┘
```

### Task Structure

```
tasks[0]
 ├── id       = 1
 ├── date     = "20-09-2026"
 ├── title    = "C Project"
 ├── priority = "High"
 └── status   = "Pending"

tasks[1]
 ├── id       = 2
 ├── date     = "20-09-2026"
 ├── title    = "Lab Report"
 ├── priority = "Medium"
 └── status   = "Done"

tasks[2]
 ├── id       = 3
 ├── date     = "20-09-2026"
 ├── title    = "DSA Assignment"
 ├── priority = "High"
 └── status   = "Pending"
```

### How It Works

1. **Dashboard** – Add, view pending, search by date, mark done, or delete tasks.
2. **Search Date** – Enter a date in DD-MM-YYYY format.
3. **Date Page** – All tasks for that date are shown with status and priority.
4. **Task Management** – From the date page: add, mark done, or delete tasks.
5. **Save Changes** – Modified tasks are saved with `saveTasks()`.
6. **Refresh** – The date page updates to show the latest list.
```
