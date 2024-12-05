#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 100

// Structure to store shop items
typedef struct {
    int id;
    char name[50];
    float price;
    char quantity[10]; // Store quantity as a string to include units
} Item;

// Global variables
Product supershop[MAX_ITEMS]; // Array to hold items
int product_count = 0;
User users[MAX_USERS]; // Array to hold users
int userCount = 0;

void addItem(char *name, float price, char *quantity, float discount);  //Ariyan
void deleteItem(char *name);    //Ariyan
void updateItem(char *name);    //Ariyan
float enterDiscount();  //ariyan
// Function to add an item to the shop
void addItem(char *name, float price, char *quantity, float discount) {

    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    product_count = 0;

    while (fscanf(file, "%d %s %f %s %f", &supershop[product_count].id, supershop[product_count].name,
                  &supershop[product_count].price, supershop[product_count].quantity,
                  &supershop[product_count].discount) != EOF) {
        product_count++;
    }
    fclose(file);

    supershop[product_count].id = product_count + 1; // Automatically assign a unique ID
    strcpy(supershop[product_count].name, name);
    supershop[product_count].price = price;
    strcpy(supershop[product_count].quantity, quantity);
    supershop[product_count].discount = discount;

    file = fopen("inventory.txt", "a");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }
    fprintf(file, "%d %s %.2f %s %.2f\n", supershop[product_count].id, supershop[product_count].name,
            supershop[product_count].price, supershop[product_count].quantity, supershop[product_count].discount);
    fclose(file);

    product_count++;
}

// Function to delete an item from the shop
void deleteItem(char *name) {
    int found = 0;
    FILE *file = fopen("inventory.txt", "r");
    FILE *tempFile = fopen("temp_inventory.txt", "w"); // Temporary file for updated inventory

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "%d %s %f %s %f", &supershop[product_count].id, supershop[product_count].name,
                  &supershop[product_count].price, supershop[product_count].quantity,
                  &supershop[product_count].discount) != EOF) {

        if (strcmp(supershop[product_count].name, name) == 0) {
            found = 1;
            printf("\nProduct with name '%s' has been deleted.\n", name);
            continue; // Skip writing this item to the temp file
        }
        fprintf(tempFile, "%d %s %.2f %s %.2f\n", supershop[product_count].id, supershop[product_count].name,
                supershop[product_count].price, supershop[product_count].quantity, supershop[product_count].discount);
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated one
    remove("inventory.txt");
    rename("temp_inventory.txt", "inventory.txt");

    if (!found) {
        printf("Product with name '%s' not found in the supershop.\n", name);
    }
    view_menu(1);
}

// Function to update an item in the shop
void updateItem(char *name) {
    int found = 0;
    FILE *file = fopen("inventory.txt", "r");
    FILE *tempFile = fopen("temp_inventory.txt", "w");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(file, "%d %s %f %s %f", &supershop[product_count].id, supershop[product_count].name,
                  &supershop[product_count].price, supershop[product_count].quantity,
                  &supershop[product_count].discount) != EOF) {

        if (strcmp(supershop[product_count].name, name) == 0) {
            found = 1;
            printf("\nUpdating product with name: %s.\n", name);

            float price;
            char quantity[10];
            float discount;

            printf("Enter new price: ");
            scanf("%f", &price);
            printf("Enter new quantity (e.g., 10L or 250gm): ");
            scanf(" %9s", quantity);
            printf("Do you want to add a discount? (1 for Yes, 0 for No): ");
            int addDiscount;
            scanf("%d", &addDiscount);

            if (addDiscount) {
                discount = enterDiscount();
            } else {
                discount = 0.0;
            }
            // Update item details
            strcpy(supershop[product_count].name, name);
            supershop[product_count].price = price;
            strcpy(supershop[product_count].quantity, quantity);
            supershop[product_count].discount = discount;

            printf("\nProduct with name %s has been updated successfully.\n", name);
        }

        // Write the item to the temporary file
        fprintf(tempFile, "%d %s %.2f %s %.2f\n", supershop[product_count].id, supershop[product_count].name,
                supershop[product_count].price, supershop[product_count].quantity, supershop[product_count].discount);
        product_count++;
    }

    fclose(file);
    fclose(tempFile);

    // Replace the original file with the updated one
    remove("inventory.txt");
    rename("temp_inventory.txt", "inventory.txt");

    if (!found) {
        printf("Product with name %s not found in the supershop.\n", name);
    }
    view_menu(1);
}

// Function to enter discount percentage
float enterDiscount() {
    float discount;
    printf("Enter discount percentage: ");
    scanf("%f", &discount);
    return discount;
}
