#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct admins
{
    char username[20];
    char password[20];
} admin, newadmin, entered;

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
        return;
    }
    while (fscanf(fp, % s % s, admin.username, admin.password) != EOF)
    {
        if (strcmp(username, admin.username) == 0 && strcmp(password, admin.password) == 0)
        {
            printf("Admin login successful, welcome %s", admin.username);
            fclose(fp);
            return 1;
        }
        else
            printf("Wrong username or password. Access denied.");
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
    adminvalidation(entered.username, entered.password);
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
        fprintf(fp, "\n%s\n%s", newadmin.username, newadmin.password);

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
    adminvalidation(entered.username, entered.password);
    if (adminvalidation(entered.username, entered.password))
    {
        FILE *fp;
        fp = fopen("Users.txt", "a+");
        if (fp == NULL)
        {
            return;
        }
        printf("Enter new user's job role (doctor/nurse): ");
        scanf("%s", user.job);
        printf("Enter new user's username: ");
        scanf("%s", user.username);
        printf("Enter new user's password: ");
        scanf("%s", user.password);
        fprintf(fp, "\n%s\n%s\n%s", user.job, user.username, user.password);
        printf("New user successfully registered.");
    }
}
void loginportal()
{
    int login = 0;
    FILE *fp;
    fp = fopen("Users.txt", "r+");
    if (fp == NULL)
    {
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
    }if (!login) {
        printf("Invalid username or password. Please try again.\n");
    }
    fclose(fp);
}
int main()
{
    signup();
}