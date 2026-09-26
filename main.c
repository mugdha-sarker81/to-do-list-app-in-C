#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "habits.h"
#include "calendar.h"

void clearScreen();
void clearInputBuffer();
void dashboard();


int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            printf("Task Manager & Daily Habit Tracker\n");
            printf("Usage: ./todo [option]\n\n");
            printf("Options:\n");
            printf("  -h, --help              Show this help message\n");
            printf("  --clear                 Clear all saved data\n");
            printf("  --date DD-MM-YYYY       Show tasks of a specific date\n");
            printf("  --habit                 Open Daily Habits dashboard\n");
            return 0;
        }
        else if (strcmp(argv[1], "--clear") == 0) {
            remove("tasks.txt");
            remove("habits.txt");
            remove("habit_log.txt");
            printf("All data cleared successfully.\n");
            return 0;
        }
        else if (strcmp(argv[1], "--date") == 0) {
            if (argc < 3) {
                printf("Please provide a date. Example: ./todo --date 26-09-2026\n");
                return 1;
            }
            loadTasks();
            char *date = argv[2];
            if (!validDate(date)) {
                printf("Invalid date format. Use DD-MM-YYYY\n");
                free(tasks);
                return 1;
            }
            printf("\n======= Tasks for %s =======\n\n", date);
            int found = 0;
            for (int i = 0; i < taskCount; i++) {
                if (!strcmp(tasks[i].date, date)) {
                    printf("%d | %s | Priority: %s | Status: %s\n",
                           tasks[i].id, tasks[i].title,
                           tasks[i].priority, tasks[i].status);
                    found = 1;
                }
            }
            if (!found) printf("No tasks found for this date.\n");
            free(tasks);
            return 0;
        }
        else if (strcmp(argv[1], "--habit") == 0) {
            loadTasks();
            loadHabits();
            loadLogs();
            habitboard();
            free(tasks);
            return 0;
        }
        else {
            printf("Unknown option: %s\n", argv[1]);
            printf("Use --help for available options.\n");
            return 1;
        }
    }

    loadTasks();
    loadHabits();
    loadLogs();
    dashboard();

    free(tasks);
    return 0;
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
                free(tasks);
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}

void clearInputBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen(){
    system("cls");
}

