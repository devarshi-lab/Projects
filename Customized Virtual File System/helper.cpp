#include"header.h"

//initializing a file descriptor array
void CreateUFDT()
{
	int i = 0;
	for(i = 0;i<MAXFILES;i++)
	{
		UFDT_Obj.ufdtArr[i]=NULL;
	}
}

//creating empty Data Inode List Block
void CreateDILB()
{
	int i = 1;
	piNODE newn = NULL;
	piNODE temp = NULL;

	while(i <= MAXFILES)
	{
		//allcating space for DILB
		newn = (piNODE)malloc(sizeof(iNODE));
		newn->Inode_number=i;
		newn->File_Size=FILESIZE;
		newn->File_Type=0;
		newn->ActualFileSize=0;
		newn->Link_Count=0;
		newn->Reference_Count=0;
		newn->Permission=0;
	
		newn->Buffer=NULL;
		newn->next = NULL;

		if(Head == NULL)
		{
			Head = newn;
			temp = Head;
		}
		else
		{
			temp->next = newn;
			temp = temp->next;
		}

		i++;
	}

	printf("DILB created Successfully\n");
}

//initializing superblock which contains information of free inodes and total inodes.
void CreateSuperBlock()
{
	Super_obj.TotalInodes = MAXFILES;
	Super_obj.FreeInode = MAXFILES;

	printf("Super Block created successfully\n");
}

//setting all virtual environment
//calling functions which we need to establish a virtual setup
void SetEnvironment()
{
	CreateDILB();
	CreateSuperBlock();
	CreateUFDT();
	RestoreData();
	printf("Environment for the virtual file system is set...\n");
}

//To display the use every command.
void DisplayHelp()
{
	printf("\n----------------------------------------------------\n");
	printf("open : It is used to open the file\n");
	printf("close : It is used to close the file\n");
	printf("closeall : It is used to close all opened files\n");
	printf("read : It is used to read the file\n");
	printf("write : It is used to write the file\n");
	printf("delete : It is used to delete the file\n");
	printf("stat : It is used to display information the file\n");
	printf("fstat : It is used to display information of opened the file\n");
	printf("ls : To list out all files present in that directory\n");
	printf("lseek : Read the data where starting point of reading data is depends on user.\n");
	printf("clear : To clear console\n");
	printf("truncate : To shrink or extend the file\n");
	printf("cat : To display the data of file without openeing it\n");
	printf("exit : To exit the application\n");
	printf("-----------------------------------------------------------\n");
	printf("to know more about command type : 'man command_name'\n");
	printf("-----------------------------------------------------------\n");
}

