#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validate(int argc, char *argv[], flist **head)  //flist =  stores filename
{
    int i;
    int flag1 = 0;

    for (i = 1; i < argc; i++) 
    { 
        //char *ptr = strstr(argv[i], ".txt");        //ptr stores beginning addre of .txt
        //if (strcmp(ptr, ".txt") != 0)
        //printf("char *ptr is %d\n",*ptr);
        //printf("char *ptr is %s\n",ptr);            //ptr holds ASCII val of begining 1st char
        //if(ptr == NULL) 
        if(strstr(argv[i],".txt")==NULL)             //NULL if not match
        {
            printf("Warning: Invalid Extension for file %s\n", argv[i]);
            continue;                                // to check next eextention if caurent extention does not contains .txt extention
        }   
        // File error handling
        FILE *fptr = fopen(argv[i], "r");             // of ith index named file // checking file exists or not //argv[i] gives file name
        if (fptr == NULL) 
        {
            printf("File %s not exist!\n", argv[i]);    //For non existing file.txt
            continue;
        }
        printf("open sussfully\n");
        // Check for contents of file if file exists
        fseek(fptr, 0, SEEK_END);           //move fptr to end
        if (ftell(fptr) == 0) 
        {
            printf("INFO: %s is Empty!!\n", argv[i]);
            fclose(fptr);
            continue;
        }
        flist *fnew = malloc(sizeof(flist));             //Memory allocation for fnew node
        if (fnew == NULL) 
        {
            printf("Memory allocation failed! \n");
            return FAILURE;
        }
        fnew->link = NULL;
        strcpy(fnew->fstr, argv[i]);      //insertion of 1st command line argument ith fnam linked list
        // If the list is empty
        if (*head == NULL) 
        {
            *head = fnew;                 //Head assigned with fnew node
            printf("INFO: List created for %s\n", argv[i]);             //List is created for Ith File
            flag1 = 1;                                                  //flag one set two 1
            fclose(fptr);
            continue;               // go to
        }
        // Check for duplicates so need to traverse to the list
        flist *temp = *head;
        int flag2 = 0;
        while (temp->link != NULL)          //traverse through the list
        {
            if (strcmp(temp->fstr, argv[i]) == 0)           //  //
            {
                printf("INFO: File %s already exists in the list!\n", argv[i]);
                flag2 = 1;
                break;
            }
            temp = temp->link;
        }
        // Check the last node
        if (strcmp(temp->fstr, argv[i]) == 0) 
        {
            printf("INFO: File %s already exists in the list!\n", argv[i]);
            flag2 = 1;
        }
        if (flag2) 
        {
            printf("Warning: %s duplicate found!!\n", argv[i]);
            free(fnew); // Free allocated memory if duplicate
        } 
        else 
        {
            temp->link = fnew;                              //  //
            printf("List created for %s\n", argv[i]);       
            flag1 = 1;
        }
        fclose(fptr);
    }
    if(flag1)
    {
        return SUCCESS;
    }
    else
    {
        return FAILURE;
    }
}