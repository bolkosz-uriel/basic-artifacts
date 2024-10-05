#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TITLE_LEN 50
#define MAX_DESC_LEN 200

// Task struct
typedef struct {
    char title[MAX_TITLE_LEN];
    char description[MAX_DESC_LEN];
    int priority;   // 1 = Low, 2 = Medium, 3 = High
    int completed;  // 0 = Incomplete, 1 = Complete
} Task;

// Function Prototypes
void add_task(Task tasks[], int *task_count);
void view_tasks(Task tasks[], int task_count);
void mark_task_completed(Task tasks[], int task_count);
void delete_task(Task tasks[], int *task_count);
void save_tasks(Task tasks[], int task_count);
void load_tasks(Task tasks[], int *task_count);

int main() {
    Task tasks[MAX_TASKS];
    int task_count = 0;
    int choice;

    // Load tasks from file at the start
    load_tasks(tasks, &task_count);

    while (1) {
        // Menu
        printf("\nTask Manager\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Task\n");
        printf("5. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_task(tasks, &task_count);
                break;
            case 2:
                view_tasks(tasks, task_count);
                break;
            case 3:
                mark_task_completed(tasks, task_count);
                break;
            case 4:
                delete_task(tasks, &task_count);
                break;
            case 5:
                save_tasks(tasks, task_count);
                printf("Tasks saved. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Function to add a task
void add_task(Task tasks[], int *task_count) {
    if (*task_count >= MAX_TASKS) {
        printf("Task limit reached. Cannot add more tasks.\n");
        return;
    }

    Task new_task;
    printf("Enter task title: ");
    getchar();  // To consume newline character from previous input
    fgets(new_task.title, MAX_TITLE_LEN, stdin);
    new_task.title[strcspn(new_task.title, "\n")] = 0;  // Remove newline

    printf("Enter task description: ");
    fgets(new_task.description, MAX_DESC_LEN, stdin);
    new_task.description[strcspn(new_task.description, "\n")] = 0;  // Remove newline

    printf("Enter priority (1 - Low, 2 - Medium, 3 - High): ");
    scanf("%d", &new_task.priority);
    new_task.completed = 0;  // Default: Task not completed

    tasks[*task_count] = new_task;
    (*task_count)++;

    printf("Task added successfully.\n");
}

// Function to view all tasks
void view_tasks(Task tasks[], int task_count) {
    if (task_count == 0) {
        printf("No tasks to display.\n");
        return;
    }

    printf("\nList of Tasks:\n");
    for (int i = 0; i < task_count; i++) {
        printf("%d. [%s] %s (Priority: %d)\n", i + 1, tasks[i].completed ? "X" : " ", tasks[i].title, tasks[i].priority);
        printf("   Description: %s\n", tasks[i].description);
    }
}

// Function to mark a task as completed
void mark_task_completed(Task tasks[], int task_count) {
    int task_num;
    printf("Enter the number of the task to mark as completed: ");
    scanf("%d", &task_num);

    if (task_num < 1 || task_num > task_count) {
        printf("Invalid task number.\n");
        return;
    }

    tasks[task_num - 1].completed = 1;  // Mark the task as completed
    printf("Task marked as completed.\n");
}

// Function to delete a task
void delete_task(Task tasks[], int *task_count) {
    int task_num;
    printf("Enter the number of the task to delete: ");
    scanf("%d", &task_num);

    if (task_num < 1 || task_num > *task_count) {
        printf("Invalid task number.\n");
        return;
    }

    // Shift all tasks after the deleted one
    for (int i = task_num - 1; i < *task_count - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    (*task_count)--;  // Reduce the task count
    printf("Task deleted successfully.\n");
}

// Function to save tasks to a file
void save_tasks(Task tasks[], int task_count) {
    FILE *file = fopen("tasks.txt", "w");
    if (file == NULL) {
        printf("Error saving tasks.\n");
        return;
    }

    for (int i = 0; i < task_count; i++) {
        fprintf(file, "%s\n%s\n%d\n%d\n", tasks[i].title, tasks[i].description, tasks[i].priority, tasks[i].completed);
    }

    fclose(file);
}

// Function to load tasks from a file
void load_tasks(Task tasks[], int *task_count) {
    FILE *file = fopen("tasks.txt", "r");
    if (file == NULL) {
        printf("No previous tasks found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, " %[^\n] %[^\n] %d %d", tasks[*task_count].title, tasks[*task_count].description, &tasks[*task_count].priority, &tasks[*task_count].completed) != EOF) {
        (*task_count)++;
    }

    fclose(file);
    printf("Tasks loaded from file.\n");
}
