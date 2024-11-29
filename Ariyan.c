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
Item supershop[MAX_ITEMS];

int supershopCount = 0;
int displayState = 1; //1=shop


// Function prototypes
void addItem(int id, char *name, float price, char *quantity);
void deleteItem(int id);
void updateItem(int id);
void displaySupershop();
void searchProductByName();

// Function to add items to the shop inventory
void addItem(int id, char *name, float price, char *quantity) {
    supershop[supershopCount].id = id;
    strcpy(supershop[supershopCount].name, name);
    supershop[supershopCount].price = price;
    strcpy(supershop[supershopCount].quantity, quantity);
    supershopCount++;
}

// Function to delete an item from the supershop
void deleteItem(int id) {
    int found = 0;
    for (int i = 0; i < supershopCount; i++) {
        if (supershop[i].id == id) {
            found = 1;
            for (int j = i; j < supershopCount - 1; j++) {
                supershop[j] = supershop[j + 1];
            }
            supershopCount--;
            printf("Item with ID %d has been deleted from the supershop.\n", id);
            break;
        }
    }
    if (!found) {
        printf("Item with ID %d not found in the supershop.\n", id);
    }
}

// Function to update an existing item in the supershop
void updateItem(int id) {
    for (int i = 0; i < supershopCount; i++) {
        if (supershop[i].id == id) {
            char name[50];
            float price;
            char quantity[10];

            printf("Updating item with ID %d.\n", id);
            printf("Enter new name: ");
            scanf(" %49[^\n]", name);
            printf("Enter new price: ");
            scanf("%f", &price);
            printf("Enter new quantity (e.g., 10L or 250gm): ");
            scanf(" %9s", quantity);

            strcpy(supershop[i].name, name);
            supershop[i].price = price;
            strcpy(supershop[i].quantity, quantity);

            printf("Item with ID %d has been updated successfully.\n", id);
            return;
        }
    }
    printf("Item with ID %d not found in the supershop.\n", id);
}

// Function to display items in the supershop
void displaySupershop() {
    printf("\n==================== Supershop ============================\n");
    printf("| %-5s | %-20s | %-12s | %-10s |\n", "ID", "Name", "Price(taka)", "Stock");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < supershopCount; i++) {
        printf("| %-5d | %-20s | %-12.2f | %-10s |\n",
               supershop[i].id, supershop[i].name, supershop[i].price, supershop[i].quantity);
    }
    printf("============================================================\n");
}

// Function to search for a product by name
void searchProductByName() {
    char searchName[50];
    int found = 0;

    printf("Enter product name to search: ");
    scanf(" %c", &searchName);

    printf("\n--- Search Results ---\n");
    for (int i = 0; i < supershopCount; i++) {
        if (strstr(supershop[i].name, searchName)) {
            printf("ID: %d, Name: %s, Price: %.2f, Stock: %s\n",
                   supershop[i].id, supershop[i].name, supershop[i].price, supershop[i].quantity);
            found = 1;
        }
    }

    if (!found) {
        printf("No products found matching '%s'.\n", searchName);
    }
}

int main() {


    addItem(1, "Milk ", 70, "100L");
    addItem(2, "Bread ", 30, "100pcs");
    addItem(3, "Eggs ", 12, "200pcs");
    addItem(4, "Oil ", 160, "500L");
    addItem(5, "Vasline ", 70, "300pcs");
    addItem(6, "Lotion ", 30, "250pcs");
    addItem(7, "Onion ", 12, "200kg");
    addItem(8, "Meat ", 720, "100kg");




    int choice;
    do {
        printf("\n======= Supershop Management =======\n");
        printf("1. Display Supershop Inventory\n");
        printf("2. Add Item\n");
        printf("3. Delete Item\n");
        printf("4. Update Item\n");
        printf("5. Search Product by Name\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySupershop();
                break;
            case 2: {
                int id;
                char name[50];
                float price;
                char quantity[10];

                printf("Enter item ID: ");
                scanf("%d", &id);
                printf("Enter item name: ");
                scanf(" %49[^\n]", name);
                printf("Enter item price: ");
                scanf("%f", &price);
                printf("Enter item quantity (e.g., 10L or 250gm): ");
                scanf(" %9s", quantity);

                addItem(id, name, price, quantity);
                printf("Item added successfully.\n");
                break;
            }
            case 3: {
                int id;
                printf("Enter item ID to delete: ");
                scanf("%d", &id);
                deleteItem(id);
                break;
            }
            case 4: {
                int id;
                printf("Enter item ID to update: ");
                scanf("%d", &id);
                updateItem(id);
                break;
            }
            case 5:
                searchProductByName();
                break;
            case 0:
                printf("Thanks You.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

