## Task Manager

### Dashboard

```text
================================
          TASK MANAGER
================================

1. Add Task
2. View Tasks
3. Mark Task as Complete
4. Search a Date
5. Exit

Enter choice:
```

### Date View

```text
================================
          20-09-2026
================================

1. C Project          | Pending
2. Lab Report         | Done
3. DSA Assignment     | Pending

--------------------------------
1. Edit
2. Add
3. Delete
4. Back
--------------------------------
```

### Task Manager Flow

```text
                    ┌──────────────┐
                    │  DASHBOARD   │
                    └──────┬───────┘
                           │
        ┌──────────┬───────┼──────────┬──────────┐
        ↓          ↓       ↓          ↓          ↓
    Add Task   View Task  Complete   Search     Exit
                           Task       Date
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
                         ┌─────────────────────┐
                         │ Tasks on this date  │
                         ├─────────────────────┤
                         │ 1. C Project |Pending│
                         │ 2. Lab Report| Done  │
                         │ 3. DSA Assignment    │
                         └──────────┬──────────┘
                                    ↓
                           ┌────────────────┐
                           │ 1. Edit       │
                           │ 2. Add        │
                           │ 3. Delete     │
                           │ 4. Back       │
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
```data array
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
### How It Works
```
1. **Dashboard** – The user can add, view, complete, or search tasks.
2. **Search Date** – The user enters a date in `DD-MM-YYYY` format.
3. **Date Page** – All tasks for that date are displayed with their current status.
4. **Task Management** – Users can edit, add, or delete tasks.
5. **Save Changes** – Modified tasks are saved using `saveTasks()`.
6. **Refresh** – The date page is refreshed to show the updated task list.
