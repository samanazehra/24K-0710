#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct pharmacyitem
{
    int id;
    char name[100];
    int quantity;
    float price;
    char type[50];
    char manufacturer[100];
} item;

FILE *fp;

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

void viewstock() {
    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("ID | Name           | Type           | Quantity | Price   | Manufacturer\n");
    printf("--------------------------------------------------------------------------\n");
    while (fscanf(fp, "%d %s %s %d %f %s", 
                  &item.id, item.name, item.type, 
                  &item.quantity, &item.price, item.manufacturer) != EOF) {
        printf("%d | %-15s | %-15s | %8d | %7.2f | %-15s\n", 
               item.id, item.name, item.type, 
               item.quantity, item.price, item.manufacturer);
    }
    fclose(fp);
}

void dispensestock() {
    viewstock();
    int itemID, quantity;
    float totalPrice;
    int found = 0;

    printf("Enter the item ID to dispense: ");
    scanf("%d", &itemID);

    printf("Enter the quantity to dispense: ");
    scanf("%d", &quantity);

    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    struct pharmacyitem items[100];
    int count = 0;

    while (fscanf(fp, "%d %s %s %d %f %s", 
                  &items[count].id, items[count].name, items[count].type, 
                  &items[count].quantity, &items[count].price, items[count].manufacturer) == 6) {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++) {
        if (items[i].id == itemID) {
            found = 1;
            if (items[i].quantity < quantity) {
                printf("Not enough stock available!\n");
                return;
            }

            items[i].quantity -= quantity;
            totalPrice = items[i].price * quantity;
            printf("Item: %s, Quantity: %d, Total Price: %.2f\n", items[i].name, quantity, totalPrice);
            break;
        }
    }

    if (!found) {
        printf("Item not found!\n");
        return;
    }

    fp = fopen("Pharmacy.txt", "w");
    if (fp == NULL) {
        printf("Error opening Pharmacy.txt for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %d %.2f %s\n", 
                items[i].id, items[i].name, items[i].type, 
                items[i].quantity, items[i].price, items[i].manufacturer);
    }

    fclose(fp);
}

void autoreorderstock() {
    int reorderunits = 50;
    struct pharmacyitem items[100];
    int count = 0;

    fp = fopen("Pharmacy.txt", "r");
    if (fp == NULL) {
        printf("Error opening Pharmacy.txt\n");
        return;
    }

    while (fscanf(fp, "%d %s %s %d %f %s", 
                  &items[count].id, items[count].name, items[count].type, 
                  &items[count].quantity, &items[count].price, items[count].manufacturer) == 6) {
        count++;
    }

    fclose(fp);

    for (int i = 0; i < count; i++) {
        if (items[i].quantity < reorderunits) {
            items[i].quantity += 50;
        }
    }

    fp = fopen("Pharmacy.txt", "w");
    if (fp == NULL) {
        printf("Error opening Pharmacy.txt for writing.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
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

    fp= fopen("Pharmacy.txt","r");
    if (fp==NULL)
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


void main()
{
    addstock();
    viewstock();
    dispensestock();
    autoreorderstock();
    generatebill();
}
