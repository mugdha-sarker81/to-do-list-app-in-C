#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ==================== Data Structure ====================

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
int nextId = 1;

// ==================== Function Prototypes ====================

void dashboard();
void loadTasks();
void saveTasks();
void addTask();
void viewTasks();
void searchByDate();
void completeTask();
void deleteTask();

int validateDate(char *date);
void clearInputBuffer();

// ==================== Main ====================

int main() {
    loadTasks();
    dashboard();

    return 0;
}

// ==================== Utility Functions ====================

void clearInputBuffer() {
    int c;

    while ((c = getchar()) != '\n' && c != EOF);
}

// Checks DD-MM-YYYY format
int validateDate(char *date) {
    if (strlen(date) != 10)
        return 0;

    if (date[2] != '-' || date[5] != '-')
        return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5)
            continue;

        if (!isdigit(date[i]))
            return 0;
    }

    int day, month, year;

    sscanf(date, "%2d-%2d-%4d", &day, &month, &year);

    if (month < 1 || month > 12)
        return 0;

    if (day < 1 || day > 31)
        return 0;

    return 1;
}

// ==================== File Handling ====================

void loadTasks() {
    FILE *fp = fopen("tasks.txt", "r");

    if (fp == NULL)
        return;

    taskCount = 0;
    nextId = 1;

    while (taskCount < MAX_TASKS &&
           fscanf(fp, "%d|%19[^|]|%99[^|]|%9[^|]|%14[^\n]",
                  &tasks[taskCount].id,
                  tasks[taskCount].date,
                  tasks[taskCount].title,
                  tasks[taskCount].priority,
                  tasks[taskCount].status) == 5) {

        if (tasks[taskCount].id >= nextId)
            nextId = tasks[taskCount].id + 1;

        taskCount++;
    }

    fclose(fp);
}

void saveTasks() {
    FILE *fp = fopen("tasks.txt", "w");

    if (fp == NULL) {
        printf("Could not save tasks.\n");
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

// ==================== Add Task ====================

void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task limit reached.\n");
        return;
    }

    struct Task newTask;

    newTask.id = nextId++;

    // Date
    do {
        printf("Enter date (DD-MM-YYYY): ");
        scanf("%19s", newTask.date);

        if (!validateDate(newTask.date))
            printf("Invalid date. Please use DD-MM-YYYY.\n");

    } while (!validateDate(newTask.date));

    clearInputBuffer();

    // Title
    printf("Enter task title: ");
    fgets(newTask.title, sizeof(newTask.title), stdin);
    newTask.title[strcspn(newTask.title, "\n")] = '\0';

    // Priority
    do {
        printf("Enter priority (High/Medium/Low): ");
        scanf("%9s", newTask.priority);

        if (strcmp(newTask.priority, "High") != 0 &&
            strcmp(newTask.priority, "Medium") != 0 &&
            strcmp(newTask.priority, "Low") != 0) {

            printf("Invalid priority.\n");
        }

    } while (strcmp(newTask.priority, "High") != 0 &&
             strcmp(newTask.priority, "Medium") != 0 &&
             strcmp(newTask.priority, "Low") != 0);

    strcpy(newTask.status, "Pending");

    tasks[taskCount] = newTask;
    taskCount++;

    saveTasks();

    printf("Task added successfully!\n");
}

// ==================== View Tasks ====================

void viewTasks() {
    int found = 0;

    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].status, "Pending") == 0) {

           // printf("\nID       : %d", tasks[i].id);
           // printf("\nDate     : %s", tasks[i].date);
           // printf("\nTitle    : %s", tasks[i].title);
            //printf("\nPriority : %s", tasks[i].priority);
           // printf("\nStatus   : %s\n", tasks[i].status);

            printf("\n%d | %s | %s | Priority: %s | Status: %s\n",
                   tasks[i].id,tasks[i].date,
                   tasks[i].title,
                   tasks[i].priority,
                   tasks[i].status);

            found = 1;
        }
    }

    if (!found)
        printf("\nNo unfinished tasks.\n");

}

// ==================== Search By Date ====================

void searchByDate() {
    char searchDate[20];
    int found = 0;

    printf("Enter date (DD-MM-YYYY): ");
    scanf("%19s", searchDate);

    if (!validateDate(searchDate)) {
        printf("Invalid date format.\n");
        return;
    }

    printf("\nTasks for %s:\n", searchDate);

    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].date, searchDate) == 0) {

            printf("\n%d | %s | Priority: %s | Status: %s\n",
                   tasks[i].id,
                   tasks[i].title,
                   tasks[i].priority,
                   tasks[i].status);

            found = 1;
        }
    }

    if (!found)
        printf("No task found for this date.\n");
}

// ==================== Complete Task ====================

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

// ==================== Delete Task ====================

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

            for (int j = i; j < taskCount - 1; j++)
                tasks[j] = tasks[j + 1];

            taskCount--;

            saveTasks();

            printf("Task deleted.\n");
            return;
        }
    }

    printf("Task not found.\n");
}

// ==================== Dashboard ====================

void dashboard() {
    int choice;

    while (1) {

        printf("\n=====================================\n");
        printf("            TASK MANAGER\n");
        printf("=====================================\n");
        printf("1. Add Task\n");
        printf("2. View All Tasks\n");
        printf("3. Search Task by Date\n");
        printf("4. Complete Task\n");
        printf("5. Delete Task\n");
        printf("6. Exit\n");
        printf("=====================================\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
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
                printf("Invalid choice! Please try again.\n");
        }
    }
}



