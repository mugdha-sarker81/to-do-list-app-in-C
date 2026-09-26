#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "habits.h"
#include "calendar.h"

struct Task {
    int id;
    char date[20];
    char title[100];
    char priority[10];
    char status[15];
};

#define MAX_TASKS 1000000

struct Task tasks[MAX_TASKS];
int taskCount = 0;
int nextId = 1;

void clearScreen();
void clearInputBuffer();
void dashboard();
void loadTasks();
void saveTasks();
void addTask();
void viewTasks();
void searchByDate();
void completeTask();
void deleteTask();
int validDate(char *date);
int cmpByDate(const void *a, const void *b);
long dateToKey(const char *date);
void askuser();

int main(){
    loadTasks();
    loadHabits();
    loadLogs();
    dashboard();
    return 0;
}

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen(){
    system("cls");   // Windows
    // system("clear"); // Linux/Mac এর জন্য এটা ব্যবহার করো
}

int validDate(char *date){
    if (strlen(date) != 10) return 0;
    if (date[2] != '-' || date[5] != '-') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)date[i])) return 0;
    }

    int d, m, y;
    sscanf(date, "%2d-%2d-%4d", &d, &m, &y);
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > 31) return 0;
    return 1;
}

long dateToKey(const char *date){
    int d, m, y;
    sscanf(date, "%2d-%2d-%4d", &d, &m, &y);
    return (long)y * 10000L + (long)m * 100L + d;
}

int cmpByDate(const void *a, const void *b){
    const struct Task *ta = (const struct Task *)a;
    const struct Task *tb = (const struct Task *)b;
    long ka = dateToKey(ta->date);
    long kb = dateToKey(tb->date);
    if (ka != kb) return (ka < kb) ? -1 : 1;
    return ta->id - tb->id;
}

void loadTasks(){
    FILE *fp = fopen("tasks.txt", "r");
    if (!fp) return;

    taskCount = 0;
    nextId = 1;
    struct Task tmp;

    while (taskCount < MAX_TASKS && fscanf(fp, "%d|%19[^|]|%99[^|]|%9[^|]|%14[^\n]",
                  &tmp.id, tmp.date, tmp.title, tmp.priority, tmp.status) == 5)
    {
        int c = fgetc(fp);
        if (c != '\n' && c != EOF) ungetc(c, fp);

        if (tmp.id >= nextId) nextId = tmp.id + 1;
        tasks[taskCount++] = tmp;
    }
    fclose(fp);
    qsort(tasks, taskCount, sizeof(struct Task), cmpByDate);
}

void saveTasks(){
    FILE *fp = fopen("tasks.txt", "w");
    if (!fp) {
        printf("Could not save tasks.\n");
        return;
    }

    qsort(tasks, taskCount, sizeof(struct Task), cmpByDate);
    for (int i = 0; i < taskCount; i++){
        fprintf(fp, "%d|%s|%s|%s|%s\n",
                tasks[i].id, tasks[i].date, tasks[i].title,
                tasks[i].priority, tasks[i].status);
    }
    fclose(fp);
}

void addTask() {
    clearScreen();
    if (taskCount >= MAX_TASKS) {
        printf("Task limit reached.\n");
        return;
    }

    struct Task tmp;
    tmp.id = nextId++;

    do {
        printf("Enter date (DD-MM-YYYY): ");
        scanf("%19s", tmp.date);
        if (!validDate(tmp.date))
            printf("Invalid date. Please use DD-MM-YYYY.\n");
    } while (!validDate(tmp.date));

    clearInputBuffer();

    printf("Enter task title: ");
    fgets(tmp.title, sizeof(tmp.title), stdin);
    tmp.title[strcspn(tmp.title, "\n")] = 0;

    do {
        printf("Enter priority (High/Medium/Low): ");
        scanf("%9s", tmp.priority);
        if (strcmp(tmp.priority, "High") && strcmp(tmp.priority, "Medium") && strcmp(tmp.priority, "Low"))
            printf("Invalid priority.\n");
    } while (strcmp(tmp.priority, "High") && strcmp(tmp.priority, "Medium") && strcmp(tmp.priority, "Low"));

    strcpy(tmp.status, "Pending");
    tasks[taskCount++] = tmp;
    saveTasks();
    printf("\nTask added successfully!\n");
}