//to display detailed information about every command
void DisplayManpage(char *str)
{
	if(str==NULL)
	{
		return;
	}
	if(strcasecmp(str,"open")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\topen - open the file"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\topen file_name mode"
				"\n\n"
				"DESCRIPTION\n"
				"\t\topen the existing file which is specified by user.\n" 
			   	"\t\tmode - \t"
			   	"1.\tr or 4 - open file in read mode.\n"
			   	"\t\t\t2.\tw or 2 - open file in write mode\n"
			   	"\t\t\t3.\trw or 6 - open file in read & write both mode"
				"\n\n"
				"RETURN VALUE\n"
				"\t\ton success returned file descriptor, on failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"close")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tclose- close the file"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tclose file_name"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tcloses the all file_descriptor pointing to file which is specified by user.so it may reused."
				"\n\n"
				"RETURN VALUE\n"
				"\t\ton failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"read")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tread - read from a file name"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\t1.\tread file_name\n"
			   	"\t\t2.\tread file_name no_of_bytes"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tread attempts to read up to count bytes from file descriptor fd into the buffer starting at buf."
				"\n\t\tif u did not specify the no of bytes you want to read then it will read the whole file from current offset."
				"\n\n"
				"RETURN VALUE\n"
				"\t\tOn success, the number of bytes read is returned, on failure error name gets displayed appropriately\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"write")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\twrite - write from a file_name"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\twrite file_name"
				"\n\n"
				"DESCRIPTION\n"
				"\t\twrite attempts to write up to count bytes from file name in the file."
				"\n\n"
				"RETURN VALUE\n"
				"\t\tOn success, the number of bytes written is returned, and the file position is advanced by this number and on failure errorname gets display.\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"ls")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tls - displays list"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\t1.\tls\n"
			   	"\t\t2.\tls -i\n"
			   	"\t\t3.\tls fd"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tls displays the list of files present in directory\n"
				"\t\tls -i displays the list of file with their inode number\n"
				"\t\tls fd display the list of files opened with their file descriptor\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"stat")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tstat - information from a file_name"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tstat file_name"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tstat command display the all information related to that file."
				"\n\n"
				"RETURN VALUE\n"
				"\t\tOn success, display information, on failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"fstat")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tfstat - information from a file descriptor"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tfstat file_descriptor"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tfstat command display the all information related to that file descriptor."
				"\n\n"
				"RETURN VALUE\n"
				"\t\tOn success, display information, on failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"truncate")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\ttruncate - shrink or extend the size of a file to the specified size"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\ttruncate file_name size"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tIf  a  Actual File Size is larger than the specified size, the extra data is lost.\n"
				"\t\tIf a Actual File Size is shorter, it is extended and the extended part (hole) reads as zero bytes."
				"\n\n"
				"RETURN VALUE\n"
				"\t\tOn success display success, on failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"create")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tcreate - creates the file"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tcreate file_name permission"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tcreate the new file.\n" 
			   	"\t\tpermssion - \t"
			   	"1.\tr or 4 - gives file only read permission to the file.\n"
			   	"\t\t\t\t2.\tw or 2 - gives only write permission to the file.\n"
			   	"\t\t\t\t3.\trw or 6 - gives read and write both permission to the file."
				"\n\n"
				"RETURN VALUE\n"
				"\t\ton success returned file descriptor, on failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"closeall")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tcloseall - closes all file_descriptor"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tcloseall"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tcloseall closes the all the file_descriptor pointing to any file, so it may be reused."
				"\n\n"
				"RETURN VALUE\n"
				"\t\tOn success display success, on failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"lseek")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tlseek - reposition read/write file offset"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tlseek file_name offset flag"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tlseek repositions the file offset of the open file description associated with the file name\n" 
                "\t\tto the argument offset according to the directive flag as follows:\n"
			   	"\t\tflag \t"
			   	"1.\tstart - The file offset is set to offset bytes.\n"
			   	"\t\t\t2.\tcurrent - The file offset is set to its current location plus offset bytes.\n"
			   	"\t\t\t3.\tend - The file offset is set to the size of the file plus offset bytes.\n"
			   	"\t\t\tlseek() allows the file offset to be set beyond the end of the file and creates hole and file size changes."
				"\n\n"
				"RETURN VALUE\n"
				"\t\ton failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"delete")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tdelete - delete the file"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tdelete file_name"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tdelete command the delete the file specified by user." 
				"\n\n"
				"RETURN VALUE\n"
				"\t\ton failure display error\n");
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"exit")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\texit - terminate the application"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\texit"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tclose the application\n"); 
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"cat")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tcat - display the file data"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tcat File_name"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tdisplay the data of file without openeing the file\n"); 
		printf("\n----------------------------------------------------\n");
	}
	else if(strcasecmp(str,"man")==0)
	{
		printf("\n----------------------------------------------------\n");
		printf(	"NAME\n"
       		   	"\t\tman - an interface to the application reference manuals"
       		   	"\n\n"
			   	"SYNOPSIS\n"
			   	"\t\tman command_name"
				"\n\n"
				"DESCRIPTION\n"
				"\t\tman is the application's manual pager.  Each page argument given to man is the name of a command.\n"
				"\t\tThe manual page associated with each of these arguments is then found and displayed. \n"); 
		printf("\n----------------------------------------------------\n");
	}
	else
	{
		printf("error : man page not found for entry %s\n",str);
	}
}

