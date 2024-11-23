#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Doctor {
    int doctorID;
    char name[100];
    int age;
    char address[100];
    char specialization[50];
    char contactNumber[20];
    int patientsAttending;
};

void addDoctor(FILE *file) {
    struct Doctor doctor;
    printf("Enter Doctor ID: ");
    scanf("%d", & doctor.doctorID);
    getchar();

    printf("Enter Doctor's Name: ");
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

    printf("Enter Contact Number(+92-000-0000000): "); 
    fgets(doctor.contactNumber, sizeof(doctor.contactNumber), stdin);  
    doctor.contactNumber[strcspn(doctor.contactNumber, "\n")] = 0;  

    printf("Enter Number of Patients Attending: ");
    scanf("%d", &doctor.patientsAttending);

    fseek(file, 0, SEEK_END);
    fwrite(&doctor, sizeof(struct Doctor), 1, file);
}

void updateDoctor(FILE *file) {
    struct Doctor doctor;
    int doctorID, found = 0;
    printf("Enter Doctor ID to update: ");
    scanf("%d", &doctorID);
    getchar();

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Error opening file!\n");
        return;
    }

    rewind(file);
    while (fread(&doctor, sizeof(struct Doctor), 1, file)) {
        if (doctor.doctorID == doctorID) {
            found = 1;
            printf("Enter new Name (current: %s): ", doctor.name);
            fgets(doctor.name, sizeof(doctor.name), stdin);
            if (doctor.name[0] == '\n') strcpy(doctor.name, "");

            printf("Enter new Age (current: %d): ", doctor.age);
            scanf("%d", &doctor.age);
            getchar();

            printf("Enter new Address (current: %s): ", doctor.address);
            fgets(doctor.address, sizeof(doctor.address), stdin);
            if (doctor.address[0] == '\n') strcpy(doctor.address, "");

            printf("Enter new Specialization (current: %s): ", doctor.specialization);
            fgets(doctor.specialization, sizeof(doctor.specialization), stdin);
            if (doctor.specialization[0] == '\n') strcpy(doctor.specialization, "");

            printf("Enter new Contact Details (current: %s): ", doctor.contactNumber);
            fgets(doctor.contactNumber, sizeof(doctor.contactNumber), stdin);
            if (doctor.contactNumber[0] == '\n') strcpy(doctor.contactNumber, "");

            printf("Enter new Number of Patients Attending (current: %d): ", doctor.patientsAttending);
            scanf("%d", &doctor.patientsAttending);
        }
        fwrite(&doctor, sizeof(struct Doctor), 1, tempFile);
    }

    if (!found) {
        printf("Doctor not found.\n");
    }

    fclose(file);
    fclose(tempFile);
    remove("doctors.dat");
    rename("temp.dat", "doctors.dat");

    file = fopen("doctors.dat", "rb+");
    if (!file) {
        printf("Error reopening file!\n");
    }
}

void viewDoctors(FILE *file) {
    struct Doctor doctor;
    rewind(file);
    while (fread(&doctor, sizeof(struct Doctor), 1, file)) {
        printf("Doctor ID: %d\n", doctor.doctorID);
        printf("Name: %s\n", doctor.name);
        printf("Age: %d\n", doctor.age);
        printf("Address: %s\n", doctor.address);
        printf("Specialization: %s\n", doctor.specialization);
        printf("Contact Number: %d\n", doctor.contactNumber);
        printf("Patients Attending: %d\n", doctor.patientsAttending);
        printf("------------------------------\n");
    }
}

void deleteDoctor(FILE *file) {
    struct Doctor doctor;
    int doctorID, found = 0;
    printf("Enter Doctor ID to delete: ");
    scanf("%d", &doctorID);

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Error opening temporary file!\n");
        return;
    }

    rewind(file);
    while (fread(&doctor, sizeof(struct Doctor), 1, file)) {
        if (doctor.doctorID == doctorID && !found) {
            found = 1;  
            continue;
        }
        fwrite(&doctor, sizeof(struct Doctor), 1, tempFile);
    }

    if (!found) {
        printf("Doctor not found.\n");
    } else {
        printf("Doctor record deleted successfully.\n");
    }

    fclose(file);
    fclose(tempFile);
    remove("doctors.dat");
    rename("temp.dat", "doctors.dat");

    file = fopen("doctors.dat", "rb+");
    if (!file) {
        printf("Error reopening file!\n");
    }
}




