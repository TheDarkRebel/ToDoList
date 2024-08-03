#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

// Function to write the tasks to a file
void addToFile(const vector<string>& tasks, string filename) {
    // Opening stream for writing in binary mode
    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        // Writing tasks to the file
        for (int i = 0; i < tasks.size(); i++){
            file << i + 1 << ". " << tasks[i] << endl;
        }
        cout << "List successfully added to file: " << filename << endl;
        file.close();           
    } else {
        // If file could not be opened
        cerr << "Failed to open file." << endl;
    }
}

// Function to read the tasks from a file
void readFromFile(string filename) {
    string line;
    // Opening stream for reading in binary mode
    ifstream file(filename, ios::binary);
    if (file.is_open()) {
        // Reading lines from the file and displaying them
        while (getline(file, line)){
            cout << line << std::endl;
        }
        file.close();
    } else {
        // If file could not be opened
        cerr << "Failed to open file." << endl;
    }
}

// Function to display the tasks in the console
void displayTasks(const vector<string>& tasks) {
    if (tasks.size() == 0){
        // If no tasks are present
        cout << "\nTo-Do List is empty.\n";
    } else {
        // Displaying the tasks
        cout << "\nTo-Do List:" << endl;
        for (size_t i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i] << endl;
        }
    }
}

int main() {
    vector<string> tasks; // Vector to store the tasks
    int choice; // Variable to store user choice
    string task, line;
    string filename = "data.txt"; // Filename for storing tasks

    // Load existing tasks from file
    ifstream file(filename, ios::binary);
    file.ignore(3); // Ignore the first 3 characters (assuming a specific file format)
    while(getline(file, line)){
        file.ignore(3); // Ignore the next 3 characters
        tasks.push_back(line);
    }

    do {
        // Displaying the menu
        cout << "\nSelection table:\n";
        cout << "____________________\n";
        cout << "|1. Add task       |\n";
        cout << "|__________________|\n";
        cout << "|2. Delete task    |\n";
        cout << "|__________________|\n";
        cout << "|3. View tasks     |\n";
        cout << "|__________________|\n";
        cout << "|4. Save to file   |\n";
        cout << "|__________________|\n";
        cout << "|5. Read from file |\n";
        cout << "|__________________|\n";
        cout << "|6. Clear list     |\n";
        cout << "|__________________|\n";
        cout << "|0. Exit           |\n";
        cout << "|__________________|\n";
        cout << "\nEnter your choice: ";

        // Getting user choice
        if (!(std::cin >> choice)) {
            // Handling invalid input
            std::cerr << "Invalid task number!" << std::endl;
            std::cin.clear(); // Clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore rest of the input
            continue;
        }

        switch (choice) {
            case 1:
                // Adding a new task
                cout << "Enter the task: ";
                cin.ignore(); // Clear the newline left by previous input
                getline(cin, task); // Get the full line of task description
                tasks.push_back(task);
                break;

            case 2:
                // Deleting a task
                int taskIndex;
                displayTasks(tasks); // Display current tasks
                cout << "Enter the task number to delete: ";
                cin >> taskIndex; // Get the task number to delete
                if (taskIndex > 0 && taskIndex <= tasks.size()) {
                    // Valid task number, erase the task
                    tasks.erase(tasks.begin() + taskIndex - 1);
                } else {
                    // Invalid task number
                    cout << "Invalid task number!" << endl;
                }
                break;

            case 3:
                // Viewing tasks
                displayTasks(tasks);
                break;

            case 4:
                // Saving tasks to file
                addToFile(tasks, filename);
                break;

            case 5:
                // Reading tasks from file
                readFromFile(filename);
                break;

            case 6:
                // Clearing all tasks
                tasks.clear();
                break;

            case 0:
                // Exiting the program
                cout << "Exiting..." << endl;
                break;

            default:
                // Handling invalid menu choice
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 0); // Loop until user chooses to exit

    return 0;
}