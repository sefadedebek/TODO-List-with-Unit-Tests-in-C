#ifndef TODO_H
#define TODO_H

#define MAX_TASKS 100
#define TASK_LENGTH 256

typedef struct {
    char task[TASK_LENGTH];
    int completed;
} Todo;

void addTask(const char* newTask);
int deleteTask(int index);
int completeTask(int index);
int getTaskCount();
const Todo* getTask(int index);

#endif
