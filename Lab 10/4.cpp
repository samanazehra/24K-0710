#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void rotateLogs(int logNumber) {
    string oldName = "log.txt";
    string newName = "log" + to_string(logNumber) + ".txt";
    rename(oldName.c_str(), newName.c_str());
}

long getFileSize(string filename) {
    ifstream fin(filename, ios::binary | ios::ate); // open at end
    if (!fin) return -1;
    return fin.tellg();
}

int main() {
    int logCount = 1;
    const long maxSize = 1 * 1024 * 1024; // 1MB
    string message;

    while (true) {
        cout << "Enter log message (or type exit to quit): ";
        getline(cin, message);

        if (message == "exit") break;

        ofstream fout("log.txt", ios::app);
        fout << message << endl;
        fout.close();

        if (getFileSize("log.txt") >= maxSize) {
            rotateLogs(logCount);
            logCount++;
        }
    }

    return 0;
}