//this is to provide file descriptor using filename.
int GetFDFromName(char *name)
{
	if(name==NULL)
	{
		return -1;
	}

	int i=0;
	for(i=0;i<MAXFILES;i++)
	{
		if((UFDT_Obj.ufdtArr[i]!=NULL) && (strcasecmp(UFDT_Obj.ufdtArr[i]->ptr->File_name,name)==0))
		{
			break;
		}
	}

	return i;
}

//this returns address of file name.
piNODE GetInode(char *name)
{
	piNODE temp = Head;

	while(temp!=NULL)
	{
		if((temp->File_Type!=0) && (strcasecmp(temp->File_name,name)==0))
		{
			break;
		}

		temp = temp->next;
	}

	return temp;
}

//this is to check that file is present in our DILB or not.
bool ChkFile(char *name)
{
	piNODE temp = Head;

	while(temp != NULL)
	{
		if(temp->File_Type!=0)
		{
			if(strcasecmp(temp->File_name,name)==0)
			{
				break;
			}
		}
		temp=temp->next;
	}

	if(temp==NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//this creates the file.
int create_file(char *str,int permission)
{
	bool bret = false;

	//checking user has entered correct permission or not.
	if((str==NULL) || ((permission!=READ) && (permission!=WRITE) && (permission!=READ+WRITE)))
	{
		return -1;
	}

	//to check if there are freeinode or not
	if(Super_obj.FreeInode==0)
	{
		return -2;
	}

	int i = 0;

	//to know where we can allocate the file descriptor.
	for(i=0;i<MAXFILES;i++)
	{
		if(UFDT_Obj.ufdtArr[i]==NULL)
		{
			break;
		}
	}

	//if there ufdt are overflowed.
	if(i==MAXFILES)
	{
		return -4;
	}

	bret = ChkFile(str);
	//to check file is present or not
	if(bret == true)
	{
		return -3;
	}

	//allocating memory for FILETABLE
	UFDT_Obj.ufdtArr[i]=(PFILETTABLE)malloc(sizeof(FILETABLE));
	UFDT_Obj.ufdtArr[i]->ReadOffset=0;
	UFDT_Obj.ufdtArr[i]->WriteOffset=0;
	UFDT_Obj.ufdtArr[i]->count=1;
	UFDT_Obj.ufdtArr[i]->Mode=permission;

	piNODE temp = Head;

	//cheching free inode.
	while(temp!=NULL)
	{
		if(temp->File_Type==0)
		{
			break;
		}
		temp=temp->next;
	}

	givetime = time(NULL);							//to access current system time.
	UFDT_Obj.ufdtArr[i]->ptr=temp;
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->File_name,str);
	UFDT_Obj.ufdtArr[i]->ptr->File_Type=REGULAR;
	UFDT_Obj.ufdtArr[i]->ptr->Permission=permission;
	UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize=0;
	UFDT_Obj.ufdtArr[i]->ptr->Link_Count=0;
	UFDT_Obj.ufdtArr[i]->ptr->Reference_Count=0;
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->birth,ctime(&givetime));
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->last_accessed,ctime(&givetime));
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->last_modified,ctime(&givetime));  

	UFDT_Obj.ufdtArr[i]->ptr->Buffer=(char *)malloc(sizeof(FILESIZE)); //allocating memory to buffer.

	Super_obj.FreeInode--;	//decreasing free inode.

	return (i+1);

}

