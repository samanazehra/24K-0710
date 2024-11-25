#include <stdio.h>
#include <string.h>

struct Doctor {
    int doctorID;
    char name[100];
    int age;
    char address[200];
    char specialization[100];
    char contactNumber[20];
    int patientsAttending;  // Number of patients the doctor is attending to
};

FILE *fp;
struct Doctor doctor;

void addDoctor() {
    fp = fopen("doctors.txt", "a");
    if (fp == NULL) {
        printf("File cannot be opened.\n");
        return;
    }

    printf("Enter Doctor ID: ");
    scanf("%d", &doctor.doctorID);
    getchar();

    printf("Enter Name: ");
    fgets(doctor.name, sizeof(doctor.name), stdin);
    doctor.name[strcspn(doctor.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &doctor.age);
    getchar();

    printf("Enter Address: ");
    fgets(doctor.address, sizeof(doctor.address), stdin);
    doctor.address[strcspn(doctor.address, "\n")] = 0;

    printf("Enter Specialization: ");
    fgets(doctor.specialization, sizeof(doctor.specialization), stdin);
    doctor.specialization[strcspn(doctor.specialization, "\n")] = 0;

    printf("Enter Contact Number: ");
    fgets(doctor.contactNumber, sizeof(doctor.contactNumber), stdin);
    doctor.contactNumber[strcspn(doctor.contactNumber, "\n")] = 0;

    printf("Enter Number of Patients Attending: ");
    scanf("%d", &doctor.patientsAttending);

    fprintf(fp, "Doctor ID: %d\nName: %s\nAge: %d\nAddress: %s\nSpecialization: %s\nContact Number: %s\nPatients Attending: %d\n\n", 
            doctor.doctorID, doctor.name, doctor.age, doctor.address, 
            doctor.specialization, doctor.contactNumber, doctor.patientsAttending);

    fclose(fp);
}

void readDoctors() {
    fp = fopen("doctors.txt", "r");
    if (fp == NULL) {
        printf("File cannot be opened.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);  // Print the content of each line in the file
    }

    fclose(fp);
}

void updateDoctor() {
    FILE *fp;
    struct Doctor doctorArray[100];
    int doctorCount = 0;
    int searchID;
    int found = 0;
    int choice;

    fp = fopen("doctors.txt", "r+");
    if (fp == NULL) {
        printf("File cannot be opened.\n");
        return;
    }

    while (fscanf(fp, "Doctor ID: %d\nName: %[^\n]\nAge: %d\nAddress: %[^\n]\nSpecialization: %[^\n]\nContact Number: %[^\n]\nPatients Attending: %d\n\n", 
            &doctorArray[doctorCount].doctorID, doctorArray[doctorCount].name, 
            &doctorArray[doctorCount].age, doctorArray[doctorCount].address, 
            doctorArray[doctorCount].specialization, doctorArray[doctorCount].contactNumber, 
            &doctorArray[doctorCount].patientsAttending) != EOF) {
        doctorCount++;
    }

    printf("Enter Doctor ID to update: ");
    scanf("%d", &searchID);
    getchar();

    for (int i = 0; i < doctorCount; i++) {
        if (doctorArray[i].doctorID == searchID) {
            printf("Doctor found! Updating information...\n");

            do {
                printf("\nWhich field do you want to update?\n");
                printf("1. Name\n");
                printf("2. Age\n");
                printf("3. Address\n");
                printf("4. Specialization\n");
                printf("5. Contact Number\n");
                printf("6. Number of Patients Attending\n");
                printf("Enter your choice (1-6): ");
                scanf("%d", &choice);
                getchar();

                switch(choice) {
                    case 1:
                        printf("Enter new Name: ");
                        fgets(doctorArray[i].name, sizeof(doctorArray[i].name), stdin);
                        doctorArray[i].name[strcspn(doctorArray[i].name, "\n")] = 0;
                        break;
                    case 2:
                        printf("Enter new Age: ");
                        scanf("%d", &doctorArray[i].age);
                        getchar();
                        break;
                    case 3:
                        printf("Enter new Address: ");
                        fgets(doctorArray[i].address, sizeof(doctorArray[i].address), stdin);
                        doctorArray[i].address[strcspn(doctorArray[i].address, "\n")] = 0;
                        break;
                    case 4:
                        printf("Enter new Specialization: ");
                        fgets(doctorArray[i].specialization, sizeof(doctorArray[i].specialization), stdin);
                        doctorArray[i].specialization[strcspn(doctorArray[i].specialization, "\n")] = 0;
                        break;
                    case 5:
                        printf("Enter new Contact Number: ");
                        fgets(doctorArray[i].contactNumber, sizeof(doctorArray[i].contactNumber), stdin);
                        doctorArray[i].contactNumber[strcspn(doctorArray[i].contactNumber, "\n")] = 0;
                        break;
                    case 6:
                        printf("Enter new Number of Patients Attending: ");
                        scanf("%d", &doctorArray[i].patientsAttending);
                        getchar();
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                        continue;
                }

                printf("Do you want to update another field? (1 for Yes, 0 for No): ");
                scanf("%d", &choice);
                getchar();

            } while (choice == 1);  // If user wants to update another field

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Doctor with ID %d not found.\n", searchID);
    } else {

        freopen("doctors.txt", "w", fp);
        for (int i = 0; i < doctorCount; i++) {
            fprintf(fp, "Doctor ID: %d\nName: %s\nAge: %d\nAddress: %s\nSpecialization: %s\nContact Number: %s\nPatients Attending: %d\n\n", 
                    doctorArray[i].doctorID, doctorArray[i].name, doctorArray[i].age, doctorArray[i].address, 
                    doctorArray[i].specialization, doctorArray[i].contactNumber, doctorArray[i].patientsAttending);
        }
        printf("Doctor information updated successfully.\n");
    }

    fclose(fp);
}

void deleteDoctor() {
    FILE *fp;
    struct Doctor doctorArray[100];
    int doctorCount = 0;
    int searchID;
    int found = 0;

    fp = fopen("doctors.txt", "r+");
    if (fp == NULL) {
        printf("File cannot be opened.\n");
        return;
    }

    while (fscanf(fp, "Doctor ID: %d\nName: %[^\n]\nAge: %d\nAddress: %[^\n]\nSpecialization: %[^\n]\nContact Number: %[^\n]\nPatients Attending: %d\n\n", 
            &doctorArray[doctorCount].doctorID, doctorArray[doctorCount].name, 
            &doctorArray[doctorCount].age, doctorArray[doctorCount].address, 
            doctorArray[doctorCount].specialization, doctorArray[doctorCount].contactNumber, 
            &doctorArray[doctorCount].patientsAttending) != EOF) {
        doctorCount++;
    }

    printf("Enter Doctor ID to delete: ");
    scanf("%d", &searchID);

    for (int i = 0; i < doctorCount; i++) {
        if (doctorArray[i].doctorID == searchID) {
            found = 1;
            for (int j = i; j < doctorCount - 1; j++) {
                doctorArray[j] = doctorArray[j + 1];
            }
            doctorCount--;
            break;
        }
    }

    if (!found) {
        printf("Doctor with ID %d not found.\n", searchID);
    } else {
        freopen("doctors.txt", "w", fp);
        for (int i = 0; i < doctorCount; i++) {
            fprintf(fp, "Doctor ID: %d\nName: %s\nAge: %d\nAddress: %s\nSpecialization: %s\nContact Number: %s\nPatients Attending: %d\n\n", 
                    doctorArray[i].doctorID, doctorArray[i].name, doctorArray[i].age, doctorArray[i].address, 
                    doctorArray[i].specialization, doctorArray[i].contactNumber, doctorArray[i].patientsAttending);
        }
        printf("Doctor deleted successfully.\n");
    }

    fclose(fp);
}


int main() {
    int choice;

    do {
        printf("Menu:\n");
        printf("1. Add Doctor\n");
        printf("2. View All Doctors\n");
        printf("3. Update Doctor\n");
        printf("4. Delete Doctor\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addDoctor();
                break;
            case 2:
                readDoctors();
                break;
            case 3:
                updateDoctor();
                break;
            case 4:
                deleteDoctor();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}




