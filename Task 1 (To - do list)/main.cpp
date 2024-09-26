#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits> // For std::numeric_limits

using namespace std;

class Task {
private:
    string description;
    bool isCompleted;
    int priority; // New member variable for task priority

public:
    Task(const string &desc, int prio = 0, bool completed = false) 
        : description(desc), isCompleted(completed), priority(prio) {}

    string getDescription() const { return description; }
    void setDescription(const string &desc) { description = desc; }

    bool getStatus() const { return isCompleted; }
    void setStatus(bool status) { isCompleted = status; }

    void toggleStatus() { isCompleted = !isCompleted; }

    int getPriority() const { return priority; }
    void setPriority(int prio) { priority = prio; }
};

class TaskManager {
private:
    vector<Task> tasks;
    bool tasksLoaded; // Flag to check if tasks are loaded

public:
    TaskManager() : tasksLoaded(false) {} // Initialize tasksLoaded to false

    void addTask(const Task &task) {
        tasks.push_back(task);
    }

    void viewTasks(bool showCompleted = true) {
        cout << "To-DO list: " << endl;
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
            return;
        }
        for (size_t i = 0; i < tasks.size(); i++) {
            if (showCompleted || !tasks[i].getStatus()) {
                cout << i + 1 << ". " << tasks[i].getDescription() << " ("
                     << (tasks[i].getStatus() ? "Completed" : "Pending") << ", Priority: " 
                     << tasks[i].getPriority() << ")" << endl;
            }
        }
    }

    void completeTask(size_t index) {
        if (index < tasks.size()) {
            tasks[index].setStatus(true);
            cout << "Task marked as completed." << endl;
        } else {
            cout << "Invalid task number." << endl;
        }
    }

    void deleteTask(size_t index) {
        if (index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
            cout << "Task deleted." << endl;
        } else {
            cout << "Invalid task number." << endl;
        }
    }

    void editTask(size_t index) {
        if (index < tasks.size()) {
            string newDescription;
            cout << "Enter new description for the task: ";
            cin.ignore();
            getline(cin, newDescription);
            tasks[index].setDescription(newDescription);
            cout << "Task updated." << endl;
        } else {
            cout << "Invalid task number." << endl;
        }
    }

    void loadTasks(const string &filename) {
        if (tasksLoaded) { // Check if tasks have already been loaded
            cout << "Tasks have already been loaded from the file." << endl;
            return;
        }

        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string desc;
                int prio;
                bool completed;

                // Improved error handling for malformed CSV lines
                if (getline(ss, desc, ',') && (ss >> prio) && (ss.ignore() && (ss >> completed))) {
                    tasks.emplace_back(desc, prio, completed);
                } else {
                    cout << "Malformed line in file: " << line << endl;
                }
            }
            file.close();
            tasksLoaded = true; // Set tasksLoaded to true after successful loading
            cout << "Tasks loaded successfully." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }

    void saveTasks(const string &filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const auto &task : tasks) {
                file << task.getDescription() << "," 
                     << task.getPriority() << "," 
                     << task.getStatus() << endl;
            }
            file.close();
            cout << "Tasks saved successfully." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }
};

void displayMenu() {
    cout << "\n---- TO-DO List Manager ----\n";
    cout << "1. Add Task\n";
    cout << "2. View Tasks\n";
    cout << "3. Complete Task\n";
    cout << "4. Delete Task\n";
    cout << "5. Edit Task\n";
    cout << "6. Save Tasks\n";
    cout << "7. Load Tasks\n";
    cout << "8. Quit\n";
    cout << "Enter your choice: ";
}

int main() {
    TaskManager TM;
    int choice;
    string Description;
    size_t taskIndex;
    int priority;

    while (true) {
        displayMenu();
        cin >> choice;

        // Input validation for choice
        if (cin.fail() || choice < 1 || choice > 8) {
            cin.clear(); // clear input buffer to restore cin to a usable state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << "Invalid choice, try again..." << endl;
            continue; // skip to next iteration of loop
        }

        switch (choice) {
            case 1:
                cout << "Enter task description: ";
                cin.ignore();
                getline(cin, Description);
                cout << "Enter task priority (0 for low, 1 for medium, 2 for high): ";
                cin >> priority;

                // Input validation for priority
                if (priority < 0 || priority > 2) {
                    cout << "Invalid priority, task not added." << endl;
                    break;
                }

                TM.addTask(Task(Description, priority));
                break;

            case 2:
                cout << "Show completed tasks? (1 for yes, 0 for no): ";
                bool showCompleted;
                cin >> showCompleted;

                // Input validation for showCompleted
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input, showing all tasks." << endl;
                    TM.viewTasks();
                } else {
                    TM.viewTasks(showCompleted);
                }
                break;

            case 3:
                cout << "Enter task number to mark as completed: ";
                cin >> taskIndex;

                // Input validation for task index
                if (taskIndex < 1) {
                    cout << "Invalid task number." << endl;
                } else {
                    TM.completeTask(taskIndex - 1);
                }
                break;

            case 4:
                cout << "Enter task number to be deleted: ";
                cin >> taskIndex;

                // Input validation for task index
                if (taskIndex < 1) {
                    cout << "Invalid task number." << endl;
                } else {
                    TM.deleteTask(taskIndex - 1);
                }
                break;

            case 5:
                cout << "Enter task number to edit: ";
                cin >> taskIndex;

                // Input validation for task index
                if (taskIndex < 1) {
                    cout << "Invalid task number." << endl;
                } else {
                    TM.editTask(taskIndex - 1);
                }
                break;

            case 6:
                TM.saveTasks("tasks.csv");
                break;

            case 7:
                TM.loadTasks("tasks.csv");
                break;

            case 8:
                cout << "Exiting session..." << endl;
                return 0;

            default:
                cout << "Invalid choice, try again..." << endl;
                break;
        }
    }
}