void viewTasks() {
    clearScreen();
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (!strcmp(tasks[i].status, "Pending")) {
            printf("\n%d | %s | %s | Priority: %s | Status: %s\n",
                   tasks[i].id, tasks[i].date, tasks[i].title,
                   tasks[i].priority, tasks[i].status);
            found = 1;
        }
    }
    if (!found) printf("\nNo unfinished tasks.\n");
    askuser();
}

void searchByDate() {
    char date[20];
    int found = 0;

    printf("Enter date (DD-MM-YYYY): ");
    scanf("%19s", date);
    if (!validDate(date)) {
        printf("Invalid date format.\n");
        return;
    }

    clearScreen();
    printf("\n=======Tasks for %s:=========\n\n", date);
    for (int i = 0; i < taskCount; i++) {
        if (!strcmp(tasks[i].date, date)) {
            printf("\n%d | %s | Priority: %s | Status: %s\n",
                   tasks[i].id, tasks[i].title,
                   tasks[i].priority, tasks[i].status);
            found = 1;
        }
    }
    if (!found) printf("[]No task found for this date.\n");
    askuser();
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
            printf("Task marked as completed.\n");
            return;
        }
    }
    printf("Task not found.\n");
}

void deleteTask() {
    int id;
    printf("\nEnter task ID: ");
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

void askuser(){
    int choice;
    while (1){
        printf("\n=====================================\n");
        printf("            want to customize ?\n");
        printf("=====================================\n");
        printf("1. Add Task\n");
        printf("2. Mark a Task done\n");
        printf("3. Delete Task\n");
        printf("4. back to dashboard\n");
        printf("=====================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        switch (choice) {
            case 1: addTask(); break;
            case 2: completeTask(); break;
            case 3: deleteTask(); break;
            case 4: dashboard(); break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void dashboard() {
    clearScreen();
    int choice;
    while (1){
        printf("\n=====================================\n");
        printf("Today: %d%%   Streak: %d day(s)\n", todayPerformance(), currentStreak());
        printf("=====================================\n");
        printf("            TASK MANAGER\n");
        printf("=====================================\n");
        printf("1. Add Task\n");
        printf("2. View All pending Tasks\n");
        printf("3. Search Task by Date\n");
        printf("4. Mark a Task done\n");
        printf("5. Delete Task\n");
        printf("6. Daily Habits dashboard\n");
        printf("7. Show Calendar\n");
        printf("8. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: searchByDate(); break;
            case 4: {
                viewTasks();
                completeTask();
                printf("\n=========back to dashboard (press 5): ");
                while (1) {
                    int ch; scanf("%d", &ch);
                    if (ch == 5) { dashboard(); break; }
                    else printf("\nInvalid choice! Please press '5' again: ");
                }
                break;
            }
            case 5: {
                viewTasks();
                deleteTask();
                printf("\n=========back to dashboard (press 5): ");
                while (1) {
                    int ch; scanf("%d", &ch);
                    if (ch == 5) { dashboard(); break; }
                    else printf("\nInvalid choice! Please press '5' again: ");
                }
                break;
            }
            case 6: habitboard(); break;
            case 7: {
                int year, month;
                printf("Enter month and year (e.g. 9 2026): ");
                scanf("%d %d", &month, &year);

                if (month < 1 || month > 12) {
                    printf("Invalid month!\n");
                } else {
                    clearScreen();
                    showCalendar(year, month);
                    printf("\n\nPress Enter to go back to dashboard...");
                    clearInputBuffer();
                    getchar();
                    clearScreen();
                }
                break;
            }
            case 8:
                printf("\nThank you for using Task Manager!\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}