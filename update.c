#include"main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to update the database by reading from the backup file
int update_database(mnode **hashtable) 
{
    // Check if hash table is empty
    for (int i = 0; i < 27; i++) 
    {
        if (hashtable[i] != NULL) 
        {
            printf("ERROR: Hash table is not empty, unable to update database.\n");
            return FAILURE;
        }
    }

    char backup_file[50];
    
    printf("INFO: Enter the backup file name: ");
    if (scanf("%49s", backup_file) != 1) 
    {
        printf("ERROR: Invalid input for backup file name.\n");
        return FAILURE;
    }

    FILE *fptr = fopen(backup_file, "r");
    if (fptr == NULL) 
    {
        printf("ERROR: Unable to open %s file.\n", backup_file);
        return FAILURE;
    }

    // Check if file has .txt extension
    char *ptr = strstr(backup_file, ".txt");
    if (ptr == NULL) 
    {
        printf("Warning: Invalid extension for file %s. Expected .txt.\n", backup_file);
        fclose(fptr);
        return FAILURE;
    }

    // Check if file is empty
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0) 
    {
        printf("INFO: %s is empty.\n", backup_file);
        fclose(fptr);
        return FAILURE;
    }

    // Reset the file pointer to the beginning
    rewind(fptr);

    // Update the database with the contents of the backup file
    int result = update_backup_entry(fptr, hashtable);
    fclose(fptr);
    return result;
}

// Function to process the backup file and update the hash table
int update_backup_entry(FILE *fptr, mnode **hashtable) 
{
    char str[50];
    int index = 0;
    char word[50];
    int file_count = 0;

    while (fscanf(fptr, "%s", str) != EOF) 
    {
        if (str[0] == '#') 
        {
            // Parse the line
            char *token = strtok(&str[1], ";");
            index = atoi(token);

            token = strtok(NULL, ";");
            strcpy(word, token);

            token = strtok(NULL, ";");
            file_count = atoi(token);

            // Create main node for the word
            mnode *main_ptr = malloc(sizeof(mnode));
            if (main_ptr == NULL) 
            {
                printf("ERROR: Memory allocation failed for main node.\n");
                return FAILURE;
            }

            main_ptr->fcount = file_count;
            strcpy(main_ptr->mword, word);
            main_ptr->link = NULL;
            main_ptr->sublink = NULL;

            // Create sub node for the document information
            snode *sub_ptr = malloc(sizeof(snode));
            if (sub_ptr == NULL) 
            {
                free(main_ptr);
                printf("ERROR: Memory allocation failed for sub node.\n");
                return FAILURE;
            }

            token = strtok(NULL, ";");
            strcpy(sub_ptr->sfname, token);

            token = strtok(NULL, ";");
            sub_ptr->wcount = atoi(token);

            sub_ptr->link = NULL;

            // Link sub node to main node
            main_ptr->sublink = sub_ptr;

            // Insert main node into the hash table at the given index
            if (hashtable[index] == NULL) 
            {
                hashtable[index] = main_ptr;
            } else 
            {
                // If there is a collision, insert at the end of the list
                mnode *temp = hashtable[index];
                while (temp->link != NULL) 
                {
                    temp = temp->link;
                }
                temp->link = main_ptr;
            }
        } else 
        {
            printf("ERROR: File format is invalid.\n");
            return FAILURE;
        }
    }

    printf("INFO: Database is updated successfully.\n");
    return SUCCESS;
}

// Function to clear dynamically allocated memory
void clear_memory(mnode *main_ptr, snode *sub_ptr) 
{
    if (main_ptr != NULL) 
    {
        free(main_ptr);
    }
    if (sub_ptr != NULL)
    {
        free(sub_ptr);
    }
}

// Function to print the contents of the hash table (for debugging)
void print_hash_table(mnode **hashtable) 
{
    printf("\nPrinting Hash Table:\n");
    for (int i = 0; i < 27; i++) 
    {
        if (hashtable[i] != NULL) 
        {
            printf("Index %d:\n", i);
            mnode *main_ptr = hashtable[i];
            while (main_ptr != NULL) 
            {
                printf("  Word: %s (Count: %d)\n", main_ptr->mword, main_ptr->fcount);
                snode *sub_ptr = main_ptr->sublink;
                while (sub_ptr != NULL) 
                {
                    printf("    Document: %s (Count: %d)\n", sub_ptr->sfname, sub_ptr->wcount);
                    sub_ptr = sub_ptr->link;
                }
                main_ptr = main_ptr->link;
            }
        }
    }
}