//to list out all present files.
void ls_file(int i)
{
	piNODE temp = Head;



	if(i==0)	//ls  -i : prints all files with their inode numbers
	{
		while(temp!=NULL)
		{
			if(temp->File_Type!=0)
			{
				printf("%d\t%s\n",temp->Inode_number,temp->File_name);
			}
			temp=temp->next;
		}
	}
	else if(i==1)		//ls : prints only file name
	{
		while(temp!=NULL)
		{
			if(temp->File_Type!=0)
			{
				printf("%s\n",temp->File_name);
			}
			temp=temp->next;
		}
	}
	else if(i==2)	//ls fd : prints all file descriptor which are being used
	{
		for(int k=0;k<MAXFILES;k++)
		{
			if(UFDT_Obj.ufdtArr[k]!= NULL)
			{
				printf("%d\t%s\n",(k+1),UFDT_Obj.ufdtArr[k]->ptr->File_name);
			}
		}
	}
}

//deletes the file
int delete_file(char *name)
{
	if(name==NULL)
	{
		return -1;
	}

	bool bret=true;

	bret=ChkFile(name);

	if(bret == false)
	{
		return -2;
	}

	int i = 0;

	i = GetFDFromName(name);
	if(i!=MAXFILES)	//if file is opened or in process.
	{
		strcpy(UFDT_Obj.ufdtArr[i]->ptr->File_name,"");
		UFDT_Obj.ufdtArr[i]->ptr->File_Type=0;
		UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize=0;
		UFDT_Obj.ufdtArr[i]->ptr->Link_Count=0;
		UFDT_Obj.ufdtArr[i]->ptr->Reference_Count=0;

		free(UFDT_Obj.ufdtArr[i]->ptr->Buffer);
		UFDT_Obj.ufdtArr[i]->ptr->Buffer = NULL;
		free(UFDT_Obj.ufdtArr[i]);

		UFDT_Obj.ufdtArr[i] = NULL;
	}
	else	//if file is not opened.
	{
		piNODE temp = GetInode(name);
		strcpy(temp->File_name,"");
		temp->File_Type=0;
		temp->ActualFileSize=0;
		temp->Link_Count=0;
		temp->Reference_Count=0;

		free(temp->Buffer);
		temp->Buffer = NULL;

	}

	Super_obj.FreeInode++;//increasing free inode.

	return 0;
}

//opens the file
int open_file(char *name,int mode)
{
	if(name==NULL)
	{
		return -1;
	}
	bool bret = true;
	bret = ChkFile(name);
	if(bret==false)
	{
		return -2;
	}

	piNODE temp = GetInode(name);

	if((temp->Permission != mode) && (temp->Permission != 6))
	{
		return -3;
	}

	int i = 0;
	//checking for empty fd.
	while(i<MAXFILES)
	{
		if(UFDT_Obj.ufdtArr[i]==NULL)
		{
			break;
		}
		i++;
	}

	givetime = time(NULL);
	UFDT_Obj.ufdtArr[i]=(PFILETTABLE)malloc(sizeof(FILETABLE));//allocating filetable to fd.
	UFDT_Obj.ufdtArr[i]->count=1;
	UFDT_Obj.ufdtArr[i]->Mode=mode;
	UFDT_Obj.ufdtArr[i]->ReadOffset=0;
	UFDT_Obj.ufdtArr[i]->WriteOffset=0;
	UFDT_Obj.ufdtArr[i]->ptr=temp;
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->last_accessed,ctime(&givetime));
	temp->Reference_Count++;	//file is opened so reference count gets increased

	return i+1;;
}

//closes the opened file.
int close_file(char *name)
{
	if(name==NULL)
	{
		return -1;
	}

	bool bret = true;
	bret = ChkFile(name);
	if(bret==false)
	{
		return -2;
	}

	int i = 0,flag = -1;
	for(i=0;i<MAXFILES;i++)
	{
		if((UFDT_Obj.ufdtArr[i]!=NULL) && (strcmp(UFDT_Obj.ufdtArr[i]->ptr->File_name,name)==0))
		{
			if(UFDT_Obj.ufdtArr[i]->ptr->Reference_Count!=0)//if file is opened and reference count is > 0.
			{
				(UFDT_Obj.ufdtArr[i]->ptr->Reference_Count)--;
				UFDT_Obj.ufdtArr[i]=NULL;
			}
			else	//file is just created and reference count is 0
			{
				UFDT_Obj.ufdtArr[i]=NULL;
			}
			flag++; 
		}
	}

	if(flag!=(-1))//if file successfully closed.
	{
		return 0;
	}
	return -3;	//if file is just in DILB but not opened.
}

