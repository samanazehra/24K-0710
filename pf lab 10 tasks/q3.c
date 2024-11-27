#include <stdio.h>
#include <string.h>

struct Flight {
    int flightNumber;
    char departureCity[50];
    char destinationCity[50];
    char date[20];
    int availableSeats;
};

void displayFlightDetails(struct Flight flight) {
    printf("Flight Number: %d\n", flight.flightNumber);
    printf("Departure City: %s\n", flight.departureCity);
    printf("Destination City: %s\n", flight.destinationCity);
    printf("Date: %s\n", flight.date);
    printf("Available Seats: %d\n\n", flight.availableSeats);
}

void bookSeat(struct Flight *flight) {
    if (flight->availableSeats > 0) {
        flight->availableSeats--;
        printf("Seat booked successfully! Remaining seats: %d\n", flight->availableSeats);
    } else {
        printf("Sorry, no seats available on this flight.\n");
    }
}

int main() {
    struct Flight flights[] = {
        {101, "New York", "London", "2024-12-01", 10},
        {102, "Tokyo", "Sydney", "2024-12-02", 5},
        {103, "Paris", "Dubai", "2024-12-03", 0},
        {104, "Berlin", "Rome", "2024-12-04", 3},
        {105, "Delhi", "Singapore", "2024-12-05", 8}
    };

    int choice, flightIndex;
    int totalFlights = sizeof(flights) / sizeof(flights[0]);

    while (1) {
        printf("1. Display Flight Details\n");
        printf("2. Book a Seat\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 3) break;

        printf("Enter flight index (0 to %d): ", totalFlights - 1);
        scanf("%d", &flightIndex);

        if (flightIndex < 0 || flightIndex >= totalFlights) {
            printf("Invalid flight index!\n");
            continue;
        }

        if (choice == 1) {
            displayFlightDetails(flights[flightIndex]);
        } else if (choice == 2) {
            bookSeat(&flights[flightIndex]);
        } else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
