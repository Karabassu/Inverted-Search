#include"main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to search the database for a specific word
void search_database(mnode **hashtable) 
{
    char word[20];
    int index;
    int flag=0;
    printf("Enter the word to search: ");
    scanf("%s", word);
    if(word[0]>'A' && word[0]<'Z')//////here
    { 
        index= ((word[0]+32) % 97);
        printf("UPPER %d \n",index);
        flag=1;
    }
    else if(flag!=1 && word[0]>'a' && word[0]<'z')
    {
    index = tolower(word[0]) % 97; // Calculate the index for the hash table
    printf("LOWER %d \n",index);
    }
    if (index < 0 || index > 26) 
    {
        printf("DATA_NOT_FOUND\n");
        return; // Invalid index, exit the function
    }
    mnode *mainNode = hashtable[index];
    int fileCount = 0; // To fcount the number of files
    char fileNames[100][20]; // To store file names (assuming a max of 100 files)
    int totalCount = 0; // To count total occurrences of the word

    while (mainNode != NULL) 
    {
        if (strcmp(mainNode->mword, word) == 0) 
        {                                               // Check if the word matches
            snode *subNode = mainNode->sublink;
            while (subNode != NULL) 
            {
                strcpy(fileNames[fileCount], subNode->sfname); // Store the file name
                totalCount += subNode->wcount; // Sum the occurrences
                fileCount++;
                subNode = subNode->link; // Move to the next sub node
            }
            break; // Word found, exit the loop
        }
        mainNode = mainNode->link; // Move to the next main node
    }

    // Check if we found the word
    if (fileCount > 0) 
    {
        printf("The word '%s' is present in '%d' files:\n", word, fileCount);
        for (int i = 0; i < fileCount; i++) {
            printf(" - '%s' for '%d' times\n", fileNames[i], totalCount);
        }
    } 
    else 
    {
        printf("DATA_NOT_FOUND\n");
    }
}