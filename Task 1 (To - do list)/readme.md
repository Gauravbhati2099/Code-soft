# C++ To-Do List Manager

This is a console-based To-Do List Manager built in C++. It allows users to manage tasks with features like adding, editing, completing, deleting tasks, and assigning priorities. Additionally, the tasks can be saved to or loaded from a file to maintain the task list between sessions.

## Features

- **Add Tasks**: Users can add new tasks with a description and priority (Low, Medium, High).
- **View Tasks**: View all tasks in the to-do list, including their status (Completed/Pending) and priority.
- **Edit Tasks**: Modify the description of any existing task.
- **Complete Tasks**: Mark tasks as completed.
- **Delete Tasks**: Remove tasks from the list.
- **Task Prioritization**: Tasks are prioritized as Low (0), Medium (1), or High (2).
- **File Operations**: 
  - **Save Tasks**: Save the current task list to a file (`tasks.csv`).
  - **Load Tasks**: Load tasks from a file if previously saved.

## How to Run

1. Clone this repository or download the source code files.
2. Compile the project using a C++ compiler, such as g++:
   ```bash
   g++ main.cpp -o todo_manager
3. Run the project:
   ```bash
        ./todo_manager
