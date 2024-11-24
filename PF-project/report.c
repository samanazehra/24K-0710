#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generateDailyReport() {
    FILE *fp = fopen("patients.txt", "r");
    
    if (fp==NULL) {
        printf("Error opening patients file!\n");
        return;
    }

    int totalPatientsAdmitted = 0;
    int totalPatientsInHospital = 0;
    int totalSurgeriesToday = 0;
    int totalPatientsDischarged = 0;
    float totalRevenue = 0.0;

    char reportDate[11]; 
    printf("Enter the date for the report (dd-mm-yyyy): ");
    scanf("%s", reportDate);

    int patientID;
    char admissionDate[11], dischargeDate[11], surgeryDate[11];
    float surgeryCost;

    while (fscanf(patientsFile, "%d %s %s %s %f", &patientID, admissionDate, dischargeDate, surgeryDate, &surgeryCost) != EOF) {
      
        if (strcmp(admissionDate, reportDate) == 0) {
            totalPatientsAdmitted++;
        }
               
        if (strcmp(dischargeDate, reportDate) == 0) {
            totalPatientsDischarged++;
        }
        
        if (strcmp(surgeryDate, reportDate) == 0 && surgeryCost > 0) {
            totalSurgeriesToday++;
            totalRevenue += surgeryCost;
        }
        
        if (strcmp(dischargeDate, "00-00-0000") == 0) {
            totalPatientsInHospital++;
        }
    }

    fclose(patientsFile);

    printf("------- Daily Report for %s -------\n", reportDate);
    printf("Total Patients Admitted Today: %d\n", totalPatientsAdmitted);
    printf("Total Patients in the Hospital: %d\n", totalPatientsInHospital);
    printf("Total Surgeries Performed Today: %d\n", totalSurgeriesToday);
    printf("Total Patients Discharged Today: %d\n", totalPatientsDischarged);
    printf("Total Daily Revenue: %.2f\n", totalRevenue);
    printf("-----------------------------------------\n");
}
