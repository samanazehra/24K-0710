#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player {
    char name[20];
    char team[20];
};

struct bowl {
    char type[10];
    char arm[5];
    struct player ply;
};

struct bat {
    char type[10];
    char handed[8];
    struct bowl ply2;
};

void createPlayer(struct bat playerData, const char *fileName);
void readPlayers(const char *fileName);
void updatePlayer(const char *fileName);
void deletePlayer(const char *fileName);

void createPlayer(struct bat playerData, const char *fileName) {
    FILE *file = fopen(fileName, "a");
    if (!file) {
        perror("Error opening file");
        return;
    }
    fprintf(file, "%s %s %s %s %s %s\n",
            playerData.ply2.ply.name, playerData.ply2.ply.team,
            playerData.ply2.type, playerData.ply2.arm,
            playerData.type, playerData.handed);
    fclose(file);
}

void readPlayers(const char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    struct bat playerData;
    printf("Player Records:\n");
    printf("------------------------------------------------------------------\n");
    printf("| Name       | Team       | Bowl Type | Arm  | Bat Type | Handed |\n");
    printf("------------------------------------------------------------------\n");
    while (fscanf(file, "%19s %19s %9s %6s %9s %7s",
                  playerData.ply2.ply.name, playerData.ply2.ply.team,
                  playerData.ply2.type, playerData.ply2.arm,
                  playerData.type, playerData.handed) == 6) {
        printf("| %-10s | %-10s | %-9s | %-4s | %-8s | %-6s |\n",
               playerData.ply2.ply.name, playerData.ply2.ply.team,
               playerData.ply2.type, playerData.ply2.arm,
               playerData.type, playerData.handed);
    }
    printf("------------------------------------------------------------------\n");
    fclose(file);
}

void updatePlayer(const char *fileName) {
    char name[20];
    printf("Enter the name of the player to update: ");
    scanf("%19s", name);

    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    struct bat playerData;
    char buffer[100][256];
    int count = 0, found = 0;

    while (fscanf(file, "%19s %19s %9s %9s %9s %7s",
                  playerData.ply2.ply.name, playerData.ply2.ply.team,
                  playerData.ply2.type, playerData.ply2.arm,
                  playerData.type, playerData.handed) == 6) {
        if (strcmp(playerData.ply2.ply.name, name) == 0) {
            found = 1;
            printf("Enter new details:\n");
            printf("Name: ");
            scanf("%19s", playerData.ply2.ply.name);
            printf("Team: ");
            scanf("%19s", playerData.ply2.ply.team);
            printf("Bowling Type (seemer, pacer, spinner): ");
            scanf("%9s", playerData.ply2.type);
            printf("Bowling Arm (left, right): ");
            scanf("%9s", playerData.ply2.arm);
            printf("Batting Type (top, middle, lower): ");
            scanf("%9s", playerData.type);
            printf("Handedness (lefty, righty): ");
            scanf("%7s", playerData.handed);
        }
        sprintf(buffer[count++], "%s %s %s %s %s %s\n",
                playerData.ply2.ply.name, playerData.ply2.ply.team,
                playerData.ply2.type, playerData.ply2.arm,
                playerData.type, playerData.handed);
    }
    fclose(file);

    if (!found) {
        printf("Player not found.\n");
        return;
    }
    file = fopen(fileName, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < count; i++) {
        fputs(buffer[i], file);
    }
    fclose(file);
    printf("Player updated successfully.\n");
}


void deletePlayer(const char *fileName) {
    char name[20];
    printf("Enter the name of the player to delete: ");
    scanf("%19s", name);
    FILE *file = fopen(fileName, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }
    struct bat playerData;
    char buffer[100][256];
    int count = 0, found = 0;
    while (fscanf(file, "%19s %19s %9s %6s %9s %7s",
                  playerData.ply2.ply.name, playerData.ply2.ply.team,
                  playerData.ply2.type, playerData.ply2.arm,
                  playerData.type, playerData.handed) == 6) {
        if (strcmp(playerData.ply2.ply.name, name) == 0) {
            found = 1;
            continue;
        }
        sprintf(buffer[count++], "%s %s %s %s %s %s\n",
                playerData.ply2.ply.name, playerData.ply2.ply.team,
                playerData.ply2.type, playerData.ply2.arm,
                playerData.type, playerData.handed);
    }
    fclose(file);
    if (!found) {
        printf("Player not found.\n");
        return;
    }
    file = fopen(fileName, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < count; i++) {
        fputs(buffer[i], file);
    }
    fclose(file);
    printf("Player deleted successfully.\n");
}

int main() {
    const char *fileName = "players.txt";
    struct bat playerData;
    int choice;
    do {
        printf("Player Management System\n");
        printf("1. Add Player\n");
        printf("2. View Players\n");
        printf("3. Update Player\n");
        printf("4. Delete Player\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter player details:\n");
                printf("Name: ");
                scanf("%19s", playerData.ply2.ply.name);
                printf("Team: ");
                scanf("%19s", playerData.ply2.ply.team);
                printf("Bowling Type (seemer, pacer, spinner): ");
                scanf("%9s", playerData.ply2.type);
                printf("Bowling Arm (left, right): ");
                scanf("%6s", playerData.ply2.arm);
                printf("Batting Type (top, middle, lower): ");
                scanf("%9s", playerData.type);
                printf("Handedness (lefty, righty): ");
                scanf("%7s", playerData.handed);
                createPlayer(playerData, fileName);
                printf("Player added successfully.\n");
                break;
            case 2:
                readPlayers(fileName);
                break;
            case 3:
                updatePlayer(fileName);
                break;
            case 4:
                deletePlayer(fileName);
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
    return 0;
}
