#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Employee {
public:
    int id;
    string name;
    string designation;
    int years;

    Employee() {}

    Employee(int id, string name, string designation, int years) {
        this->id = id;
        this->name = name;
        this->designation = designation;
        this->years = years;
    }

    void writeToFile(ofstream &fout) {
        fout << id << "," << name << "," << designation << "," << years << endl;
    }

    void readFromStream(string line) {
        stringstream ss(line);
        string temp;
        getline(ss, temp, ',');
        id = stoi(temp);
        getline(ss, name, ',');
        getline(ss, designation, ',');
        getline(ss, temp, ',');
        years = stoi(temp);
    }

    bool isManagerWithMinYears() {
        return designation == "Manager" && years >= 2;
    }

    void incrementIdAndYears() {
        id += 10;
        years += 1;
    }
};

int main() {
    ofstream fout("employee.txt");
    Employee e1(1, "Aliza", "Manager", 3);
    Employee e2(2, "Fizza", "Developer", 1);
    Employee e3(3, "Samana", "Manager", 2);
    Employee e4(4, "Abdullah", "Tester", 5);
    Employee e5(5, "Zamin", "Manager", 1);
    e1.writeToFile(fout);
    e2.writeToFile(fout);
    e3.writeToFile(fout);
    e4.writeToFile(fout);
    e5.writeToFile(fout);
    fout.close();

    ifstream fin("employee.txt");
    ofstream tempOut("temp.txt");
    string line;
    while (getline(fin, line)) {
        Employee emp;
        emp.readFromStream(line);
        if (emp.isManagerWithMinYears()) {
            emp.writeToFile(tempOut);
        }
    }
    fin.close();
    tempOut.close();

    ofstream fout2("employee.txt");
    ifstream fin2("temp.txt");
    while (getline(fin2, line)) {
        Employee emp;
        emp.readFromStream(line);
        emp.incrementIdAndYears();
        emp.writeToFile(fout2);
    }
    fin2.close();
    fout2.close();

    return 0;
}
