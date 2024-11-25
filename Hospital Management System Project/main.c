#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

FILE *fp;

void doctormenu(int doctorchoice);
void patientmenu(int patientchoice);
void pharmacymenu(int choice);

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
    char address[200];
    char specialization[100];
    char contactNumber[20];
    int patientsAttending;
} doctor;

struct Patient
{
    int patientID;
    char name[100];
    int age;
    char gender[10];
    char disease[100];
    int durationOfDays;
    float bp;
    float pulseRate;
    char medicineTimings[100];
    int medicineQuantity;
    char doctorAttending[100];
    int surgeryDone;
    char surgeryName[100];
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

void generatedailyreport()
{
    FILE *fp = fopen("dates.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening patients file!\n");
        return;
    }

    int totalPatientsAdmitted = 0;
    int totalPatientsInHospital = 0;
    int totalSurgeriesToday = 0;
    int totalPatientsDischarged = 0;

    char reportDate[11];
    printf("Enter the date for the report (dd-mm-yyyy): ");
    scanf("%s", reportDate);

    int patientID, surgerycost, totalrevenue=0, count=0;
    char admissionDate[11], dischargeDate[11], surgeryDate[11];

    while (fscanf(fp, "%d %s %s %s %d", &patientID, admissionDate, dischargeDate, surgeryDate, &surgerycost) != EOF)
    {
        count++;
        if (strcmp(admissionDate, reportDate) == 0)
        {
            totalPatientsAdmitted++;
        }

        if (strcmp(dischargeDate, reportDate) == 0)
        {
            totalPatientsDischarged++;
        }

        if (strcmp(dischargeDate, "00-00-0000") == 0 || strlen(dischargeDate) == 0)
        {
            totalPatientsInHospital++;
        }
        for (int i = 0; i < count; i++)
        {   totalrevenue=0;
            totalrevenue+=surgerycost;
        }
        
    }

    fclose(fp);

    printf("------- Daily Report for %s -------\n", reportDate);
    printf("Total Patients Admitted Today: %d\n", totalPatientsAdmitted);
    printf("Total Patients in the Hospital: %d\n", totalPatientsInHospital);
    printf("Total Surgeries Performed Today: %d\n", totalSurgeriesToday);
    printf("Total Patients Discharged Today: %d\n", totalPatientsDischarged);
    printf("Total Revenue Generated Today: Rs. %d\n", totalrevenue);
    printf("-----------------------------------------\n");
}

