#include <stdio.h>

void convertMetersToKilometers(double meters) {
    static int callCount = 0;
    callCount++;
    double kilometers = meters / 1000.0;
    printf("Converted Distance: %.2f kilometers\n", kilometers);
    printf("Function called %d time(s).\n", callCount);
}

int main() {
    while (1) {
        printf("\n1. Convert Meters to Kilometers\n2. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        if (choice == 1) {
            double meters;
            printf("Enter distance in meters: ");
            scanf("%lf", &meters);
            convertMetersToKilometers(meters);
        } else if (choice == 2) {
            printf("Exiting the program.\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
