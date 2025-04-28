#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void addTask() {
    string task;
    cout << "Enter task: ";
    getline(cin, task);

    ofstream fout("tasks.txt", ios::app);
    fout << task << ",Not Done" << endl;
    fout.close();
}

void viewTasks() {
    ifstream fin("tasks.txt");
    string line;
    int taskNumber = 1;
    cout << "Tasks List:" << endl;
    while (getline(fin, line)) {
        cout << taskNumber << ". " << line << endl;
        taskNumber++;
    }
    fin.close();
}

void markTaskDone() {
    ifstream fin("tasks.txt");
    ofstream fout("temp.txt");

    string line;
    int number, current = 1;
    cout << "Enter task number to mark as done: ";
    cin >> number;
    cin.ignore();

    while (getline(fin, line)) {
        if (current == number) {
            size_t pos = line.find(",Not Done");
            if (pos != string::npos) {
                line.replace(pos, 9, ",Done");
            }
        }
        fout << line << endl;
        current++;
    }
    fin.close();
    fout.close();

    remove("tasks.txt");
    rename("temp.txt", "tasks.txt");
}

int main() {
    int choice;
    while (true) {
        cout << "1. Add Task" << endl;
        cout << "2. View Tasks" << endl;
        cout << "3. Mark Task as Done" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
            addTask();
        else if (choice == 2)
            viewTasks();
        else if (choice == 3)
            markTaskDone();
        else if (choice == 4)
            break;
        else
            cout << "Invalid choice. Try again." << endl;
    }

    return 0;
}
