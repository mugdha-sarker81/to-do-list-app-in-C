#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//============ data structure ============
struct Task {
    int id;
    char date[20];
    char title[100];
    char priority[10];
    char status[15];
};

#define MAX_TASKS 100
struct Task tasks[MAX_TASKS];
int taskCount = 0;
int nextId = 1;   // running ID counter so deleted tasks' IDs are never reused

//============ function prototypes ============
void dashboard();
void loadTasks();
void addTask();
void viewTasks();
void searchByDate();
void completeTask();
void deleteTask();
void saveTasks();
int  validateDate(const char *date);
void clearInputBuffer();

//========= main function ===========
int main() {
    loadTasks();     // just load; do NOT truncate the file here
    dashboard();
    return 0;
}

//======================================

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // discard leftover characters after a bad scanf
    }
}

// Basic DD-MM-YYYY format check: 10 chars, digits and dashes in the right places
int validateDate(const char *date) {
    if (strlen(date) != 10) return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (date[i] != '-') return 0;
        } else if (!isdigit((unsigned char)date[i])) {
            return 0;
        }
    }
    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    if (day < 1 || day > 31) return 0;
    if (month < 1 || month > 12) return 0;
    return 1;
}

void loadTasks() {
    FILE *fp = fopen("tasks.txt", "r");

    if (fp == NULL) {
        return;
    }

    taskCount = 0;
    int maxId = 0;

    // Allow the last line to be missing a trailing newline by matching
    // the final field up to newline OR end-of-file.
    while (taskCount < MAX_TASKS &&
           fscanf(fp, "%d|%19[^|]|%99[^|]|%9[^|]|%14[^\n]",
                  &tasks[taskCount].id,
                  tasks[taskCount].date,
                  tasks[taskCount].title,
                  tasks[taskCount].priority,
                  tasks[taskCount].status) == 5) {

        if (tasks[taskCount].id > maxId) {
            maxId = tasks[taskCount].id;
        }

        taskCount++;

        // consume the newline (or stop at EOF) between records
        int c = fgetc(fp);
        while (c != '\n' && c != EOF) {
            c = fgetc(fp);
        }
    }

    fclose(fp);
    nextId = maxId + 1;
}

void addTask() {

    if (taskCount >= MAX_TASKS) {
        printf("Task limit reached.\n");
        return;
    }

    struct Task newTask;

    newTask.id = nextId;   // always unique, never reused after deletion

    char dateBuf[20];
    do {
        printf("Enter date (DD-MM-YYYY): ");
        scanf(" %19[^\n]", dateBuf);
        if (!validateDate(dateBuf)) {
            printf("Invalid date format. Please use DD-MM-YYYY.\n");
        }
    } while (!validateDate(dateBuf));
    strcpy(newTask.date, dateBuf);

    printf("Enter task: ");
    scanf(" %99[^\n]", newTask.title);

    char priorityBuf[10];
    do {
        printf("Enter priority (High/Medium/Low): ");
        scanf(" %9[^\n]", priorityBuf);
        if (strcmp(priorityBuf, "High") != 0 &&
            strcmp(priorityBuf, "Medium") != 0 &&
            strcmp(priorityBuf, "Low") != 0) {
            printf("Please enter exactly: High, Medium, or Low.\n");
        }
    } while (strcmp(priorityBuf, "High") != 0 &&
             strcmp(priorityBuf, "Medium") != 0 &&
             strcmp(priorityBuf, "Low") != 0);
    strcpy(newTask.priority, priorityBuf);

    strcpy(newTask.status, "Pending");

    tasks[taskCount] = newTask;
    taskCount++;
    nextId++;

    saveTasks();

    printf("Task added successfully.\n");
}

void viewTasks() {

    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {

        printf("\nID: %d\n", tasks[i].id);
        printf("Date: %s\n", tasks[i].date);
        printf("Task: %s\n", tasks[i].title);
        printf("Priority: %s\n", tasks[i].priority);
        printf("Status: %s\n", tasks[i].status);
    }
}

void searchByDate() {

    char searchDate[20];
    int found = 0;

    printf("Enter date (DD-MM-YYYY): ");
    scanf(" %19[^\n]", searchDate);

    printf("\nTasks for %s:\n", searchDate);

    for (int i = 0; i < taskCount; i++) {

        if (strcmp(tasks[i].date, searchDate) == 0) {

            printf("\nID: %d\n", tasks[i].id);
            printf("Task: %s\n", tasks[i].title);
            printf("Priority: %s\n", tasks[i].priority);
            printf("Status: %s\n", tasks[i].status);

            found = 1;
        }
    }

    if (!found) {
        printf("No task found for this date.\n");
    }
}

void completeTask() {

    int id;

    printf("Enter task ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    for (int i = 0; i < taskCount; i++) {

        if (tasks[i].id == id) {

            strcpy(tasks[i].status, "Done");

            saveTasks();

            printf("Task completed.\n");
            return;
        }
    }

    printf("Task not found.\n");
}

void deleteTask() {

    int id;

    printf("Enter task ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }

    for (int i = 0; i < taskCount; i++) {

        if (tasks[i].id == id) {

            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }

            taskCount--;

            saveTasks();

            printf("Task deleted.\n");
            return;
        }
    }

    printf("Task not found.\n");
}

void saveTasks() {
    FILE *fp = fopen("tasks.txt", "w");

    if (fp == NULL) {
        printf("File could not be opened.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(fp, "%d|%s|%s|%s|%s\n",
                tasks[i].id,
                tasks[i].date,
                tasks[i].title,
                tasks[i].priority,
                tasks[i].status);
    }

    fclose(fp);
}

void dashboard() {

    int choice;
    while (1) {

        printf("\n");
        printf("=====================================\n");
        printf("          TASK MANAGER\n");
        printf("=====================================\n");
        printf("  1. Add Task\n");
        printf("  2. View All Tasks\n");
        printf("  3. Search Task by Date\n");
        printf("  4. Complete Task\n");
        printf("  5. Delete Task\n");
        printf("  6. Exit\n");
        printf("=====================================\n");

        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {

            case 1:
                addTask();
                break;

            case 2:
                viewTasks();
                break;

            case 3:
                searchByDate();
                break;

            case 4:
                completeTask();
                break;

            case 5:
                deleteTask();
                break;

            case 6:
                printf("\nThank you for using Task Manager!\n");
                return;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
}





