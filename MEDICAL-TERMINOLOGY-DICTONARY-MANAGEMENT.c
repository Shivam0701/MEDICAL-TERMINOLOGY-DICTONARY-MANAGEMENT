#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TERMS 100
// Structure to hold a medical term and its definition
int i,j;
struct Term {
    char name[50];
    char definition[100];
    char subfield[50];
};
// Function to add a new term to the dictionary file
void add_term(struct Term *terms, int *num_terms) {
    // Check if the maximum number of terms has been reached
    if (*num_terms >= MAX_TERMS) {
        printf("Error: Maximum number of terms reached\n");
return; }
    // Get the details of the new term from the user
    printf("Enter the name of the term: ");
    scanf("%s", terms[*num_terms].name);
    printf("Enter the definition of the term: ");
    scanf("%s", terms[*num_terms].definition);
    printf("Enter the subfield of the term: ");
    scanf("%s", terms[*num_terms].subfield);
    // Increment the number of terms
    (*num_terms)++;
    // Write the new term to the dictionary file
    FILE *fp = fopen("dictionary.txt", "a");
    fprintf(fp, "%s,%s,%s\n", terms[*num_terms-1].name,
terms[*num_terms-1].definition, terms[*num_terms-1].subfield);
fclose(fp);
    printf("Term added successfully\n");
}
// Function to display all the terms in alphabetical order
void display_terms(struct Term *terms, int num_terms) {
    // Sort the terms in alphabetical order
    for (i = 0; i < num_terms-1; i++) {
        for (j = i+1; j < num_terms; j++) {
            if (strcmp(terms[i].name, terms[j].name) > 0) {
                struct Term temp = terms[i];
                terms[i] = terms[j];
                terms[j] = temp;
} }
}
    // Display the terms
    printf("Terms in alphabetical order:\n-----------------------------------\n");
    for (i = 0; i < num_terms; i++) {
        printf("%s: %s (%s)\n", terms[i].name, terms[i].definition,
terms[i].subfield);
} }
// Function to update the definition of a term
void update_term(struct Term *terms, int num_terms) {
    // Get the name of the term to update from the user
    char name[50];
    printf("Enter the name of the term to update: ");
    scanf("%s", name);
    // Search for the term in the array
    int index = -1;
    for (i = 0; i < num_terms; i++) {
        if (strcmp(terms[i].name, name) == 0) {
        	 index = i;
        	 break;
        	 } }
    // If the term is found, update its definition
    if (index != -1) {
        printf("Enter the new definition of the term: ");
        scanf("%s", terms[index].definition);
        // Update the term in the dictionary file
        FILE *fp = fopen("dictionary.txt", "w");
        for (i = 0; i < num_terms; i++) {
            fprintf(fp, "%s,%s,%s\n", terms[i].name,
terms[i].definition, terms[i].subfield);
        }
        fclose(fp);
        printf("Term updated successfully\n");
    } else {
        printf("Error: Term not found\n");
    }
}
// Function to search for a term by its name
void search_term(struct Term *terms, int num_terms) {
    // Get the name of the term to search for from the user
    char name[50];
    printf("Enter the name of the term to search for: ");
    scanf("%s", name);
    // Search for the term in the array
    int index = -1;
    for (i = 0; i < num_terms; i++) {
        if (strcmp(terms[i].name, name) == 0) {
            index = i;
break; }
}
    // If the term is found, display its details
    if (index != -1) {
        printf("%s: %s (%s)\n", terms[index].name,
terms[index].definition, terms[index].subfield);
    } else {
        printf("Error: Term not found\n");
    }
}
// Function to delete a term from the dictionary file
void delete_term(struct Term *terms, int *num_terms) {
    // Get the name of the term to delete from the user
    char name[50];
    printf("Enter the name of the term to delete: ");
    scanf("%s", name);
    // Search for the term in the array
    int index = -1;
    for (i = 0; i < *num_terms; i++) {
        if (strcmp(terms[i].name, name) == 0) {
            index = i;
break; }
}
    // If the term is found, delete it from the array and the dictionary

    if (index != -1) {
        // Shift the remaining terms in the array
        for (i = index; i < *num_terms-1; i++) {
            terms[i] = terms[i+1];
        }
        // Decrement the number of terms
        (*num_terms)--;
        // Write the updated terms to the dictionary file
        FILE *fp = fopen("dictionary.txt", "w");
        for (i = 0; i < *num_terms; i++) {
            fprintf(fp, "%s,%s,%s\n", terms[i].name,
            terms[i].definition, terms[i].subfield);
        }
fclose(fp);
        printf("Term deleted successfully\n");
    } else {
        printf("Error: Term not found\n");
    }
}
int main() {
    // Array to hold the terms
    struct Term terms[MAX_TERMS];
    int num_terms = 0;
    // Read the terms from the dictionary file
    FILE *fp = fopen("dictionary.txt", "r");
    if (fp != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), fp) != NULL) {
            char *name = strtok(line, ",");
            char *definition = strtok(NULL, ",");
            char *subfield = strtok(NULL, ",");
            strcpy(terms[num_terms].name, name);
            strcpy(terms[num_terms].definition, definition);
            strcpy(terms[num_terms].subfield, subfield);
            num_terms++;
}
        fclose(fp);
    }
// Menu loop
    int choice;
    do {
        printf("\nMedical Terminology Dictionary Management\n");
        printf("1. Add term to the file\n");
        printf("2. Display all the terms in alphabetical order\n");
        printf("3. Update the definition\n");
        printf("4. Search the term by its name\n");
        printf("5. Delete the record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("-----------------------------------\n");
        switch (choice) {
            case 1:
                add_term(terms, &num_terms);
                break;
            case 2:
                display_terms(terms, num_terms);
                break;
            case 3:
                update_term(terms, num_terms);
                break;
            case 4:
                search_term(terms, num_terms);
                break;
            case 5:
                delete_term(terms, &num_terms);
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Error: Invalid choice\n");
break; }
    } while (choice != 6);
    return 0;
}
