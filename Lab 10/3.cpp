#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class User {
public:
    string user_id;
    string first_name;
    string last_name;
    string address;
    string email;

    void writeToFile(ofstream &fout) {
        fout << user_id << "," << first_name << "," << last_name << "," << address << "," << email << endl;
    }
};

class Product {
public:
    string product_id;
    string product_name;
    string description;
    int price;

    void writeToFile(ofstream &fout) {
        fout << product_id << "," << product_name << "," << description << "," << price << endl;
    }
};

class Order {
public:
    string order_id;
    string user_id;
    string product_id;
    int total_paid;

    void writeToFile(ofstream &fout) {
        fout << order_id << "," << user_id << "," << product_id << "," << total_paid << endl;
    }
};

int main() {
    ofstream userFile("users.txt");
    User u1 = {"U1", "Linus", "Torvalds", "Finland", "linus@email.com"};
    User u2 = {"U2", "Samana", "Zehra", "UK", "ssamanazr@email.com"};
    u1.writeToFile(userFile);
    u2.writeToFile(userFile);
    userFile.close();

    ofstream productFile("products.txt");
    Product p1 = {"P1", "Laptop", "Gaming Laptop", 1500};
    Product p2 = {"P2", "Phone", "Smartphone", 800};
    Product p3 = {"P3", "Tablet", "Android Tablet", 300};
    p1.writeToFile(productFile);
    p2.writeToFile(productFile);
    p3.writeToFile(productFile);
    productFile.close();

    ofstream orderFile("orders.txt");
    Order o1 = {"O1", "U1", "P1", 1500};
    Order o2 = {"O2", "U1", "P2", 800};
    Order o3 = {"O3", "U2", "P3", 300};
    o1.writeToFile(orderFile);
    o2.writeToFile(orderFile);
    o3.writeToFile(orderFile);
    orderFile.close();

    string targetUserId = "";
    ifstream userRead("users.txt");
    string line;
    while (getline(userRead, line)) {
        stringstream ss(line);
        string id, fname, lname, addr, email;
        getline(ss, id, ',');
        getline(ss, fname, ',');
        getline(ss, lname, ',');
        getline(ss, addr, ',');
        getline(ss, email, ',');
        if (fname == "Linus") {
            targetUserId = id;
            break;
        }
    }
    userRead.close();

    if (targetUserId == "") {
        cout << "User Linus not found." << endl;
        return 0;
    }

    string linusProducts[10];
    int count = 0;

    ifstream orderRead("orders.txt");
    while (getline(orderRead, line)) {
        stringstream ss(line);
        string orderid, userid, productid, totalpaid;
        getline(ss, orderid, ',');
        getline(ss, userid, ',');
        getline(ss, productid, ',');
        getline(ss, totalpaid, ',');
        if (userid == targetUserId) {
            linusProducts[count++] = productid;
        }
    }
    orderRead.close();

    cout << "Products associated with Linus:" << endl;
    for (int i = 0; i < count; i++) {
        ifstream productRead("products.txt");
        while (getline(productRead, line)) {
            stringstream ss(line);
            string pid, pname, desc, price;
            getline(ss, pid, ',');
            getline(ss, pname, ',');
            getline(ss, desc, ',');
            getline(ss, price, ',');
            if (pid == linusProducts[i]) {
                cout << pname << endl;
            }
        }
        productRead.close();
    }

    return 0;
}