//closes all the opened file.
//frees the ufdt
void close_all()
{
	int i = 0;
	piNODE temp = Head;
	while(UFDT_Obj.ufdtArr[i]!=NULL)
	{
		free(UFDT_Obj.ufdtArr[i]);
		UFDT_Obj.ufdtArr[i]=NULL;
		i++;
	}
}

//gives all information of file.
int stat_file(char *name)
{
	if(name==NULL)
	{
		return -1;
	}

	bool bret = true;
	bret = ChkFile(name);

	if(bret==false)
	{
		return -2;
	}

	piNODE temp = GetInode(name);

	printf("\n---------------------------------------------------------\n");
	printf("inode number : %d\n",temp->Inode_number);
	printf("File name : %s\n",temp->File_name);
	printf("File size : %d\n",temp->File_Size);
	if(temp->File_Type==1)
	{
		printf("File type : REGULAR\n");
	}
	else
	{
		printf("File type : SPECIAL\n");
	}
	printf("Actual file size : %d\n",temp->ActualFileSize);
	printf("Link count : %d\n",temp->Link_Count);
	printf("Reference_Count : %d\n",temp->Reference_Count);
	if(temp->Permission==4)
	{
		printf("Permission : Read\n");
	}
	else if(temp->Permission==2)
	{
		printf("Permission : Write\n");
	}
	else if(temp->Permission==6)
	{
		printf("Permission : Read&Write\n");
	}
	std::cout<<"Created on       :"<<temp->birth;
	std::cout<<"Last accessed on :"<<temp->last_accessed;
	std::cout<<"Last modified on :"<<temp->last_modified<<"\n";

	printf("\n---------------------------------------------------------\n");
	
	return 0;
}

//gives information of file using fd.
int fstat_file(int fd)
{
	if(fd==0)
	{
		return -1;
	}
	if((UFDT_Obj.ufdtArr[fd-1])==NULL)
	{
		return -2;
	}

	printf("\n---------------------------------------------------------\n");
	printf("File descriptor : %d\n",fd);
	printf("inode number : %d\n",UFDT_Obj.ufdtArr[fd-1]->ptr->Inode_number);
	printf("File name : %s\n",UFDT_Obj.ufdtArr[fd-1]->ptr->File_name);
	printf("File size : %d\n",UFDT_Obj.ufdtArr[fd-1]->ptr->File_Size);
	if(UFDT_Obj.ufdtArr[fd-1]->ptr->File_Type==1)
	{
		printf("File type : REGULAR\n");
	}
	else
	{
		printf("File type : SPECIAL\n");
	}
	printf("Actual file size : %d\n",UFDT_Obj.ufdtArr[fd-1]->ptr->ActualFileSize);
	printf("Link count : %d\n",UFDT_Obj.ufdtArr[fd-1]->ptr->Link_Count);
	printf("Reference_Count : %d\n",UFDT_Obj.ufdtArr[fd-1]->ptr->Reference_Count);
	if(UFDT_Obj.ufdtArr[fd-1]->ptr->Permission==4)
	{
		printf("Permission : Read\n");
	}
	else if(UFDT_Obj.ufdtArr[fd-1]->ptr->Permission==2)
	{
		printf("Permission : Write\n");
	}
	else if(UFDT_Obj.ufdtArr[fd-1]->ptr->Permission==6)
	{
		printf("Permission : Read&Write\n");
	}

	std::cout<<"Created on       :"<<UFDT_Obj.ufdtArr[fd-1]->ptr->birth;
	std::cout<<"Last accessed on :"<<UFDT_Obj.ufdtArr[fd-1]->ptr->last_accessed;
	std::cout<<"Last modified on :"<<UFDT_Obj.ufdtArr[fd-1]->ptr->last_modified<<"\n";

	printf("---------------------------------------------\n");

	printf("information from file table\n");
	if(UFDT_Obj.ufdtArr[fd-1]->Mode==4)
	{
		printf("Mode : Read\n");
	}
	else if(UFDT_Obj.ufdtArr[fd-1]->Mode==2)
	{
		printf("Mode : Write\n");
	}
	else if(UFDT_Obj.ufdtArr[fd-1]->Mode==6)
	{
		printf("Mode : Read&Write\n");
	}
	printf("ReadOffset : %d\n",UFDT_Obj.ufdtArr[fd-1]->ReadOffset);
	printf("WriteOffset : %d\n",UFDT_Obj.ufdtArr[fd-1]->WriteOffset);
	printf("address of IIT : %d\n",(*(UFDT_Obj.ufdtArr[fd-1]->ptr)));
	printf("-------------------------------------------------------\n");

	return 0;
}

