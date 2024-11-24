#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

FILE *fp;

struct admins
{
    char username[20];
    char password[20];
} admin, newadmin, entered, tem;

struct staff
{
    char job[20];
    char username[20];
    char password[20];
} user, temp;

struct Doctor
{
    int doctorID;
    char name[100];
    int age;
    char address[100];
    char specialization[50];
    char contactNumber[20];
    int patientsAttending;
} doctor;

struct Patient
{
    int patient_ID;
    char name[100];
    int age;
    char gender[10];
    char disease[200];
    int duration;
    int bp;
    int pulse;
    char medicineTimings[200];
    int medicineQuantity;
    char doctor[100];
    char surgery[100];
} patient;

struct pharmacyitem
{
    char name[100];
    int id;
    int quantity;
    float price;
    char type[50];
    char manufacturer[100];
} item;

void adminpanel(int choice)
{

    printf("\n1. Doctor Records Management\n");
    printf("2. Patient Records Management\n");
    printf("3. Pharmacy Medicine Stock Management\n");
    printf("4. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        doctormenu(choice);
        break;
    case 2:
        patientmenu(choice);
        break;
    case 3:
        pharmacymenu(choice);
        break;
    case 4:
        break;
    default:
        printf("Invalid choice.\n");
    }
}

void doctormenu(int doctorchoice)
{
    do
    {
        printf("\n== Doctor Management Options ==\n");
        printf("1. Add Doctor Record\n");
        printf("2. Update Doctor Info\n");
        printf("3. View Doctors Records\n");
        printf("4. Delete Doctor Record\n");
        printf("5. Go back to Admin Control Panel\n");
        printf("6. Log out and return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &doctorchoice);
        switch (doctorchoice)
        {
        case 1:
            addDoctor();
            break;
        case 2:
            updateDoctor();
            break;
        case 3:
            viewDoctors();
            break;
        case 4:
            deleteDoctor();
            break;
        case 5:
            adminpanel(doctorchoice);
            break;
        case 6:
            printf("Logging out\n");
            break;
        default:
            printf("Invalid option.\n");
            break;
        }
    } while (doctorchoice != 5 && doctorchoice != 6);
}

void patientmenu(int patientchoice)
{
    do
    {
        printf("\n== Patient Management Options ==\n");
        printf("1. Add Patient\n");
        printf("2. Update Patient\n");
        printf("3. View Patients\n");
        printf("4. Delete Patient\n");
        printf("5. Assign Doctor to Patient\n");
        printf("6. Log out and return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &patientchoice);

        switch (patientchoice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            updatePatient();
            break;
        case 3:
            viewPatients();
            break;
        case 4:
            deletePatient();
            break;
        case 5:
            assignDoctorToPatient();
            break;
        case 6:
            printf("Logging out.\n");
            return;
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (patientchoice != 6);
}

void addstock()
{
    fp = fopen("Pharmacy.txt", "a");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    printf("Enter item ID: ");
    scanf("%d", &item.id);

    printf("Enter item name: ");
    getchar();
    fgets(item.name, 100, stdin);
    item.name[strcspn(item.name, "\n")] = '\0';

    printf("Enter item type: ");
    fgets(item.type, 50, stdin);
    item.type[strcspn(item.type, "\n")] = '\0';

    printf("Enter item quantity: ");
    scanf("%d", &item.quantity);

    printf("Enter item price: ");
    scanf("%f", &item.price);

    printf("Enter manufacturer name: ");
    getchar();
    fgets(item.manufacturer, 100, stdin);
    item.manufacturer[strcspn(item.manufacturer, "\n")] = '\0';

    fprintf(fp, "%d %s %s %d %.2f %s\n", item.id, item.name, item.type, item.quantity, item.price, item.manufacturer);

    fclose(fp);

    printf("Item Added Successfully.\n");
}

void viewstock() {
    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("ID | Name           | Type           | Quantity | Price   | Manufacturer\n");
    printf("--------------------------------------------------------------------------\n");
    while (fscanf(fp, "%d %s %s %d %f %s", 
                  &item.id, item.name, item.type, 
                  &item.quantity, &item.price, item.manufacturer) != EOF) {
        printf("%d | %-15s | %-15s | %8d | %7.2f | %-15s\n", 
               item.id, item.name, item.type, 
               item.quantity, item.price, item.manufacturer);
    }
    fclose(fp);
}

void dispensestock() {
    viewstock();
    int itemID, quantity;
    float totalPrice;
    int found = 0;

    printf("Enter the item ID to dispense: ");
    scanf("%d", &itemID);

    printf("Enter the quantity to dispense: ");
    scanf("%d", &quantity);

    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    struct pharmacyitem items[100];
    int count = 0;

    while (fscanf(fp, "%d %s %s %d %f %s", 
                  &items[count].id, items[count].name, items[count].type, 
                  &items[count].quantity, &items[count].price, items[count].manufacturer) == 6) {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++) {
        if (items[i].id == itemID) {
            found = 1;
            if (items[i].quantity < quantity) {
                printf("Not enough stock available!\n");
                return;
            }

            items[i].quantity -= quantity;
            totalPrice = items[i].price * quantity;
            printf("Item: %s, Quantity: %d, Total Price: %.2f\n", items[i].name, quantity, totalPrice);
            break;
        }
    }

    if (!found) {
        printf("Item not found!\n");
        return;
    }

    fp = fopen("Pharmacy.txt", "w");
    if (fp == NULL) {
        printf("Error opening Pharmacy.txt for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %d %.2f %s\n", 
                items[i].id, items[i].name, items[i].type, 
                items[i].quantity, items[i].price, items[i].manufacturer);
    }

    fclose(fp);
}

void autoreorderstock() {
    int reorderunits = 50;
    struct pharmacyitem items[100];
    int count = 0;

    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL) {
        printf("Error opening Pharmacy.txt\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %d %f %s", 
                  &items[count].id, items[count].name, items[count].type, 
                  &items[count].quantity, &items[count].price, items[count].manufacturer) == 6) {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++) {
        if (items[i].quantity < reorderunits) {
            items[i].quantity += 50;
        }
    }

    fp = fopen("Pharmacy.txt", "w");
    if (fp == NULL) {
        printf("Error opening Pharmacy.txt for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %d %.2f %s\n", 
                items[i].id, items[i].name, items[i].type, 
                items[i].quantity, items[i].price, items[i].manufacturer);
    }

    fclose(fp);
}

void generatebill()
{
    int itemID, quantity;
    float totalPrice;

    printf("Enter the item ID to generate bill: ");
    scanf("%d", &itemID);

    printf("Enter the quantity: ");
    scanf("%d", &quantity);

    fp= fopen("Pharmacy.txt","r");
    if (fp==NULL)
    {
        printf("Error opening file");
        return;
    }

    int found = 0;
    while (fscanf(fp, "%d %s %s %d %f %s", &item.id, item.name, item.type, &item.quantity, &item.price, item.manufacturer) != EOF)
    {
        if (item.id == itemID)
        {
            found = 1;
            if (item.quantity < quantity)
            {
                printf("Not enough stock to generate the bill!\n");
                return;
            }

            totalPrice = item.price * quantity;
            printf("== Bill ==\n");
            printf("Item: %s\n", item.name);
            printf("Quantity: %d\n", quantity);
            printf("Price per unit: %.2f\n", item.price);
            printf("Total Price: %.2f\n", totalPrice);
        }
    }

    if (!found)
    {
        printf("Item not found!\n");
    }
    fclose(fp);
}

void pharmacymenu(int choice)
{
    while (1)
    {
        printf("\n== Pharmacy Management ==\n");
        printf("1. Add Stock\n");
        printf("2. View Stock\n");
        printf("3. Dispense Stock\n");
        printf("4. Generate Bill\n");
        printf("5. Back to Admin Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addstock();
            break;
        case 2:
            viewstock();
            break;
        case 3:
            dispensestock();
            autoreorderstock();
            break;
        case 4:
            generateBill();
            autoreorderstock();
            break;
        case 5:
            return;
            break;
        default:
            printf("Invalid choice.\n");
        }
    }
}

int adminvalidation(char *username, char *password)
{
    FILE *fp;
    fp = fopen("Admin.txt", "r+");
    if (fp == NULL)
    {
        return -1;
    }
    while (fscanf(fp, "%s %s", admin.username, admin.password) != EOF)
    {
        if (strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0)
        {
            printf("Admin login successful, welcome %s\n\n!", admin.username);
            fclose(fp);
            return 1;
        }
        else
            printf("Wrong username or password. Access denied.\n\n");
    }
    fclose(fp);
    return 0;
}

int doesuserexist(char *username)
{
    FILE *fp;
    fp = fopen("Users.txt", "r+");
    if (fp == NULL)
    {
        return 0;
    }
    while (fscanf(fp, "%*s %s %*s", temp.username) != EOF)
    {
        if (strcmp(username, temp.username) == 0)
        {
            printf("Username %s already exists. Please try a different username. \n\n", user.username);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

int doesadminexist(char *username)
{
    FILE *fp;
    fp = fopen("Admin.txt", "r+");
    if (fp == NULL)
    {
        return 0;
    }
    while (fscanf(fp, "%s %*s", tem.username) != EOF)
    {
        if (strcmp(username, tem.username) == 0)
        {
            printf("Admin Username %s already exists. Please try a different username. \n\n", admin.username);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void hidepassword(char *password)
{
    int i = 0;
    char c;
    while ((c = getch()) != '\r')
    {
        if (c == '\b' && i > 0)
        {
            printf("\b \b");
            i--;
        }
        else if (c != '\b')
        {
            password[i++] = c;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
}

void adminsignup()
{
    printf("==Welcome to the admin signup portal. Only admins can sign up new admins.==\n");
    printf("Enter admin username: ");
    scanf("%s", entered.username);
    printf("Enter admin password: ");
    hidepassword(entered.password);
    if (adminvalidation(entered.username, entered.password))
    {
        printf("Enter new admin's username: ");
        scanf("%s", newadmin.username);
        printf("Enter new admin's password: ");
        hidepassword(newadmin.password);
        FILE *fp;
        fp = fopen("Admin.txt", "a+");
        if (fp == NULL)
        {
            return;
        }
        if (doesadminexist(newadmin.username))
        {
            fclose(fp);
            return;
        }
        fprintf(fp, "%s %s\n", newadmin.username, newadmin.password);
        printf("New admin successfully registered. Welcome %s!\n\n", newadmin.username);

        fclose(fp);
    }
}
void signup()
{
    printf("==Welcome to the signup portal. Only admins can sign up new users.==\n");
    printf("Enter admin username: ");
    scanf("%s", entered.username);
    printf("Enter admin password: ");
    hidepassword(entered.password);
    if (adminvalidation(entered.username, entered.password))
    {
        FILE *fp;
        fp = fopen("Users.txt", "a+");
        if (fp == NULL)
        {
            printf("Error: Unable to open Users.txt.\n");
            return;
        }
        printf("Enter new user's job role (doctor/nurse): ");
        scanf("%s", user.job);
        printf("Enter new user's username: ");
        scanf("%s", user.username);
        printf("Enter new user's password: ");
        hidepassword(user.password);
        if (doesuserexist(user.username))
        {
            fclose(fp);
            return;
        }
        fprintf(fp, "%s %s %s\n", user.job, user.username, user.password);
        printf("New user successfully registered! Welcome %s %s!\n\n", user.job, user.username);
        fclose(fp);
    }
    else
        printf("Wrong admin username or password.\n\n");
}
int loginportal()
{
    int login = 0;
    int choice;
    FILE *fp;
    fp = fopen("Users.txt", "r+");
    if (fp == NULL)
    {
        printf("Error: Unable to open Users.txt.\n");
        return;
    }
    printf("Enter job role (doctor/nurse): ");
    scanf("%s", user.job);
    printf("Enter username: ");
    scanf("%s", user.username);
    printf("Enter password: ");
    hidepassword(user.password);
    while (fscanf(fp, "%s %s %s", temp.job, temp.username, temp.password) != EOF)
    {
        if (strcmp(temp.job, user.job) == 0 && strcmp(temp.username, user.username) == 0 && strcmp(temp.password, user.password) == 0)
        {
            printf("\nLogin Successful. Welcome %s %s!\n\n", user.job, user.username);
            login = 1;
            return 1;
            break;
        }
    }
    if (!login)
    {
        printf("Invalid username or password. Please try again.\n");
        return 0;
    }
    fclose(fp);
}

int adminlogin()
{
    int login = 0;
    int choice;
    FILE *fp;
    fp = fopen("Admin.txt", "r+");
    if (fp == NULL)
    {
        printf("Error: Unable to open Admin.txt.\n");
        return;
    }
    printf("Enter username: ");
    scanf("%s", entered.username);
    printf("Enter password: ");
    hidepassword(entered.password);
    while (fscanf(fp, "%s %s", tem.username, tem.password) != EOF)
    {
        if (strcmp(tem.username, entered.username) == 0 && strcmp(tem.password, entered.password) == 0)
        {
            printf("\nLogin Successful. Welcome %s!\n\n", entered.username);
            login = 1;
            return 1;
            break;
        }
    }
    if (!login)
    {
        printf("Invalid username or password. Please try again.\n");
        return 0;
    }

    fclose(fp);
}

int main()
{
    int choice, adminchoice, patientchoice;
    FILE *doctorFile = fopen("doctors.txt", "r+");
    FILE *patientFile = fopen("patients.txt", "r+");

    if (!doctorFile)
    {
        doctorFile = fopen("doctors.txt", "w+");
        if (!doctorFile)
        {
            printf("Error creating doctors file!\n");
            return 1;
        }
    }

    if (!patientFile)
    {
        patientFile = fopen("patients.txt", "w+");
        if (!patientFile)
        {
            printf("Error creating patients file!\n");
            return 1;
        }
    }

    while (1)
    {
        printf("=== San Jose St. Bonaventure's Hospital Management System ===\n");
        printf("1. Admin Login Portal\n");
        printf("2. User Login Portal\n");
        printf("3. Admin Signup\n");
        printf("4. User Signup\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if(adminlogin())
            adminpanel(choice);
            else printf("Invalid username or password. Access denied.\n");
            break;

        case 2:
            if(loginportal())
            {
            patientmenu(patientchoice);
            printf("Enter your choice: ");
            scanf("%d", &patientchoice);
            }
            else printf("Invalid username or password. Access denied.\n");
            break;

        case 3:
            adminsignup();
            break;

        case 4:
            signup();
            break;

        case 5:
            printf("Exiting the program. Goodbye!\n");
            fclose(doctorFile);
            fclose(patientFile);
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    rewind(doctorFile);
    rewind(patientFile);
    fclose(doctorFile);
    fclose(patientFile);
}