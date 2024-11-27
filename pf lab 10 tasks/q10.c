#include <stdio.h>
#include <string.h>

struct TravelPackage {
    char name[50];
    char destination[50];
    int duration;
    double cost;
    int availableSeats;
};

void displayPackages(struct TravelPackage packages[], int count) {
    if (count == 0) {
        printf("No packages available.\n");
        return;
    }

    printf("\nAvailable Travel Packages:\n");
    printf("%-20s %-20s %-10s %-10s %-10s\n", "Package Name", "Destination", "Duration", "Cost", "Seats");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-20s %-10d %-10.2f %-10d\n", packages[i].name, packages[i].destination, packages[i].duration, packages[i].cost, packages[i].availableSeats);
    }
}

void bookPackage(struct TravelPackage packages[], int count) {
    if (count == 0) {
        printf("No packages available for booking.\n");
        return;
    }

    char packageName[50];
    printf("Enter the name of the package to book: ");
    scanf(" %[^\n]", packageName);

    for (int i = 0; i < count; i++) {
        if (strcmp(packages[i].name, packageName) == 0) {
            if (packages[i].availableSeats > 0) {
                packages[i].availableSeats--;
                printf("Booking successful for package: %s\n", packages[i].name);
                return;
            } else {
                printf("Sorry, no seats available for this package.\n");
                return;
            }
        }
    }
    printf("Package not found.\n");
}

int main() {
    struct TravelPackage packages[100];
    int packageCount = 0;

    while (1) {
        printf("\nTravel Package Management System\n");
        printf("1. Add New Package\n");
        printf("2. Display Available Packages\n");
        printf("3. Book a Package\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter package name: ");
            scanf(" %[^\n]", packages[packageCount].name);
            printf("Enter destination: ");
            scanf(" %[^\n]", packages[packageCount].destination);
            printf("Enter duration (in days): ");
            scanf("%d", &packages[packageCount].duration);
            printf("Enter cost: ");
            scanf("%lf", &packages[packageCount].cost);
            printf("Enter number of seats available: ");
            scanf("%d", &packages[packageCount].availableSeats);
            packageCount++;
            printf("Package added successfully.\n");
        } else if (choice == 2) {
            displayPackages(packages, packageCount);
        } else if (choice == 3) {
            bookPackage(packages, packageCount);
        } else if (choice == 4) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