//read the data from file.
int read_file(char *name,char *data,int length)
{
	if(name == NULL)
	{
		return -1;
	}

	bool bret = true;
	bret = ChkFile(name);
	if(bret==false)
	{
		return -2;
	}

	int i = 0;
	i = GetFDFromName(name);

	if(i==MAXFILES)	//if file is not opened.
	{
		return -5;
	}

	if((UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)==(UFDT_Obj.ufdtArr[i]->ReadOffset))//if read offset is at end of the file.
	{
		return -4;
	}
	if((UFDT_Obj.ufdtArr[i]->ptr->Permission)==WRITE)	//if file only has write permission.
	{
		return -3;
	}
	
	int size_t=UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize;
	if(length>size_t)	//if length entered by user is greater than actual file size.
	{
		strncpy(data,((UFDT_Obj.ufdtArr[i]->ReadOffset)+(UFDT_Obj.ufdtArr[i]->ptr->Buffer)),((size_t)-(UFDT_Obj.ufdtArr[i]->ReadOffset)));
	}
	else
	{
		strncpy(data,((UFDT_Obj.ufdtArr[i]->ReadOffset)+(UFDT_Obj.ufdtArr[i]->ptr->Buffer)),length);
		data[length]='\0';
	}

	return 0;
}

//writes data into file.
int write_into_file(char *name,char *arr,int size)
{
	if(name==NULL)
	{
		return -1;
	}

	bool bret = true;
	bret = ChkFile(name);
	if(bret==false)
	{
		return -2;
	}

	int i = 0;
	i = GetFDFromName(name);

	if(i==MAXFILES)//if file is not opened.
	{
		return -5;
	}

	if(UFDT_Obj.ufdtArr[i]->ptr->Permission==READ)//if file has only read permission
	{
		return -3;
	}
	
	if((UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize==FILESIZE) || ((UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize+size)>FILESIZE))//if file size is exceeding.
	{
		return -4;
	}

	givetime = time(NULL);
	strncpy(((UFDT_Obj.ufdtArr[i]->ptr->Buffer)+(UFDT_Obj.ufdtArr[i]->WriteOffset)),arr,size);
	UFDT_Obj.ufdtArr[i]->ptr->Buffer[(UFDT_Obj.ufdtArr[i]->WriteOffset)+size] = '\0';	//so garbage value should not store
	if((UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)<(strlen(UFDT_Obj.ufdtArr[i]->ptr->Buffer)))
	{
		UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize = strlen(UFDT_Obj.ufdtArr[i]->ptr->Buffer);
	}
	UFDT_Obj.ufdtArr[i]->WriteOffset=strlen(UFDT_Obj.ufdtArr[i]->ptr->Buffer);//changing write offset.
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->last_modified,ctime(&givetime));

	return size;
}

