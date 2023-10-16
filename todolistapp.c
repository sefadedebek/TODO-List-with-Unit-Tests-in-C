#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define TASK_LENGTH 256

typedef struct {
    char task[TASK_LENGTH];
    int completed;
} Todo;

Todo tasks[MAX_TASKS];
int taskCount = 0;

void displayMenu() {
    printf("\nTODO LIST MENU\n");
    printf("1. Add Task\n");
    printf("2. Delete Task\n");
    printf("3. Display Tasks\n");
    printf("4. Complete Task\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

void addTask() {
    if(taskCount < MAX_TASKS) {
        printf("\nEnter new task: ");
        getchar();  // Clear newline character left by previous input
        fgets(tasks[taskCount].task, TASK_LENGTH, stdin);
        tasks[taskCount].task[strcspn(tasks[taskCount].task, "\n")] = '\0';  // Remove newline character
        tasks[taskCount].completed = 0;
        taskCount++;
        printf("Task added!\n");
    } else {
        printf("\nReached maximum task limit!\n");
    }
}

void deleteTask() {
    int index;
    printf("\nEnter the number of the task you want to delete: ");
    scanf("%d", &index);
    if(index < 1 || index > taskCount) {
        printf("Invalid number!\n");
        return;
    }

    for(int i = index - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i+1];
    }
    taskCount--;
    printf("Task deleted!\n");
}

void displayTasks() {
    if(taskCount == 0) {
        printf("\nTask list is empty.\n");
        return;
    }
    printf("\nTODO LIST:\n");
    for(int i = 0; i < taskCount; i++) {
        printf("%d. %s %s\n", i+1, tasks[i].task, tasks[i].completed ? "(Completed)" : "");
    }
}

void completeTask() {
    int index;
    printf("\nEnter the number of the task you want to mark as completed: ");
    scanf("%d", &index);
    if(index < 1 || index > taskCount) {
        printf("Invalid number!\n");
        return;
    }

    tasks[index - 1].completed = 1;
    printf("Task marked as completed!\n");
}

int main() {
    int choice;
    while(1) {
        displayMenu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addTask();
                break;
            case 2:
                deleteTask();
                break;
            case 3:
                displayTasks();
                break;
            case 4:
                completeTask();
                break;
            case 5:
                printf("\nExiting...\n");
                return 0;
            default:
                printf("\nInvalid choice!\n");
        }
    }
}
