#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100

struct Task {
    char name[50];
    char dueDate[20];
    int priority;
    int completed;
};

struct Task tasks[MAX_TASKS];
int taskCount = 0;

void loadTasks() {
    FILE *file = fopen("tasks.txt", "r");

    if (file == NULL) return;

    while (fscanf(file, "%s %s %d %d",
        tasks[taskCount].name,
        tasks[taskCount].dueDate,
        &tasks[taskCount].priority,
        &tasks[taskCount].completed) != EOF) {

        taskCount++;
    }

    fclose(file);
}

void saveTasks() {
    FILE *file = fopen("tasks.txt", "w");

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%s %s %d %d\n",
            tasks[i].name,
            tasks[i].dueDate,
            tasks[i].priority,
            tasks[i].completed);
    }

    fclose(file);
}

void addTask() {

    printf("Enter task name: ");
    scanf("%s", tasks[taskCount].name);

    printf("Enter due date: ");
    scanf("%s", tasks[taskCount].dueDate);

    printf("Enter priority (1-5): ");
    scanf("%d", &tasks[taskCount].priority);

    tasks[taskCount].completed = 0;

    taskCount++;

    printf("Task added successfully!\n");
}

void viewTasks() {

    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {

        printf("\nTask %d\n", i + 1);
        printf("Name: %s\n", tasks[i].name);
        printf("Due Date: %s\n", tasks[i].dueDate);
        printf("Priority: %d\n", tasks[i].priority);

        if (tasks[i].completed)
            printf("Status: Completed\n");
        else
            printf("Status: Not Completed\n");
    }
}

void markCompleted() {

    int num;

    printf("Enter task number to mark as completed: ");
    scanf("%d", &num);

    if (num < 1 || num > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    tasks[num - 1].completed = 1;

    printf("Task marked as completed!\n");
}

void deleteTask() {

    int num;

    printf("Enter task number to delete: ");
    scanf("%d", &num);

    if (num < 1 || num > taskCount) {
        printf("Invalid task number.\n");
        return;
    }

    for (int i = num - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    taskCount--;

    printf("Task deleted successfully!\n");
}

int main() {

    int choice;

    loadTasks();

    do {

        printf("\n===== TO DO LIST MANAGER =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task Completed\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            addTask();
            break;

        case 2:
            viewTasks();
            break;

        case 3:
            markCompleted();
            break;

        case 4:
            deleteTask();
            break;

        case 5:
            saveTasks();
            printf("Tasks saved. Goodbye!\n");
            break;

        default:
            printf("Invalid choice.\n");
        }

    } while (choice != 5);

    return 0;
}