//to channge file offset.
int lseek_file(char *name,int offset,char *flag)
{
	if(name==NULL)
	{
		return -1;
	}
	bool bret = true;
	bret = ChkFile(name);
	if(bret==false)
	{
		return -2;
	}

	int i = 0;
	i = GetFDFromName(name);

	if(i==MAXFILES)//if file is not opened.
	{
		return -3;
	}

	if(UFDT_Obj.ufdtArr[i]->Mode == READ || UFDT_Obj.ufdtArr[i]->Mode == READ+WRITE)//it changes only read offset.
	{
		if(strcasecmp(flag,"start")==0)//setting offset from starting of file.
		{

			if((offset>(UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)) || offset<0)
			{
				return -4;
			}
			UFDT_Obj.ufdtArr[i]->ReadOffset=offset;
		}
		else if(strcasecmp(flag,"current")==0)//setting to current_offset + offset
		{
			if(((UFDT_Obj.ufdtArr[i]->ReadOffset+offset)>(UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)) || ((UFDT_Obj.ufdtArr[i]->ReadOffset+offset)<0))
			{
				return -4;
			}
			UFDT_Obj.ufdtArr[i]->ReadOffset += offset;
		}
		else if(strcasecmp(flag,"end")==0)//setting to offset from end of file.
		{

			if(((UFDT_Obj.ufdtArr[i]->ReadOffset+offset)>(UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)) || ((UFDT_Obj.ufdtArr[i]->ReadOffset+offset)<0))
			{
				return -4;
			}
			UFDT_Obj.ufdtArr[i]->ReadOffset = (UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)+offset;
		}
		else
		{	
			return -5;
		}
	}
	else if(UFDT_Obj.ufdtArr[i]->Mode == WRITE)//changes write offset if opened in write mode
	{
		if(strcasecmp(flag,"start")==0)//setting offset from start
		{
			if(offset>FILESIZE)
			{
				return -4;
			}
			UFDT_Obj.ufdtArr[i]->WriteOffset=offset;
			if(UFDT_Obj.ufdtArr[i]->WriteOffset>UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)
			{
				UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize=UFDT_Obj.ufdtArr[i]->WriteOffset;
			}
		}
		else if(strcasecmp(flag,"current")==0)//setting offset from current offset
		{
			if((offset>FILESIZE) || ((offset+(UFDT_Obj.ufdtArr[i]->WriteOffset))>FILESIZE) || ((offset+(UFDT_Obj.ufdtArr[i]->WriteOffset))<0))
			{
				return -4;
			}
			UFDT_Obj.ufdtArr[i]->WriteOffset += offset;
			if(UFDT_Obj.ufdtArr[i]->WriteOffset>UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)
			{
				UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize=UFDT_Obj.ufdtArr[i]->WriteOffset;
			}

		}
		else if(strcasecmp(flag,"end")==0)//setting to offset from end of file.
		{
			UFDT_Obj.ufdtArr[i]->WriteOffset=strlen(UFDT_Obj.ufdtArr[i]->ptr->Buffer);
			if((offset>FILESIZE) || ((offset+(UFDT_Obj.ufdtArr[i]->WriteOffset))>FILESIZE) || ((offset+(UFDT_Obj.ufdtArr[i]->WriteOffset))<0))
			{
				return -4;
			}
			UFDT_Obj.ufdtArr[i]->WriteOffset += offset;
			if(UFDT_Obj.ufdtArr[i]->WriteOffset>UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)
			{
				for(int j =(UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize);j<UFDT_Obj.ufdtArr[i]->WriteOffset;j++)
				{
					UFDT_Obj.ufdtArr[i]->ptr->Buffer[j]=' ';
				}
				UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize=UFDT_Obj.ufdtArr[i]->WriteOffset;
			}
		}
		else
		{	
			return -5;
		}
	}

	givetime = time(NULL);
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->last_modified,ctime(&givetime)); 
	return 0;
}

