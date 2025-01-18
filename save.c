#include"main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void save_database(mnode **hashtable)
{
    //read filename from user
    char filename[100];
    printf("Enter filename to save database: ");
    scanf("%s", filename);
    if(strstr(filename,".txt")==NULL)
    {
        printf("invalid file file name should contain .txt extention \n");
        return;     // stop next exicution 
    }

    //check file already exists or not if exist then ask user to enter diffrent filename
    FILE *filenameexists = fopen(filename, "r");
    if (filenameexists != NULL)
    {
        //if File name already exists file opens successfully Which indicates that duplicate file is exists Ask the user to enter the different file name
        printf("File already exists. Please enter a different filename.\n");
        // close the file
        fclose(filenameexists);
        return;
    }
    //open backup.txt file in write mode to write
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    { 
        printf("Could not open file %s for writing ", filename);
        return;
    }
    printf("open file successful write into the file\n");
    //open the all existing file in the hashtable and write the file content  to the user entered filename
    for(int i=0;i<26;i++)
    {
        //int count=0;
        //printf("for loop entered");
        if(hashtable[i]!=NULL)
        {
            //traverse through the mainnode
            mnode *mtemp=hashtable[i];
            while (mtemp!=NULL)                  //main node
            {
                    //int count = 0;
                    fprintf(fp, "#%d;%s;%d",tolower(mtemp->mword[0]) % 97, mtemp->mword, mtemp->fcount);

                    snode *stemp= mtemp->sublink;
                    while (stemp!=NULL)        //stemp!=NULL
                    {
                        fprintf(fp,";%s;%d;#",stemp->sfname, stemp->wcount);
                        stemp=stemp->link;
                    }
                    fprintf(fp,"\n");
                mtemp=mtemp->link;
            }
        }
    }
    fclose(fp); // Close the file after writing
    printf("Database saved successfully to %s.\n", filename);
}
