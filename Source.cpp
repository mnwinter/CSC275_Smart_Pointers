/*
Matthew Winter
CSC 275 Assignment Smart Pointers
11/3/2024

Overview
    In this assignment, you will learn how to use smart pointers!

Requirements / Expectations
    Over comment all your code for the future you in your own words.
    Make a great UX. (This can be accomplished with lots of cout statements letting the user know what is going on.)
    Your program should do something, in addition, to clearly demonstrating smart pointers.
    You need at least one type of smart pointer. A unique_ptr, or shared_ptr, or weak_ptr.
    Demonstrate when the pointers go out of scope and therefore the values are deleted.

Hint: Use cout to print something to show when the pointers go out of scope and therefore the values are deleted.

*/

#include <iostream>   // Library for input-output operations
#include <memory>     // Library for smart pointers like unique_ptr
#include <string>     // Library for using strings
#include <vector>     // Library for using dynamic arrays (vectors)
#include <limits>     // Library for numeric limits (used to clear input)

using namespace std; // Use the entire std namespace

// Define a class called RobotTask, which represents a task for a robot
class RobotTask {
public:
    // Constructor: This function runs when a RobotTask is created
    explicit RobotTask(const string& desc) : description(desc) {
        // Print a message to show that the task has been created
        cout << "[Task Created] Robot Task: " << description << endl;
    }

    // Destructor: This function runs when a RobotTask is deleted or goes out of scope
    ~RobotTask() {
        // Print a message to show that the task has been deleted
        cout << "[Task Deleted] Robot Task: " << description << endl;
    }

    // Function to simulate doing the task
    void execute() const {
        // Print a message to show that the task is being done
        cout << "[Executing Task] " << description << endl;
    }

private:
    string description; // Holds the description of the task
};

// Function to create a RobotTask and return it as a unique_ptr
unique_ptr<RobotTask> createRobotTask(const string& desc) {
    // Create a new RobotTask and return it as a unique_ptr
    return make_unique<RobotTask>(desc);
}

// Function to wait for user to press Enter, to improve user experience
void waitForUser() {
    cout << "\nPress Enter to continue..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function to display the menu and get user's choice
int displayMenu() {
    cout << "\nRobot Task Manager Menu:\n";
    cout << "1. Initialize sensors\n";
    cout << "2. Move to coordinates (10, 20)\n";
    cout << "3. Capture image at location\n";
    cout << "4. Shutdown system\n";
    cout << "5. Execute all tasks\n";
    cout << "6. Exit\n";
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer
    return choice;
}

// Function to manage and run robot tasks based on user input
void manageRobotTasks() {
    // Define a vector to store unique_ptrs to RobotTask objects
    vector<unique_ptr<RobotTask>> taskQueue;

    // Populate the task queue with predefined tasks
    taskQueue.push_back(createRobotTask("Initialize sensors"));             // Task 1
    taskQueue.push_back(createRobotTask("Move to coordinates (10, 20)"));   // Task 2
    taskQueue.push_back(createRobotTask("Capture image at location"));      // Task 3
    taskQueue.push_back(createRobotTask("Shutdown system"));                // Task 4

    bool running = true; // Control variable for the menu loop

    // Run the menu loop until the user chooses to exit
    while (running) {
        int choice = displayMenu(); // Display menu and get choice

        switch (choice) {
        case 1:
        case 2:
        case 3:
        case 4:
            // Execute the selected task (index choice - 1 matches task index)
            cout << "\n[Executing Selected Task]\n";
            taskQueue[choice - 1]->execute();
            break;

        case 5:
            // Execute all tasks sequentially
            cout << "\n[Executing All Robot Tasks]\n";
            for (const auto& task : taskQueue) {
                task->execute();
                waitForUser(); // Wait for user input after each task
            }
            break;

        case 6:
            // Exit the program
            cout << "\n[Exiting Robot Task Manager]\n";
            running = false;
            break;

        default:
            // Handle invalid choices
            cout << "Invalid choice, please try again.\n";
            break;
        }

        if (choice != 6 && choice != 5) {
            waitForUser(); // Wait for user input after each individual task
        }
    }
}

// Main function that starts the program
int main() {
    // Print a welcome message for the user
    cout << "Welcome to the Robot Task Manager!" << endl;
    cout << "This program will manage a series of tasks for a robot." << endl;

    // Inform the user that the task manager is starting
    cout << "[Robot Task Manager Starting]\n" << endl;

    // Call the manageRobotTasks function to set up and run tasks
    manageRobotTasks();

    // Inform the user that the task manager has ended
    cout << "\n[Robot Task Manager Ended]\n" << endl;

    // Wait for the user to close the program
    cout << "Thank you for using the Robot Task Manager!" << endl;
    waitForUser();

    // Return 0 to show the program finished successfully
    return 0;
}
