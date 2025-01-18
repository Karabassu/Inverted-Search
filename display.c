#include"main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void display(mnode **hashtable)
{
    if(*hashtable == NULL)
    {
        printf("\n  empty Hashtable \n");                         
    }
    printf("\n\n");
    printf("|INDEX|\tWORD|\t\tFILE_COUNT|\tFILE_NAME|\tWORD_COUNT|\n");
    printf("\n");
    for (int i = 0; i <= 26; i++) 
    {
        mnode *mtemp = hashtable[i];                              //mnode *mtemp= ith index of the array
        //if(hashtable[i]!=NULL)  // no need
        while (mtemp != NULL)
        {   
            printf("%-6d %-20s %-12d", i, mtemp->mword, mtemp->fcount);
            snode *stemp = mtemp->sublink;                  //      //
            while (stemp != NULL) 
            {
                printf("%-19s %-13d", stemp->sfname, stemp->wcount);
                stemp = stemp->link;
            }
            printf("\n");
            mtemp = mtemp->link;
        }
    }
    printf("\n");
}