void addDoctor()
{
    fp = fopen("doctors.txt", "a");
    if (fp == NULL)
    {
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

void readDoctors()
{
    fp = fopen("doctors.txt", "r");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

void updateDoctor()
{
    FILE *fp;
    struct Doctor doctorArray[100];
    int doctorCount = 0;
    int searchID;
    int found = 0;
    int choice;

    fp = fopen("doctors.txt", "r+");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    while (fscanf(fp, "Doctor ID: %d\nName: %[^\n]\nAge: %d\nAddress: %[^\n]\nSpecialization: %[^\n]\nContact Number: %[^\n]\nPatients Attending: %d\n\n",
                  &doctorArray[doctorCount].doctorID, doctorArray[doctorCount].name,
                  &doctorArray[doctorCount].age, doctorArray[doctorCount].address,
                  doctorArray[doctorCount].specialization, doctorArray[doctorCount].contactNumber,
                  &doctorArray[doctorCount].patientsAttending) != EOF)
    {
        doctorCount++;
    }

    printf("Enter Doctor ID to update: ");
    scanf("%d", &searchID);
    getchar();

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctorArray[i].doctorID == searchID)
        {
            printf("Doctor found! Updating information...\n");

            do
            {
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

                switch (choice)
                {
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

            } while (choice == 1);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Doctor with ID %d not found.\n", searchID);
    }
    else
    {

        freopen("doctors.txt", "w", fp);
        for (int i = 0; i < doctorCount; i++)
        {
            fprintf(fp, "Doctor ID: %d\nName: %s\nAge: %d\nAddress: %s\nSpecialization: %s\nContact Number: %s\nPatients Attending: %d\n\n",
                    doctorArray[i].doctorID, doctorArray[i].name, doctorArray[i].age, doctorArray[i].address,
                    doctorArray[i].specialization, doctorArray[i].contactNumber, doctorArray[i].patientsAttending);
        }
        printf("Doctor information updated successfully.\n");
    }

    fclose(fp);
}

void deleteDoctor()
{
    FILE *fp;
    struct Doctor doctorArray[100];
    int doctorCount = 0;
    int searchID;
    int found = 0;

    fp = fopen("doctors.txt", "r+");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    while (fscanf(fp, "Doctor ID: %d\nName: %[^\n]\nAge: %d\nAddress: %[^\n]\nSpecialization: %[^\n]\nContact Number: %[^\n]\nPatients Attending: %d\n\n",
                  &doctorArray[doctorCount].doctorID, doctorArray[doctorCount].name,
                  &doctorArray[doctorCount].age, doctorArray[doctorCount].address,
                  doctorArray[doctorCount].specialization, doctorArray[doctorCount].contactNumber,
                  &doctorArray[doctorCount].patientsAttending) != EOF)
    {
        doctorCount++;
    }

    printf("Enter Doctor ID to delete: ");
    scanf("%d", &searchID);

    for (int i = 0; i < doctorCount; i++)
    {
        if (doctorArray[i].doctorID == searchID)
        {
            found = 1;
            for (int j = i; j < doctorCount - 1; j++)
            {
                doctorArray[j] = doctorArray[j + 1];
            }
            doctorCount--;
            break;
        }
    }

    if (!found)
    {
        printf("Doctor with ID %d not found.\n", searchID);
    }
    else
    {
        freopen("doctors.txt", "w", fp);
        for (int i = 0; i < doctorCount; i++)
        {
            fprintf(fp, "Doctor ID: %d\nName: %s\nAge: %d\nAddress: %s\nSpecialization: %s\nContact Number: %s\nPatients Attending: %d\n\n",
                    doctorArray[i].doctorID, doctorArray[i].name, doctorArray[i].age, doctorArray[i].address,
                    doctorArray[i].specialization, doctorArray[i].contactNumber, doctorArray[i].patientsAttending);
        }
        printf("Doctor deleted successfully.\n");
    }

    fclose(fp);
}

void addPatient()
{
    fp = fopen("patients.txt", "a");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &patient.patientID);
    getchar();

    printf("Enter Name: ");
    fgets(patient.name, sizeof(patient.name), stdin);
    patient.name[strcspn(patient.name, "\n")] = 0;

    printf("Enter Age: ");
    scanf("%d", &patient.age);
    getchar();

    printf("Enter Gender: ");
    fgets(patient.gender, sizeof(patient.gender), stdin);
    patient.gender[strcspn(patient.gender, "\n")] = 0;

    printf("Enter Disease: ");
    fgets(patient.disease, sizeof(patient.disease), stdin);
    patient.disease[strcspn(patient.disease, "\n")] = 0;

    printf("Enter Duration of Days Admitted: ");
    scanf("%d", &patient.durationOfDays);

    printf("Enter Blood Pressure: ");
    scanf("%f", &patient.bp);

    printf("Enter Pulse Rate: ");
    scanf("%f", &patient.pulseRate);
    getchar();

    printf("Enter Medicine Timings: ");
    fgets(patient.medicineTimings, sizeof(patient.medicineTimings), stdin);
    patient.medicineTimings[strcspn(patient.medicineTimings, "\n")] = 0;

    printf("Enter Medicine Quantity: ");
    scanf("%d", &patient.medicineQuantity);
    getchar();

    printf("Enter Doctor Attending: ");
    fgets(patient.doctorAttending, sizeof(patient.doctorAttending), stdin);
    patient.doctorAttending[strcspn(patient.doctorAttending, "\n")] = 0;

    printf("Was surgery performed (1 for Yes, 0 for No): ");
    scanf("%d", &patient.surgeryDone);

    if (patient.surgeryDone == 1)
    {
        printf("Enter Surgery Name: ");
        getchar();
        fgets(patient.surgeryName, sizeof(patient.surgeryName), stdin);
        patient.surgeryName[strcspn(patient.surgeryName, "\n")] = 0;
    }

    fprintf(fp, "Patient ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDuration of Days: %d\nBlood Pressure: %.2f\nPulse Rate: %.2f\nMedicine Timings: %s\nMedicine Quantity: %d\nDoctor Attending: %s\nSurgery Done: %d\nSurgery Name: %s\n\n",
            patient.patientID, patient.name, patient.age, patient.gender,
            patient.disease, patient.durationOfDays, patient.bp, patient.pulseRate,
            patient.medicineTimings, patient.medicineQuantity, patient.doctorAttending,
            patient.surgeryDone, patient.surgeryDone == 1 ? patient.surgeryName : "None");

    fclose(fp);
}

void readPatients()
{
    fp = fopen("patients.txt", "r");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

void updatePatient()
{
    struct Patient patientArray[100];
    int patientCount = 0;
    int searchID;
    int found = 0;
    int choice;

    fp = fopen("patients.txt", "r");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    while (fscanf(fp, "Patient ID: %d\nName: %[^\n]\nAge: %d\nGender: %[^\n]\nDisease: %[^\n]\nDuration of Days: %d\nBlood Pressure: %f\nPulse Rate: %f\nMedicine Timings: %[^\n]\nMedicine Quantity: %d\nDoctor Attending: %[^\n]\nSurgery Done: %d\nSurgery Name: %[^\n]\n\n",
                  &patientArray[patientCount].patientID, patientArray[patientCount].name,
                  &patientArray[patientCount].age, patientArray[patientCount].gender,
                  patientArray[patientCount].disease, &patientArray[patientCount].durationOfDays,
                  &patientArray[patientCount].bp, &patientArray[patientCount].pulseRate,
                  patientArray[patientCount].medicineTimings, &patientArray[patientCount].medicineQuantity,
                  patientArray[patientCount].doctorAttending, &patientArray[patientCount].surgeryDone,
                  patientArray[patientCount].surgeryName) != EOF)
    {
        patientCount++;
    }
    fclose(fp);

    printf("Enter Patient ID to update: ");
    scanf("%d", &searchID);
    getchar();

    for (int i = 0; i < patientCount; i++)
    {
        if (patientArray[i].patientID == searchID)
        {
            found = 1;
            printf("Patient found! Updating information...\n");

            do
            {
                printf("\nWhich field do you want to update?\n");
                printf("1. Name\n");
                printf("2. Age\n");
                printf("3. Gender\n");
                printf("4. Disease\n");
                printf("5. Duration of Days\n");
                printf("6. Blood Pressure\n");
                printf("7. Pulse Rate\n");
                printf("8. Medicine Timings\n");
                printf("9. Medicine Quantity\n");
                printf("10. Doctor Attending\n");
                printf("11. Surgery Done\n");
                printf("12. Surgery Name (if applicable)\n");
                printf("Enter your choice (1-12): ");
                scanf("%d", &choice);
                getchar();

                switch (choice)
                {
                case 1:
                    printf("Enter new Name: ");
                    fgets(patientArray[i].name, sizeof(patientArray[i].name), stdin);
                    patientArray[i].name[strcspn(patientArray[i].name, "\n")] = 0;
                    break;
                case 2:
                    printf("Enter new Age: ");
                    scanf("%d", &patientArray[i].age);
                    getchar();
                    break;
                case 3:
                    printf("Enter new Gender: ");
                    fgets(patientArray[i].gender, sizeof(patientArray[i].gender), stdin);
                    patientArray[i].gender[strcspn(patientArray[i].gender, "\n")] = 0;
                    break;
                case 4:
                    printf("Enter new Disease: ");
                    fgets(patientArray[i].disease, sizeof(patientArray[i].disease), stdin);
                    patientArray[i].disease[strcspn(patientArray[i].disease, "\n")] = 0;
                    break;
                case 5:
                    printf("Enter new Duration of Days: ");
                    scanf("%d", &patientArray[i].durationOfDays);
                    getchar();
                    break;
                case 6:
                    printf("Enter new Blood Pressure: ");
                    scanf("%f", &patientArray[i].bp);
                    break;
                case 7:
                    printf("Enter new Pulse Rate: ");
                    scanf("%f", &patientArray[i].pulseRate);
                    break;
                case 8:
                    printf("Enter new Medicine Timings: ");
                    fgets(patientArray[i].medicineTimings, sizeof(patientArray[i].medicineTimings), stdin);
                    patientArray[i].medicineTimings[strcspn(patientArray[i].medicineTimings, "\n")] = 0;
                    break;
                case 9:
                    printf("Enter new Medicine Quantity: ");
                    scanf("%d", &patientArray[i].medicineQuantity);
                    getchar();
                    break;
                case 10:
                    printf("Enter new Doctor Attending: ");
                    fgets(patientArray[i].doctorAttending, sizeof(patientArray[i].doctorAttending), stdin);
                    patientArray[i].doctorAttending[strcspn(patientArray[i].doctorAttending, "\n")] = 0;
                    break;
                case 11:
                    printf("Was surgery performed (1 for Yes, 0 for No): ");
                    scanf("%d", &patientArray[i].surgeryDone);
                    getchar();
                    if (patientArray[i].surgeryDone == 0)
                    {
                        strcpy(patientArray[i].surgeryName, "None");
                    }
                    break;
                case 12:
                    if (patientArray[i].surgeryDone)
                    {
                        printf("Enter new Surgery Name: ");
                        fgets(patientArray[i].surgeryName, sizeof(patientArray[i].surgeryName), stdin);
                        patientArray[i].surgeryName[strcspn(patientArray[i].surgeryName, "\n")] = 0;
                    }
                    else
                    {
                        printf("No surgery was performed. Cannot update Surgery Name.\n");
                    }
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                }

                printf("Do you want to update another field? (1 for Yes, 0 for No): ");
                scanf("%d", &choice);
                getchar();

            } while (choice == 1);

            break;
        }
    }

    if (found)
    {
        fp = fopen("patients.txt", "w");
        for (int i = 0; i < patientCount; i++)
        {
            fprintf(fp, "Patient ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDuration of Days: %d\nBlood Pressure: %.2f\nPulse Rate: %.2f\nMedicine Timings: %s\nMedicine Quantity: %d\nDoctor Attending: %s\nSurgery Done: %d\nSurgery Name: %s\n\n",
                    patientArray[i].patientID, patientArray[i].name, patientArray[i].age,
                    patientArray[i].gender, patientArray[i].disease, patientArray[i].durationOfDays,
                    patientArray[i].bp, patientArray[i].pulseRate, patientArray[i].medicineTimings,
                    patientArray[i].medicineQuantity, patientArray[i].doctorAttending,
                    patientArray[i].surgeryDone, patientArray[i].surgeryName);
        }
        fclose(fp);
        printf("Patient information updated successfully.\n");
    }
    else
    {
        printf("Patient with ID %d not found.\n", searchID);
    }
}

void dischargePatient()
{
    struct Patient patientArray[100];
    int patientCount = 0;
    int searchID;
    int found = 0;

    fp = fopen("patients.txt", "r");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    while (fscanf(fp, "Patient ID: %d\nName: %[^\n]\nAge: %d\nGender: %[^\n]\nDisease: %[^\n]\nDuration of Days: %d\nBlood Pressure: %f\nPulse Rate: %f\nMedicine Timings: %[^\n]\nMedicine Quantity: %d\nDoctor Attending: %[^\n]\nSurgery Done: %d\nSurgery Name: %[^\n]\n\n",
                  &patientArray[patientCount].patientID, patientArray[patientCount].name,
                  &patientArray[patientCount].age, patientArray[patientCount].gender,
                  patientArray[patientCount].disease, &patientArray[patientCount].durationOfDays,
                  &patientArray[patientCount].bp, &patientArray[patientCount].pulseRate,
                  patientArray[patientCount].medicineTimings, &patientArray[patientCount].medicineQuantity,
                  patientArray[patientCount].doctorAttending, &patientArray[patientCount].surgeryDone,
                  patientArray[patientCount].surgeryName) != EOF)
    {
        patientCount++;
    }
    fclose(fp);

    printf("Enter Patient ID to discharge: ");
    scanf("%d", &searchID);

    for (int i = 0; i < patientCount; i++)
    {
        if (patientArray[i].patientID == searchID)
        {
            found = 1;

            printf("Enter the number of days the patient was admitted: ");
            int daysadmitted;
            scanf("%d", &daysadmitted);

            float roomcharge = 4000;
            float medicinecharge = 2000;
            float healthtaxrate = 0.10;
            float subtotal = (roomcharge * daysadmitted) + medicinecharge;
            float tax = subtotal * healthtaxrate;
            float totalBill = subtotal + tax;

            printf("Bill Details for Patient ID: %d\n", searchID);
            printf("Admission Charges: %.2f per day x %d days = %.2f\n", roomcharge, daysadmitted, roomcharge * daysadmitted);
            printf("Medicine Charges: %.2f\n", medicinecharge);
            printf("Subtotal: %.2f\n", subtotal);
            printf("Health Tax (10%%): %.2f\n", tax);
            printf("Total Bill: Rs. %.2f\n", totalBill);

            for (int j = i; j < patientCount - 1; j++)
            {
                patientArray[j] = patientArray[j + 1];
            }
            patientCount--;
            break;
        }
    }

    if (found)
    {
        fp = fopen("patients.txt", "w");
        if (fp == NULL)
        {
            printf("Error opening file for writing.\n");
            return;
        }

        for (int i = 0; i < patientCount; i++)
        {
            fprintf(fp, "Patient ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDuration of Days: %d\nBlood Pressure: %.2f\nPulse Rate: %.2f\nMedicine Timings: %s\nMedicine Quantity: %d\nDoctor Attending: %s\nSurgery Done: %d\nSurgery Name: %s\n\n",
                    patientArray[i].patientID, patientArray[i].name, patientArray[i].age,
                    patientArray[i].gender, patientArray[i].disease, patientArray[i].durationOfDays,
                    patientArray[i].bp, patientArray[i].pulseRate, patientArray[i].medicineTimings,
                    patientArray[i].medicineQuantity, patientArray[i].doctorAttending,
                    patientArray[i].surgeryDone, patientArray[i].surgeryName);
        }
        fclose(fp);
        printf("Patient discharged successfully.\n");
    }
    else
    {
        printf("Patient with ID %d not found.\n", searchID);
    }
}

void assignDoctorToPatient()
{
    int foundPatient = 0;
    int doctorFound = 0;

    fp = fopen("patients.txt", "r+");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }

    printf("Enter Patient ID to assign doctor: ");
    int patientID;
    scanf("%d", &patientID);

    while (fscanf(fp, "Patient ID: %d\nName: %[^\n]\nAge: %d\nGender: %[^\n]\nDisease: %[^\n]\nDuration of Days: %d\nBlood Pressure: %f\nPulse Rate: %f\nMedicine Timings: %[^\n]\nMedicine Quantity: %d\nDoctor Attending: %[^\n]\nSurgery Done: %d\nSurgery Name: %[^\n]\n\n",
                  &patient.patientID, patient.name, &patient.age, patient.gender, patient.disease, &patient.durationOfDays,
                  &patient.bp, &patient.pulseRate, patient.medicineTimings, &patient.medicineQuantity, patient.doctorAttending,
                  &patient.surgeryDone, patient.surgeryName) != EOF)
    {
        if (patient.patientID == patientID)
        {
            foundPatient = 1;
            break;
        }
    }

    if (!foundPatient)
    {
        printf("Patient with ID %d not found.\n", patientID);
        fclose(fp);
        return;
    }
    fp = fopen("doctors.txt", "r+");
    if (fp == NULL)
    {
        printf("File cannot be opened.\n");
        return;
    }
    printf("Enter Doctor ID to assign: ");
    int doctorID;
    scanf("%d", &doctorID);

    while (fscanf(fp, "Doctor ID: %d\nName: %[^\n]\nAge: %d\nAddress: %[^\n]\nSpecialization: %[^\n]\nContact Number: %[^\n]\nPatients Attending: %d\n\n",
                  &doctor.doctorID, doctor.name, &doctor.age, doctor.address, doctor.specialization, doctor.contactNumber, &doctor.patientsAttending) != EOF)
    {
        if (doctor.doctorID == doctorID)
        {
            doctorFound = 1;
            if (doctor.patientsAttending < 6)
            {
                printf("Assigning patient %d to doctor %d...\n", patientID, doctorID);
                strcpy(patient.doctorAttending, doctor.name);
                doctor.patientsAttending++;

                fseek(fp, 0, SEEK_SET);
                while (fscanf(fp, "Patient ID: %d\nName: %[^\n]\nAge: %d\nGender: %[^\n]\nDisease: %[^\n]\nDuration of Days: %d\nBlood Pressure: %.2f\nPulse Rate: %.2f\nMedicine Timings: %[^\n]\nMedicine Quantity: %d\nDoctor Attending: %[^\n]\nSurgery Done: %d\nSurgery Name: %[^\n]\n\n",
                              &patient.patientID, patient.name, &patient.age, patient.gender, patient.disease, &patient.durationOfDays,
                              &patient.bp, &patient.pulseRate, patient.medicineTimings, &patient.medicineQuantity, patient.doctorAttending,
                              &patient.surgeryDone, patient.surgeryName) != EOF)
                {
                    if (patient.patientID == patientID)
                    {
                        fprintf(fp, "Patient ID: %d\nName: %s\nAge: %d\nGender: %s\nDisease: %s\nDuration of Days: %d\nBlood Pressure: %.2f\nPulse Rate: %.2f\nMedicine Timings: %s\nMedicine Quantity: %d\nDoctor Attending: %s\nSurgery Done: %d\nSurgery Name: %s\n\n",
                                patient.patientID, patient.name, patient.age, patient.gender, patient.disease, patient.durationOfDays,
                                patient.bp, patient.pulseRate, patient.medicineTimings, patient.medicineQuantity, patient.doctorAttending,
                                patient.surgeryDone, patient.surgeryName);
                    }
                }

                fseek(fp, 0, SEEK_SET);
                while (fscanf(fp, "Doctor ID: %d\nName: %[^\n]\nAge: %d\nAddress: %[^\n]\nSpecialization: %[^\n]\nContact Number: %[^\n]\nPatients Attending: %d\n\n",
                              &doctor.doctorID, doctor.name, &doctor.age, doctor.address, doctor.specialization, doctor.contactNumber, &doctor.patientsAttending) != EOF)
                {
                    if (doctor.doctorID == doctorID)
                    {
                        doctor.patientsAttending++;
                    }
                    fprintf(fp, "Doctor ID: %d\nName: %s\nAge: %d\nAddress: %s\nSpecialization: %s\nContact Number: %s\nPatients Attending: %d\n\n",
                            doctor.doctorID, doctor.name, doctor.age, doctor.address, doctor.specialization, doctor.contactNumber, doctor.patientsAttending);
                }

                printf("Patient assigned to doctor successfully.\n");
                break;
            }
            else
            {
                printf("Doctor %d has reached the maximum number of patients.\n", doctorID);
                fclose(fp);
                return;
            }
        }
    }

    if (!doctorFound)
    {
        printf("Doctor with ID %d not found.\n", doctorID);
    }

    fclose(fp);
}

void adminpanel(int choice)
{

    printf("\n1. Doctor Records Management\n");
    printf("2. Patient Records Management\n");
    printf("3. Pharmacy Medicine Stock Management\n");
    printf("4. Daily Report Generator\n");
    printf("5. Back to Main Menu\n");
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
        generatedailyreport();
        break;
    case 5:
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
            readDoctors();
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
        printf("4. Discharge Patient and Generate Bill\n");
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
            readPatients();
            break;
        case 4:
            dischargePatient();
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

void viewstock()
{
    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return;
    }

    printf("ID | Name           | Type           | Quantity | Price   | Manufacturer\n");
    printf("--------------------------------------------------------------------------\n");
    while (fscanf(fp, "%d %s %s %d %f %s",
                  &item.id, item.name, item.type,
                  &item.quantity, &item.price, item.manufacturer) != EOF)
    {
        printf("%d | %-15s | %-15s | %8d | %7.2f | %-15s\n",
               item.id, item.name, item.type,
               item.quantity, item.price, item.manufacturer);
    }
    fclose(fp);
}

void dispensestock()
{
    viewstock();
    int itemID, quantity;
    float totalPrice;
    int found = 0;

    printf("Enter the item ID to dispense: ");
    scanf("%d", &itemID);

    printf("Enter the quantity to dispense: ");
    scanf("%d", &quantity);

    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }

    struct pharmacyitem items[100];
    int count = 0;

    while (fscanf(fp, "%d %s %s %d %f %s",
                  &items[count].id, items[count].name, items[count].type,
                  &items[count].quantity, &items[count].price, items[count].manufacturer) == 6)
    {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++)
    {
        if (items[i].id == itemID)
        {
            found = 1;
            if (items[i].quantity < quantity)
            {
                printf("Not enough stock available!\n");
                return;
            }

            items[i].quantity -= quantity;
            totalPrice = items[i].price * quantity;
            printf("Item: %s, Quantity: %d, Total Price: %.2f\n", items[i].name, quantity, totalPrice);
            break;
        }
    }

    if (!found)
    {
        printf("Item not found!\n");
        return;
    }

    fp = fopen("Pharmacy.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening Pharmacy.txt for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d %s %s %d %.2f %s\n",
                items[i].id, items[i].name, items[i].type,
                items[i].quantity, items[i].price, items[i].manufacturer);
    }

    fclose(fp);
}

