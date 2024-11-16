#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>

using namespace std;

class ChecklistApp {
public:
    std::vector<std::string> checklist;
    std::vector<bool> isCompleted;
    std::vector<int> completionCounts;
    std::vector<int> currentCompletions;
    const std::string fileName = "tasks.csv";

    //This function loads tasks from a file. If there are no tasks in the file, it skips the setup
    void loadTasksFromFile() {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            return;
        }

        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            std::string item;
            bool completed;
            int completionCount, currentCompletion;

            getline(ss, item, ',');
            ss >> completed;
            ss.ignore(1);
            ss >> completionCount;
            ss.ignore(1);
            ss >> currentCompletion;

            checklist.push_back(item);
            isCompleted.push_back(completed);
            completionCounts.push_back(completionCount);
            currentCompletions.push_back(currentCompletion);
        }
        file.close();
    }

    //This function saves the tasks to a csv file
    void saveTasksToFile() const {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            return;
        }

        for (size_t i = 0; i < checklist.size(); ++i) {
            file << checklist[i] << ","
                 << isCompleted[i] << ","
                 << completionCounts[i] << ","
                 << currentCompletions[i] << "\n";
        }
        file.close();
    }




    //This function allows the user to add a task to the list.
    //It asks if it is a repeated task, then saves the info to a file
    void addItem() {
        system("CLS");
        std::string item;
        int repeatCount = 1;

        std::cout << "Enter an item to add to the checklist: ";
        std::getline(std::cin, item);

        std::cout << "Is this a repeated task? (Enter the number of times it needs to be completed, or 1 if it's a single task): ";
        std::cin >> repeatCount;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        checklist.push_back(item);
        isCompleted.push_back(false);
        completionCounts.push_back(repeatCount);
        currentCompletions.push_back(0);
        std::cout << "Item added successfully.\n";
        saveTasksToFile();
    }

    //This function allows the user to view saved tasks, both complete and uncomplete.
    void viewItems() const {
        system("CLS");
        if (checklist.empty()) {
            std::cout << "The checklist is empty.\n";
            return;
        }

        std::cout << "\n--- Uncompleted Tasks ---\n";
        bool hasUncompleted = false;
        for (size_t i = 0; i < checklist.size(); ++i) {
            if (!isCompleted[i]) {
                std::cout << i + 1 << ". " << checklist[i] 
                          << " (Completed " << currentCompletions[i] << "/" << completionCounts[i] << " times)\n";
                hasUncompleted = true;
            }
        }
        if (!hasUncompleted) {
            std::cout << "No uncompleted tasks.\n";
        }

        std::cout << "\n--- Completed Tasks ---\n";
        bool hasCompleted = false;
        for (size_t i = 0; i < checklist.size(); ++i) {
            if (isCompleted[i]) {
                std::cout << i + 1 << ". " << checklist[i] << '\n';
                hasCompleted = true;
            }
        }
        if (!hasCompleted) {
            std::cout << "No completed tasks.\n";
        }
    }

    //This function allows the user to mark tasks as complete; updating the file in the process.
    //If all tasks are completed, it informs the user. 
    //If a task has multiple completions, it gives the number of completions.
    void markItemComplete() {
        system("CLS");
        std::cout << "\n--- Uncompleted Tasks ---\n";
        bool hasUncompleted = false;
        std::vector<int> uncompletedIndices;

        for (size_t i = 0; i < checklist.size(); ++i) {
            if (!isCompleted[i]) {
                std::cout << uncompletedIndices.size() + 1 << ". " << checklist[i] 
                << " (Completed " << currentCompletions[i] << "/" << completionCounts[i] << " times)\n";
                uncompletedIndices.push_back(i);
                hasUncompleted = true;
            }
        }

        if (!hasUncompleted) {
            std::cout << "All tasks are completed!\n";
            return;
        }

        int taskNumber;
        std::cout << "Enter the number of the task to mark as complete: ";
        std::cin >> taskNumber;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (taskNumber < 1 || taskNumber > static_cast<int>(uncompletedIndices.size())) {
            std::cout << "Invalid task number.\n";
        } 
        else {
            int originalIndex = uncompletedIndices[taskNumber - 1];
            currentCompletions[originalIndex]++;

            if (currentCompletions[originalIndex] >= completionCounts[originalIndex]) {
                isCompleted[originalIndex] = true;
                std::cout << "Task marked as fully complete.\n";
            } 
            else {
                std::cout << "Task marked as completed " << currentCompletions[originalIndex]
                          << "/" << completionCounts[originalIndex] << " times.\n";
            }
            saveTasksToFile();
        }
    }

    //This runs the menu loop
    void run() {
        int choice;
         while (choice != 4) {
            std::cout << "\n--- Checklist App ---\n";
            std::cout << "1. Add item\n";
            std::cout << "2. View items\n";
            std::cout << "3. Mark item as complete\n";
            std::cout << "4. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    system("CLS");
                    addItem();
                    break;
                case 2:
                    system("CLS");
                    viewItems();
                    break;
                case 3:
                    system("CLS");
                    markItemComplete();
                    break;
                case 4:
                    break;
                default:
                    system("CLS");
                    std::cout << "Invalid choice. Please try again.\n";
                    break;
            }
        };
    }
};

int main() {
    ChecklistApp app;
    app.run();
    return 0;
}
