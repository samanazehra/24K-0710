#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int patient_ID;
    char name[100];
    int age;
    char gender[10];
    char disease[200];
    int duration;  // Duration (days) of admission 
    int bp;  
    int pulse;  
    char medicineTimings[200];  
    int medicineQuantity;   
    char doctor[100]; 
    int surgery;  // Surgery flag (0 = no surgery, 1 = surgery done)
};

void addPatient(FILE *file) {
    struct Patient New_Patient;
    printf("Enter Patient ID: ");
    scanf("%d", & New_Patient.patient_ID);
    getchar();

    printf("Enter Patient's Name: ");
    fgets(New_Patient.name, sizeof(New_Patient.name), stdin);
    New_Patient.name[strcspn(New_Patient.name, "\n")] = 0;

    printf("Enter Patient's Age: ");
    scanf("%d", & New_Patient.age);

    printf("Enter Patient's Gender: ");
    getchar();
    fgets(New_Patient.gender, sizeof(New_Patient.gender), stdin);
    New_Patient.gender[strcspn(New_Patient.gender, "\n")] = 0;

    printf("Enter Patient's Disease: ");
    fgets(New_Patient.disease, sizeof(New_Patient.disease), stdin);
    New_Patient.disease[strcspn(New_Patient.disease, "\n")] = 0;

    printf("Enter Duration of Admission (in days): ");
    scanf("%d", & New_Patient.duration);

    printf("Enter Patient's Blood Pressure(BP): ");
    scanf("%d", & New_Patient.bp);

    printf(" Enter Patient's Pulse rate: ");
    scanf("%d", & New_Patient.pulse);

    getchar();  
    printf("Enter Patient's Medicine Timings (e.g:'8 AM, 2 PM, 9 PM'): ");
    fgets(New_Patient.medicineTimings, sizeof(New_Patient.medicineTimings), stdin);
    New_Patient.medicineTimings[strcspn(New_Patient.medicineTimings, "\n")] = 0; 
  
    printf("Enter Medicine Quantity (e.g., 2.0 tablets): ");
    scanf("%d", &New_Patient.medicineQuantity);

    printf("Enter Attending Doctor's Name: ");
    fgets(New_Patient.doctor, sizeof(New_Patient.doctor), stdin);
    New_Patient.doctor[strcspn(New_Patient.doctor, "\n")] = 0;

    printf("Has any Surgery been performed? (0 = No, 1 = Yes): ");
    scanf("%d", & New_Patient.surgery);

    fwrite(& New_Patient, sizeof(struct Patient), 1, file);
}

void updatePatient(FILE *file) {
    struct Patient patient;
    int patientID, found = 0;
    printf("Enter Patient ID to update: ");
    scanf("%d", &patientID);
    
    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Error opening file!\n");
        return;
    }

    rewind(file); 
    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        if (patient.patient_ID == patientID) {
            found = 1;
            printf("Enter new Blood Pressure: ", patient.bp);
            scanf("%d", & patient.bp);

            printf("Enter new Pulse Rate: ", patient.pulse);
            scanf("%d", & patient.pulse);

            printf("Enter updated Medicine Timings, or press Enter to keep unchanged: ", patient.medicineTimings);
            getchar();
            fgets(patient.medicineTimings, sizeof(patient.medicineTimings), stdin);
          
            if (patient.medicineTimings[0] == '\n') {
                strcpy(patient.medicineTimings, "");  
            } else {
                patient.medicineTimings[strcspn(patient.medicineTimings, "\n")] = 0;
            }

            printf("Has any Surgery been performed? (current: %s, 0 = No, 1 = Yes): ", patient.surgery ? "Yes" : "No");
            scanf("%d", & patient.surgery);
        }
        fwrite(&patient, sizeof(struct Patient), 1, tempFile);
    }

    if (!found) {
        printf("Patient not found.\n");
    }

    fclose(file);
    fclose(tempFile);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    file = fopen("patients.dat", "rb+");
    if (!file) {
        printf("Error reopening file!\n");
    }
}

void viewPatients(FILE *file) {
    struct Patient patient;
    rewind(file);
    while (fread(&patient, sizeof(struct Patient), 1, file)) {
        printf("Patient ID: %d\n", patient.patient_ID);
        printf("Name: %s\n", patient.name);
        printf("Age: %d\n", patient.age);
        printf("Gender: %s\n", patient.gender);
        printf("Disease: %s\n", patient.disease);
        printf("Duration of Admission: %d days\n", patient.duration);
        printf("Blood Pressure: %d\n", patient.bp);
        printf("Pulse Rate: %d\n", patient.pulse);
        printf("Medicine Timings: %s\n", patient.medicineTimings);
        printf("Medicine Quantity: %d\n", patient.medicineQuantity);
        printf("Doctor: %s\n", patient.doctor);
        printf("Surgery: %s\n", patient.surgery? "Yes" : "No");
        printf("------------------------------\n");
    }
}

void deletePatient(FILE *file) {
    struct Patient patient;
    int patientID, found = 0;
    printf("Enter Patient ID to delete: ");
    scanf("%d", & patientID);

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile) {
        printf("Error opening temporary file!\n");
        return;
    }

    rewind(file);
    int position = 0; 
    while (fread(& patient, sizeof(struct Patient), 1, file)) {
        if (patient.patient_ID == patientID && !found) {
            found = 1;  
            printf("Patient ID %d has been discharged.\n", patientID);
            continue;
        }
      
        fwrite(&patient, sizeof(struct Patient), 1, tempFile);
    }

    if (!found) {
        printf("Patient not found.\n");
    } else {
        printf("Patient record deleted successfully.\n");
    }

    fclose(file);
    fclose(tempFile);
    remove("patients.dat");
    rename("temp.dat", "patients.dat");

    file = fopen("patients.dat", "rb+");
    if (!file) {
        printf("Error reopening file!\n");
    }
}

