//karabassu sangur
//inverted search
#ifndef MAIN_H
#define MAIN_H

#define SUCCESS 0
#define FAILURE -1
#define DATA_NOT_FOUND  
#define DATA_FOUND 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//linked list structure
typedef struct fnode 
{
    char fstr[30];
    struct fnode *link; 
}flist;

//snode structure
typedef struct snode
{
    int wcount;
    char sfname[20];
    struct snode *link;      //sub node2
}snode;

//main nodestructure for 
typedef struct mainnode
{
    int fcount;
    char mword[20];
    snode *sublink;
    struct mainnode *link;  //main node3
}mnode;

// Function prototypes
int validate(int argc, char *argv[], flist **head);
// Add other function prototypes as needed
mnode* create_mnode(mnode *mptr, const char *word);
snode* create_subn(snode *sptr, const char *fname);
int create_database(flist **head, mnode **hashtable);
void display(mnode **hashtable);
void search_database(mnode **hashtable);
void save_database(mnode **hashtable);
int update_database(mnode **hashtable);
int update_backup_entry(FILE *fptr, mnode **hashtable);
void clear_memory(mnode *main_ptr, snode *sub_ptr);
void print_hash_table(mnode **hashtable);

#endif 
