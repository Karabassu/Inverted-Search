#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

// Function to create the database from the linked list of filenames
int create_database(flist **head, mnode **hashtable) 
{
    flist *ftemp = *head;
    //traverse through list
    while (ftemp != NULL)
    {
        //fetch file name and open in read mode
        FILE *fptr = fopen(ftemp->fstr, "r");                              //to open file Fetching first file name from flist (Single Linked list) And 1st file name addresses store in fptr
        //check if file exists
        if (fptr == NULL) 
        {
            printf("Could not open file %s for reading.\n", ftemp->fstr);
            ftemp = ftemp->link;                                         // Move to the next file in the flist
            continue;                                                   //skip the rest of the code in the loop and move to the next iteration (while)
        }
        //define a variable
        char word[20];  //for storing Word stored in ->File name Stored in-> F list  

        //fetch the word from file and store it in to the word array
        while (fscanf(fptr, "%s", word) == 1)         // //             // fscanf returns 1, it means one word was successfully reads
        {
            //calculate the index
            int index = tolower(word[0]) % 97;                      //word[0] is the first character of the word

            //insert the word into the hash table
            // Handle non-alphabetic characters
            if (index < 0 || index >= 26) 
            {
                index = 26; // index Special character characters
            }
            //create main node and snode
            mnode *mptr = malloc(sizeof(mnode));            //Memory allocation for main node
            snode *sptr = malloc(sizeof(snode));            //memory allocation power sub node
            
            //check node is created or not
            if (mptr == NULL || sptr == NULL) 
            {
                printf("Memory allocation failed!\n");
                fclose(fptr);
                return FAILURE; // Handle memory allocation failure
            }
            // Initialize the new main node
            create_mnode(mptr, word);        //118   //passing Man no temporary variable and word to create main node
            // Initialize the new sub node
            create_subn(sptr, ftemp->fstr);         //passing Subnode temporary variable and filename to create sub node
            
            // Check if hash table index is empty
            if (hashtable[index] == NULL)
            {
                mptr->sublink = sptr;
                hashtable[index] = mptr; // Insert into the hash table in Respective index
            } 
            else
            {
                //Traverse Through that respective index main node
                mnode *mtemp = hashtable[index];  //temp ptr to traverse
                mnode *mprev = NULL;           //prev temp ptr to traverse
                
                while (mtemp != NULL) 
                {
                    // Check if word matches
                    if (strcmp(mtemp->mword, word) == 0)        //if same word is exist in the main node list traversed through the Snode and update word count
                    {
                        // Traverse sub nodes
                        snode *stemp = mtemp->sublink;          // mtemp->sublink; //
                        snode *sprev = NULL;

                        while (stemp != NULL) 
                        {
                            // Check if file name matches
                            if (strcmp(stemp->sfname, ftemp->fstr) == 0)         //Comparing subnode file name with file name In the Flist
                            {
                                stemp->wcount++;
                                break; // File already counted, break the loop
                            }
                            sprev = stemp;
                            stemp = stemp->link;
                        }
                        
                        // Add new sub node if file not found
                        if (stemp == NULL) 
                        {
                            create_subn(sptr, ftemp->fstr);
                            sprev->link = sptr; // Link the new sub node
                            mtemp->fcount++;
                        }
                        free(mptr); // Free memory since we don't need to add a new main node
                        break;
                    }
                    mprev = mtemp;
                    mtemp = mtemp->link;
                }
                // Add new main node and sub node if word not found
                if (mtemp == NULL) 
                {
                    mptr->sublink = sptr;
                    mptr->link = hashtable[index]; // Link to the existing list
                    hashtable[index] = mptr; // Insert new main node into the hash table
                }
            }
        }
        fclose(fptr); // Close the file after processing
        ftemp = ftemp->link; // Move to the next file in the list
    }
    
    return SUCCESS; // Return success if all files processed
}

// Function to create main node
mnode* create_mnode(mnode *mptr, const char *word)  //51
{
    mptr->fcount = 1;           // Initialize file fcount to 1
    strcpy(mptr->mword, word);  // Copy the word into the node 
    mptr->link = NULL;          // Initialize the link to the next main node
    mptr->sublink = NULL;       // Initialize the link to the sub nodes
    
    return mptr;                // Return the initialized main node to 
}

// Function to create sub node
snode* create_subn(snode *sptr, const char *fname)          //fname receives "ftemp->fstr"
{
    sptr->wcount = 1; // Initialize word wcount to 1
    strcpy(sptr->sfname, fname);

    sptr->link = NULL; // Initialize the link to the next sub node

    return sptr; // Return the initialized sub node
}
