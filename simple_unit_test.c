#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_TASKS 100
#define TASK_LENGTH 256

typedef struct {
    char task[TASK_LENGTH];
    int completed;
} Todo;

static Todo tasks[MAX_TASKS];
static int taskCount = 0;

static void addTask(const char* newTask) {
    if(taskCount < MAX_TASKS) {
        strncpy(tasks[taskCount].task, newTask, TASK_LENGTH);
        tasks[taskCount].completed = 0;
        taskCount++;
    }
}

static int deleteTask(int index) {
    if(index < 1 || index > taskCount) {
        return -1;  // Invalid index
    }
    for(int i = index - 1; i < taskCount - 1; i++) {
        tasks[i] = tasks[i+1];
    }
    taskCount--;
    return 0;  // Success
}

static int completeTask(int index) {
    if(index < 1 || index > taskCount) {
        return -1;  // Invalid index
    }
    tasks[index - 1].completed = 1;
    return 0;  // Success
}

// Unit Tests
static void test_addTask() {
    // Reset task count for fresh testing environment
    taskCount = 0;

    // Test: Add a single task
    addTask("Test Task 1");
    assert(strcmp(tasks[0].task, "Test Task 1") == 0);
    assert(tasks[0].completed == 0);
    assert(taskCount == 1);

    // Test: Add multiple tasks
    addTask("Test Task 2");
    assert(strcmp(tasks[1].task, "Test Task 2") == 0);
    assert(taskCount == 2);

    // Test: Add tasks until maximum
    for (int i = 3; i <= MAX_TASKS; i++) {
        char buffer[TASK_LENGTH];
        snprintf(buffer, TASK_LENGTH, "Test Task %d", i);
        addTask(buffer);
    }
    assert(taskCount == MAX_TASKS);

    // Test: Try adding beyond maximum - expect no changes
    addTask("This should not be added");
    assert(taskCount == MAX_TASKS);
}

static void test_deleteTask() {
    // Setup: Populate tasks
    taskCount = 3;
    strcpy(tasks[0].task, "Test Task 1");
    strcpy(tasks[1].task, "Test Task 2");
    strcpy(tasks[2].task, "Test Task 3");

    // Test: Delete a middle task
    assert(deleteTask(2) == 0);
    assert(taskCount == 2);
    assert(strcmp(tasks[1].task, "Test Task 3") == 0);

    // Test: Delete an invalid index (too low)
    assert(deleteTask(0) == -1);

    // Test: Delete an invalid index (too high)
    assert(deleteTask(10) == -1);
}

static void test_completeTask() {
    // Setup: Populate tasks
    taskCount = 2;
    strcpy(tasks[0].task, "Test Task 1");
    tasks[0].completed = 0;
    strcpy(tasks[1].task, "Test Task 2");
    tasks[1].completed = 0;

    // Test: Complete a valid task
    assert(completeTask(1) == 0);
    assert(tasks[0].completed == 1);

    // Test: Try an invalid index (too low)
    assert(completeTask(0) == -1);

    // Test: Try an invalid index (too high)
    assert(completeTask(10) == -1);
}

int main() {
    // Run Unit Tests
    test_addTask();
    test_deleteTask();
    test_completeTask();
    printf("All unit tests passed!\n");
    return 0;
}
