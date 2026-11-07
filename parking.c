#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

struct Vehicle {
    int slot;
    char number[20];
    char owner[50];
};

struct Vehicle *vehicles;
int count = 0;

void loadData() {

    FILE *fp = fopen("parking.txt", "r");

    if (fp == NULL)
        return;

    struct Vehicle v;

    while (count < MAX &&
           fscanf(fp, "%d|%19[^|]|%49[^\n]\n",
                  &v.slot, v.number, v.owner) == 3) {

        vehicles[count++] = v;
    }

    fclose(fp);
}

void saveData() {

    FILE *fp = fopen("parking.txt", "w");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    for (int i = 0; i < count; i++) {

        fprintf(fp, "%d|%s|%s\n",
                vehicles[i].slot,
                vehicles[i].number,
                vehicles[i].owner);
    }

    fclose(fp);
}

void parkVehicle() {

    if (count >= MAX) {
        printf("Parking lot is full!\n");
        return;
    }

    struct Vehicle v;

    printf("Enter Slot Number (1-50): ");
    scanf("%d", &v.slot);

    if (v.slot < 1 || v.slot > MAX) {
        printf("Invalid slot number!\n");
        return;
    }

    for (int i = 0; i < count; i++) {

        if (vehicles[i].slot == v.slot) {
            printf("Slot already occupied!\n");
            return;
        }

        if (strcmp(vehicles[i].number, "") != 0) {
            if (strcmp(vehicles[i].number, v.number) == 0) {
                printf("Vehicle already parked!\n");
                return;
            }
        }
    }

    printf("Enter Vehicle Number: ");
    scanf(" %19s", v.number);

    for (int i = 0; i < count; i++) {
        if (strcmp(vehicles[i].number, v.number) == 0) {
            printf("Vehicle already parked!\n");
            return;
        }
    }

    printf("Enter Owner Name: ");
    scanf(" %49[^\n]", v.owner);

    vehicles[count++] = v;

    saveData();

    printf("Vehicle parked successfully!\n");
}

void displayVehicles() {

    if (count == 0) {
        printf("No vehicles parked!\n");
        return;
    }

    printf("\n===== PARKED VEHICLES =====\n");

    for (int i = 0; i < count; i++) {

        printf("\nSlot Number: %d\n", vehicles[i].slot);
        printf("Vehicle Number: %s\n", vehicles[i].number);
        printf("Owner: %s\n", vehicles[i].owner);
    }

    printf("\nOccupied Slots: %d", count);
    printf("\nAvailable Slots: %d\n", MAX - count);
}

void removeVehicle() {

    int slot, found = -1;

    printf("Enter Slot Number: ");
    scanf("%d", &slot);

    for (int i = 0; i < count; i++) {

        if (vehicles[i].slot == slot) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Vehicle not found!\n");
        return;
    }

    for (int i = found; i < count - 1; i++) {
        vehicles[i] = vehicles[i + 1];
    }

    count--;

    saveData();

    printf("Vehicle removed successfully!\n");
}

void searchVehicle() {

    char number[20];
    int found = 0;

    printf("Enter Vehicle Number: ");
    scanf(" %19s", number);

    for (int i = 0; i < count; i++) {

        if (strcmp(vehicles[i].number, number) == 0) {

            printf("\nVehicle Found!\n");
            printf("Slot: %d\n", vehicles[i].slot);
            printf("Owner: %s\n", vehicles[i].owner);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Vehicle not found!\n");
}

int main() {

    vehicles = malloc(MAX * sizeof(struct Vehicle));

    if (vehicles == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    loadData();

    int choice;

    do {

        printf("\n===== PARKING MANAGEMENT =====\n");
        printf("1. Park Vehicle\n");
        printf("2. Display Vehicles\n");
        printf("3. Remove Vehicle\n");
        printf("4. Search Vehicle\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                parkVehicle();
                break;

            case 2:
                displayVehicles();
                break;

            case 3:
                removeVehicle();
                break;

            case 4:
                searchVehicle();
                break;

            case 5:
                printf("Exiting Parking System!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    free(vehicles);

    return 0;
}