//shrinks or extend file size.
int truncate_file(char *name,int size)
{
	if(name == NULL)
	{
		return -1;
	}
	if(size>FILESIZE)
	{
		return -2;
	}

	bool bret = true;
	bret = ChkFile(name);
	if(bret==false)
	{
		return -3;
	}

	int i = 0;
	i = GetFDFromName(name);

	if(i==MAXFILES)
	{
		return -4;
	}

	if(size==0)//if size is 0
	{
		UFDT_Obj.ufdtArr[i]->ptr->Buffer=NULL;
		UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize=0;
	}
	else if(size>0 && size<UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize)//if size is less than Actual file size.
	{
		UFDT_Obj.ufdtArr[i]->ptr->Buffer[size]='\0';
		UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize=size;
		UFDT_Obj.ufdtArr[i]->WriteOffset=size;
	}
	else if((size>UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize) && ((size+(UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize))<FILESIZE))//if size is greater than actual file size and less than filesize then creates hole
	{
		UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize = size;
	}
	else if(size==(UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize))//if size is equal to actual file size.
	{
		return 0;
	}
	else if((size+(UFDT_Obj.ufdtArr[i]->ptr->ActualFileSize))>FILESIZE)//if size is greater than filesize.
	{
		return -2;
	}
	else
	{
		return -5;
	}

	givetime = time(NULL);
	strcpy(UFDT_Obj.ufdtArr[i]->ptr->last_modified,ctime(&givetime));//changes modified time
	return 0;
}

//read data from file without opening it.
int cat_file(char *name)
{
	if(name==NULL)
	{
		return -1;
	}

	bool bret = true;
	bret = ChkFile(name);
	if(bret==false)
	{
		return -1;
	}

	piNODE temp = GetInode(name);

	if(temp->ActualFileSize==0 || (strlen(temp->Buffer)==0))//if file is empty.
	{
		printf("File is empty\n");
		return 0;
	}

	if(temp->Buffer!=NULL)
		printf("%s\n",temp->Buffer);
	
	return 0;
}

//backing up data
void BackupData()
{
	int fd = 0;
	int goes = 0;
	piNODE temp = Head;
	fd = open("backup.txt",O_WRONLY | O_APPEND);

	while(temp!=NULL)
	{
		if(temp->File_Type!=0)
		{
			goes = 1;
			write(fd,temp,sizeof(iNODE));	//write inode into file
			write(fd,temp->Buffer,1024);	//write data of Buffer of that inode into file
		}
		temp = temp->next;
	}

	if(goes!=1)//if there is no data gets written
	{
		ftruncate(fd,0);
	}

	close(fd);
}

//restoring the data.
void RestoreData()
{
	int fd= 0,ret = 0;
	char Data[1024]={'\0'};
	iNODE iobj;
	piNODE temp = Head;

	fd = open("backup.txt",O_RDONLY);
	if(fd == -1)
	{
		return;
	}

	int size = lseek(fd,0,SEEK_END);
	if(size==0)
	{
		return;
	}

	lseek(fd,0,SEEK_SET);

	while((ret = read(fd,&iobj,sizeof(iobj)))!=0)	//read inode information from file.
	{

		temp->Inode_number=iobj.Inode_number;
		strcpy(temp->File_name,iobj.File_name);
		temp->File_Size=iobj.File_Size;
		temp->File_Type=iobj.File_Type;
		temp->ActualFileSize=iobj.ActualFileSize;
		temp->Link_Count=iobj.Link_Count;
		temp->Reference_Count=iobj.Reference_Count;
		temp->Permission=iobj.Permission;
		strcpy(temp->birth,iobj.birth);
		strcpy(temp->last_accessed,iobj.last_accessed);
		strcpy(temp->last_modified,iobj.last_modified);

		temp->Buffer = (char *)malloc(1024);	//allocating space to buffer to copy the data further.

		read(fd,Data,1024);						//reading data from file.
		if(strlen(Data)==temp->ActualFileSize)
		{
			memcpy(temp->Buffer,Data,1024);
		}

		Super_obj.FreeInode--;
		temp = temp->next;
	}

	close(fd);
	printf("Data Restored\n");
}