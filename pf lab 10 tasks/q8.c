#include <stdio.h>
#include <string.h>

struct Car {
    char make[50];
    char model[50];
    int year;
    double price;
    int mileage;
};

void addCar(struct Car cars[], int *count, int maxCars) {
    if (*count >= maxCars) {
        printf("Cannot add more cars. Maximum capacity reached.\n");
        return;
    }

    printf("Enter car make: ");
    scanf(" %[^\n]", cars[*count].make);
    printf("Enter car model: ");
    scanf(" %[^\n]", cars[*count].model);
    printf("Enter manufacturing year: ");
    scanf("%d", &cars[*count].year);
    printf("Enter price: ");
    scanf("%lf", &cars[*count].price);
    printf("Enter mileage: ");
    scanf("%d", &cars[*count].mileage);

    (*count)++;
    printf("Car added successfully.\n");
}

void displayCars(struct Car cars[], int count) {
    if (count == 0) {
        printf("No cars available.\n");
        return;
    }

    printf("\nAvailable Cars:\n");
    printf("%-20s %-20s %-10s %-10s %-10s\n", "Make", "Model", "Year", "Price", "Mileage");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-20s %-10d %-10.2f %-10d\n", cars[i].make, cars[i].model, cars[i].year, cars[i].price, cars[i].mileage);
    }
}

void searchCar(struct Car cars[], int count) {
    if (count == 0) {
        printf("No cars available to search.\n");
        return;
    }

    char searchTerm[50];
    printf("Enter make or model to search: ");
    scanf(" %[^\n]", searchTerm);

    int found = 0;
    printf("\nSearch Results:\n");
    printf("%-20s %-20s %-10s %-10s %-10s\n", "Make", "Model", "Year", "Price", "Mileage");
    for (int i = 0; i < count; i++) {
        if (strstr(cars[i].make, searchTerm) || strstr(cars[i].model, searchTerm)) {
            printf("%-20s %-20s %-10d %-10.2f %-10d\n", cars[i].make, cars[i].model, cars[i].year, cars[i].price, cars[i].mileage);
            found = 1;
        }
    }

    if (!found) {
        printf("No cars found matching the search term.\n");
    }
}

int main() {
    int maxCars = 100;
    struct Car cars[maxCars];
    int carCount = 0;

    while (1) {
        printf("\nCar Dealership Management System\n");
        printf("1. Add New Car\n");
        printf("2. Display All Cars\n");
        printf("3. Search for Cars\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            addCar(cars, &carCount, maxCars);
        } else if (choice == 2) {
            displayCars(cars, carCount);
        } else if (choice == 3) {
            searchCar(cars, carCount);
        } else if (choice == 4) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
