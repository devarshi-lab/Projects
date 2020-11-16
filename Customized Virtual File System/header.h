#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<time.h>
#include<iostream>

//maximum file we can create
#define MAXFILES 100

//maximum filesize if file
#define FILESIZE 1024

//permissions of file
#define READ 4
#define WRITE 2

//to store file type
#define REGULAR 1
#define SPECIAL 2

//to change offset
#define START 0
#define CURRENT 1
#define END 2

//structures which are being used in project declared here
typedef struct SuperBlock
{
	int TotalInodes;
	int FreeInode;
}SUPERBLOCK;

typedef struct inode
{
	char File_name[50];
	int Inode_number;
	int File_Size;
	int File_Type;
	int ActualFileSize;
	int Link_Count;
	int Reference_Count;
	int Permission;
	char birth[30];
	char last_accessed[30];
	char last_modified[30];

	char *Buffer;
	struct inode* next;
}iNODE,*piNODE;

typedef struct FileTable
{
	int ReadOffset;
	int WriteOffset;
	int count;
	piNODE ptr;
	int Mode;
}FILETABLE,*PFILETTABLE;

typedef struct ufdt
{
	PFILETTABLE ufdtArr[MAXFILES];
}UFDT;

UFDT UFDT_Obj;
SUPERBLOCK Super_obj;

piNODE Head = NULL;
time_t givetime = time(NULL);//to access time throughout the project.

//all the functions which are used in project are declared here
void CreateUFDT();
void CreateDILB();
void CreateSuperBlock();
void SetEnvironment();
void DisplayHelp();
void DisplayManpage();
int GetFDFromName(char*);
piNODE GetInode(char*);
bool ChkFile(char*);
int create_file(char*,int);
int open_file(char*,int);
int close_file(char*);
void close_all();
int stat_file(char*);
int fstat_file(int);
void ls_file(int);
int read_file(char*,int);
int write_into_file(char*);
int lseek_file(char*,int,char*);
int truncate_file(char*,int);
int cat_file(char*);
void BackupData();
void RestoreData();