void autoreorderstock()
{
    int reorderunits = 50;
    struct pharmacyitem items[100];
    int count = 0;

    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening Pharmacy.txt\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %d %f %s",
                  &items[count].id, items[count].name, items[count].type,
                  &items[count].quantity, &items[count].price, items[count].manufacturer) == 6)
    {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++)
    {
        if (items[i].quantity < reorderunits)
        {
            items[i].quantity += 50;
        }
    }

    fp = fopen("Pharmacy.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening Pharmacy.txt for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
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

    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL)
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
            generatebill();
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
            printf("Admin login successful, welcome %s!\n\n", admin.username);
            fclose(fp);
            return 1;
            break;
        }
        else
            printf("Wrong username or password. Access denied.\n\n");
    }       return 0;
    fclose(fp);
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
        return 1;
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
        return 1;
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
    while (1)
    {   printf("----------------------------------------\n");
        printf("=== Shaukat Khanum Memorial Hospital ===\n");
        printf("----------------------------------------\n");
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
            if (adminlogin())
                adminpanel(choice);
            else
                printf("Invalid username or password. Access denied.\n");
            break;

        case 2:
            if (loginportal())
            {
                patientmenu(patientchoice);
                printf("Enter your choice: ");
                scanf("%d", &patientchoice);
            }
            else
                printf("Invalid username or password. Access denied.\n");
            break;

        case 3:
            adminsignup();
            break;

        case 4:
            signup();
            break;

        case 5:
            printf("Exiting the program. Goodbye!\n");
            return 0;

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}