#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for each product in warehouse
struct Product {
    int id;
    char name[50];
    int quantity;
    int ecoFriendly; // 1 = Eco-friendly, 0 = Non-eco
    struct Product *left, *right;
};

// Function to create a new product node
struct Product* createProduct(int id, char name[], int quantity, int ecoFriendly) {
    struct Product* newProduct = (struct Product*) malloc(sizeof(struct Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->quantity = quantity;
    newProduct->ecoFriendly = ecoFriendly;
    newProduct->left = newProduct->right = NULL;
    return newProduct;
}

// Insert a product (BST based on Product ID)
struct Product* insertProduct(struct Product* root, int id, char name[], int quantity, int ecoFriendly) {
    if (root == NULL)
        return createProduct(id, name, quantity, ecoFriendly);
    if (id < root->id)
        root->left = insertProduct(root->left, id, name, quantity, ecoFriendly);
    else if (id > root->id)
        root->right = insertProduct(root->right, id, name, quantity, ecoFriendly);
    else
        printf("Product ID %d already exists!\n", id);
    return root;
}

// Search for a product
struct Product* searchProduct(struct Product* root, int id) {
    if (root == NULL || root->id == id)
        return root;
    if (id < root->id)
        return searchProduct(root->left, id);
    return searchProduct(root->right, id);
}

// Find the minimum node (for deletion)
struct Product* findMin(struct Product* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

// Delete a product
struct Product* deleteProduct(struct Product* root, int id) {
    if (root == NULL) return root;

    if (id < root->id)
        root->left = deleteProduct(root->left, id);
    else if (id > root->id)
        root->right = deleteProduct(root->right, id);
    else {
        if (root->left == NULL) {
            struct Product* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Product* temp = root->left;
            free(root);
            return temp;
        }
        struct Product* temp = findMin(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        root->quantity = temp->quantity;
        root->ecoFriendly = temp->ecoFriendly;
        root->right = deleteProduct(root->right, temp->id);
    }
    return root;
}

// Display all products (inorder = sorted by ID)
void displayProducts(struct Product* root) {
    if (root != NULL) {
        displayProducts(root->left);
        printf("ID: %d | Name: %s | Quantity: %d | Eco-friendly: %s\n",
               root->id, root->name, root->quantity,
               root->ecoFriendly ? "Yes" : "No");
        displayProducts(root->right);
    }
}

// Calculate sustainability score
void sustainabilityReport(struct Product* root, int *total, int *ecoCount) {
    if (root == NULL) return;
    (*total)++;
    if (root->ecoFriendly) (*ecoCount)++;
    sustainabilityReport(root->left, total, ecoCount);
    sustainabilityReport(root->right, total, ecoCount);
}

int main() {
    struct Product* root = NULL;
    int choice, id, quantity, eco;
    char name[50];

    printf("\n=== GreenWarehouse: Responsible Stock Management (SDG 12) ===\n");

    do {
        printf("\nMenu:\n");
        printf("1. Add Product\n");
        printf("2. Search Product\n");
        printf("3. Delete Product\n");
        printf("4. Display All Products\n");
        printf("5. Sustainability Report\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Product ID: ");
                scanf("%d", &id);
                printf("Enter Product Name: ");
                scanf(" %[^\n]", name);
                printf("Enter Quantity: ");
                scanf("%d", &quantity);
                printf("Eco-friendly (1=Yes, 0=No): ");
                scanf("%d", &eco);
                root = insertProduct(root, id, name, quantity, eco);
                break;

            case 2:
                printf("Enter Product ID to search: ");
                scanf("%d", &id);
                struct Product* found;
                found = searchProduct(root, id);
                if (found)
                    printf("Found: %s | Quantity: %d | Eco-friendly: %s\n",
                           found->name, found->quantity,
                           found->ecoFriendly ? "Yes" : "No");
                else
                    printf("Product not found!\n");
                break;

            case 3:
                printf("Enter Product ID to delete: ");
                scanf("%d", &id);
                root = deleteProduct(root, id);
                printf("Product deleted if existed.\n");
                break;

            case 4:
                printf("\n--- Product List (Sorted by ID) ---\n");
                displayProducts(root);
                break;

            case 5: {
                int total = 0, ecoCount = 0;
                sustainabilityReport(root, &total, &ecoCount);
                if (total == 0)
                    printf("No products in stock.\n");
                else {
                    float score = (ecoCount * 100.0) / total;
                    printf("\nTotal Products: %d", total);
                    printf("\nEco-friendly Products: %d", ecoCount);
                    printf("\nSustainability Score: %.2f%%\n", score);
                    if (score >= 70)
                        printf("✅ Great job! Warehouse is sustainable.\n");
                    else
                        printf("⚠ Try to increase eco-friendly products.\n");
                }
                break;
            }

            case 6:
                printf("Exiting program... Thank you!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}


---

🧠 Explanation

Binary Search Tree (BST):
Used to organize products by Product ID for fast search, insertion, and deletion.

Sustainability Score:
Shows how many eco-friendly products are stored → connects with SDG 12.

Key Operations:
insertProduct, deleteProduct, searchProduct, displayProducts, and sustainabilityReport.



---

🧾 Sample Output

=== GreenWarehouse: Responsible Stock Management (SDG 12) ===

Menu:
1. Add Product
2. Search Product
3. Delete Product
4. Display All Products
5. Sustainability Report
6. Exit
Enter choice: 1
Enter Product ID: 101
Enter Product Name: Paper Box
Enter Quantity: 50
Eco-friendly (1=Yes, 0=No): 1

Enter choice: 1
Enter Product ID: 102
Enter Product Name: Plastic Bottle
Enter Quantity: 100
Eco-friendly (1=Yes, 0=No): 0

Enter choice: 4
--- Product List (Sorted by ID) ---
ID: 101 | Name: Paper Box | Quantity: 50 | Eco-friendly: Yes
ID: 102 | Name: Plastic Bottle | Quantity: 100 | Eco-friendly: No

Enter choice: 5
Total Products: 2
Eco-friendly Products: 1
Sustainability Score: 50.00%
⚠ Try to increase eco-friendly products.


---

Would you like me to give a short project report (abstract + objective + output screenshot explanation) for submission along with this code?



