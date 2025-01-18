//Name : karabassu sangur
//Date : 20-11-2024

//project:Inverted search (data structure)
/*Project Description: The purpose of storing an index is to optimize speed and performance in finding relevant documents
for a search query. Without an index, the search engine would scan every document in the corpus, which would require
considerable time and computing power.

An inverted index is an index data structure storing a mapping from content, such as words or numbers, to its
locations in a database file, or in a document or a set of documents. The purpose of an inverted index is to allow
fast full text searches, at the cost of increased processing when a document is added to the database. The inverted
file may be the database file itself, rather than its index. It is the most popular data structure used in document
retrieval systems, used on a large scale for example in search engines

--------------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include "main.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
    flist *head = NULL;                //Head to file name list
    mnode *hashtable[27] = {NULL};   //array of pointer of main node data type
    
    if (argc < 2) 
    {
        printf("Please enter the valid file formats!\n");
        printf("Usage: file1.txt file2.txt file3.txt........\n");
        return FAILURE;
    }
    else 
    {
        if (validate(argc, argv, &head) != SUCCESS)         //initially head==NULL
        {
            printf("validation failed\n");
            return FAILURE;
        }
    }
    int choice;
    do 
    {
        printf("1. Create database\n2. Display database\n3. Search database\n4. Save database\n5. Update database\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) 
        {
            case 1:
                // Call create database function 
                if(create_database(&head,hashtable) == SUCCESS)
                {
                    printf("Database for the given file is created successfully! \n");
                }
                else
                {
                    printf("Database is not created! \n");
                }
                break;
            case 2:
                // Call display database fun
                display(hashtable);
                printf("display database success\n");
                break;
            case 3:
                // Call search database fun
                search_database(hashtable);
                printf("search database success\n");
                break;
            case 4:
                // Call save database fun
                save_database(hashtable);
                //printf("database saved success\n");
                break;
            case 5:
                // Call update database function
                update_database(hashtable);
                printf("database updated success\n");
                break;
            case 6:
                printf("Exit\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } 
    while (choice != 6); 
    return 0;
}

