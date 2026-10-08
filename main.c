#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"
#include "habits.h"
#include "calendar.h"
#include "export.h"

void clearScreen();
void clearInputBuffer();
void dashboard();
void printTutorial();

int main(int argc, char *argv[]) {

    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {

            printf("\n============================================================\n");
            printf("              TASK MANAGER & HABIT TRACKER\n");
            printf("============================================================\n\n");
            printf("Usage:  ");
            printf("  ./todo [option]\n\n");

            printf("Commands:\n");
            printf("  -h, --help              Show this help message\n");
            printf("  --clear                 Clear all saved tasks and habits\n");
            printf("  --date DD-MM-YYYY       View tasks for a specific date\n");
            printf("  --habit                 Open the Daily Habits dashboard\n");
            printf("  --report                Generate and open the HTML task report\n");
            printf("  --data                  Show where your data is saved\n");
            printf("  --tut                   Open the quick tutorial\n\n");

            printf("Tip: Run './todo --tut' if you're using the app for the first time.\n");
            printf("============================================================\n\n");

            return 0;
        }
        else if (strcmp(argv[1], "--tut") == 0) {
            printTutorial();
            return 0;
        }
        else if (strcmp(argv[1], "--data") == 0) {
            printf("------------------------------------------------------------\n");
            printf("             YOUR DATA\n");
            printf("------------------------------------------------------------\n");
            printf(" Your progress is automatically saved in:\n");
            printf(" • tasks.txt → Your tasks\n");
            printf(" • habits.txt → Your habits\n");
            printf(" • habit_log.txt → Your habit history\n\n");
            return 0;
        }
        else if (strcmp(argv[1], "--report") == 0) {
            if (exportTasksToHTML() != 0) {
                fprintf(stderr, "Could not generate the task report.\n");
                return 1;
            }

            #ifdef _WIN32
                        const char *openCommand = "start \"\" \"report.html\"";
            #elif defined(__APPLE__)
                        const char *openCommand = "open \"report.html\"";
            #else
                        const char *openCommand = "xdg-open \"report.html\"";
            #endif
            
            if (system(openCommand) != 0) {
                fprintf(stderr, "Report created, but could not open it. "
                        "Open report.html manually.\n");
                return 1;
            }

            printf("Report created and opened: report.html\n");
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
        printf("8. Export tasks to HTML\n");
        printf("9. Exit\n");
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
                exportTasksToHTML();
                printf("Press Enter to continue...");
                clearInputBuffer();
                getchar();
                break;
            case 9:
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

void printTutorial() {
    printf("\n");
    printf("============================================================\n"); 
    printf(" TASK MANAGER & HABIT TRACKER - GUIDE\n"); 
    printf("============================================================\n\n"); 
    printf("Welcome! \n"); 
    printf("This app helps you organize your daily tasks and habits.\n"); 
    printf("Choose an option from the menu and follow the instructions.\n\n"); 
    printf("------------------------------------------------------------\n"); 
    printf("  TASKS\n"); 
    printf("------------------------------------------------------------\n"); 
    printf(" [1] Add Task\n"); 
    printf(" \tCreate a new task with a date, title, and priority.\n"); 
    printf(" [2] View Tasks\n"); 
    printf(" \tSee all your unfinished tasks in one place.\n"); 
    printf(" [3] Find Tasks by Date\n"); 
    printf(" \tEnter a date to see what you need to do that day.\n"); 
    printf(" [4] Complete a Task\n"); 
    printf(" \tFinished something? Mark it as DONE using its ID.\n"); 
    printf(" [5] Delete a Task\n"); 
    printf(" \tRemove a task you no longer need using its ID.\n"); 
    printf("------------------------------------------------------------\n"); 
    printf("  HABITS & PLANNING\n"); 
    printf("------------------------------------------------------------\n"); 
    printf(" [6] Habit Dashboard\n"); 
    printf(" \tAdd habits and track how well you are doing today.\n"); 
    printf(" [7] Calendar\n"); 
    printf(" \tPick a month and year to see your task calendar.\n"); 
    printf(" [8] Export Report\n"); 
    printf(" \tCreate a report.html file to view your tasks in a browser.\n"); 
    printf(" [9] Exit\n"); 
    printf(" \tSave your progress and close the application.\n\n");
    printf(" Tip: Start with [1] Add Task and create your first task!\n"); 
    printf("============================================================\n");
    return;
}