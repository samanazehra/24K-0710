#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
            printf("Admin login successful, welcome %s\n", admin.username);
            fclose(fp);
            return 1;
        }
        else
            printf("Wrong username or password. Access denied.\n");
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
            printf("Username %s already exists. Please try a different username. \n", user.username);
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
            printf("Admin Username %s already exists. Please try a different username. \n", admin.username);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

void adminsignup()
{
    printf("==Welcome to the admin signup portal. Only admins can sign up new admins.==\n");
    printf("Enter admin username: ");
    scanf("%s", entered.username);
    printf("Enter admin password: ");
    scanf("%s", entered.password);
    if (adminvalidation(entered.username, entered.password))
    {
        printf("Enter new admin's username: ");
        scanf("%s", newadmin.username);
        printf("Enter new admin's password: ");
        scanf("%s", newadmin.password);
        FILE *fp;
        fp = fopen("Admin.txt", "a+");
        if (fp == NULL)
        {
            return;
        }
        if (doesadminexist(entered.username))
        {
            fclose(fp);
            return;
        }
        fprintf(fp, "%s %s\n", newadmin.username, newadmin.password);
        printf("New admin registered. Welcome %s!\n", newadmin.username);

        fclose(fp);
    }
}
void signup()
{
    printf("==Welcome to the signup portal. Only admins can sign up new users.==\n");
    printf("Enter admin username: ");
    scanf("%s", entered.username);
    printf("Enter admin password: ");
    scanf("%s", entered.password);
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
        scanf("%s", user.password);
        if (doesuserexist(user.username))
        {
            fclose(fp);
            return;
        }
        fprintf(fp, "%s %s %s\n", user.job, user.username, user.password);
        printf("New user successfully registered! Welcome %s %s!\n", user.job, user.username);
        fclose(fp);
    }
    else
        printf("Wrong admin username or password.");
}
void loginportal()
{
    int login = 0;
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
    scanf("%s", user.password);
    while (fscanf(fp, "%s %s %s", temp.job, temp.username, temp.password) != EOF)
    {
        if (strcmp(temp.job, user.job) == 0 && strcmp(temp.username, user.username) == 0 && strcmp(temp.password, user.password) == 0)
        {
            printf("\nLogin Successful.\n");
            login = 1;
            break;
        }
    }
    if (!login)
    {
        printf("Invalid username or password. Please try again.\n");
    }
    fclose(fp);
}

int main()
{
    int choice;
    printf("===San Jose St. Bonaventure Hospital Portal===\n");
    while (1)
    {
        printf("1. User Login Portal\n2. New User Signup\n3. New Admin Signup\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            loginportal();
            break;
        case 2:
            signup();
            break;
        case 3:
            adminsignup();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("Invalid choice. ");
            break;
        }
    }
    return 0;
}