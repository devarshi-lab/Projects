#include"helper.cpp"	//including helper.cpp which contains all function realted to project

int main()
{
	//variable declarations
	char str[80];
	int count = 0,ret=0,fd=0;
	char command[5][80],arr[1024];

	printf("Customized Virtual File System\n");
	SetEnvironment();

	while(1)
	{
		printf("Devarshi VFS:~$  ");
		scanf(" %[^'\n']s",str);


		//to seperate out commands or to tokenize the command.
		count = sscanf(str,"%s %s %s %s %s",command[0],command[1],command[2],command[3],command[4]);

		if(count==1)
		{
			if((strcasecmp(command[0],"help"))==0)
			{
				DisplayHelp();
				continue;
			}
			else if((strcasecmp(command[0],"exit"))==0)
			{
				BackupData();
				printf("Thank You!!!\n");
				break;
			}
			else if((strcasecmp(command[0],"clear"))==0)
			{
				system("clear");
				continue;
			}
			else if((strcasecmp(command[0],"ls"))==0)
			{
				ls_file(1);
				continue;
			}
			else if((strcasecmp(command[0],"closeall"))==0)
			{
				close_all();
				continue;
			}
			else if((strcasecmp(command[0],"man"))==0)
			{
				printf("missing parameter : man command_name\n");
				continue;
			}
			else
			{
				printf("error : command not found\n");
				printf("type \"help\" to know about commands\n");
				continue;
			}
		}
		else if(count==2)
		{
			if(strcasecmp(command[0],"man")==0)
			{
				DisplayManpage(command[1]);
				continue;
			}
			else if(strcasecmp(command[0],"cat")==0)
			{
				ret = cat_file(command[1]);
				if(ret!=0)
				{
					printf("Unable to close file\n");
				}
			}
			else if(strcasecmp(command[0],"ls")==0)
			{
				if(strcasecmp(command[1],"-i")==0)
				{
					ls_file(0);
				}
				else if(strcasecmp(command[1],"fd")==0)
				{
					ls_file(2);
				}
				continue;
			}
			else if((strcasecmp(command[0],"stat"))==0)
			{
				ret = stat_file(command[1]);
				if(ret == -1)
				{
					printf("error : incorrect parameters\n");
				}
				else if(ret == -2)
				{
					printf("error : there is no such file\n");
				}
				continue;
			}
			else if((strcasecmp(command[0],"fstat"))==0)
			{
				ret = fstat_file(atoi(command[1]));
				if(ret == -1)
				{
					printf("error : incorrect parameters\n");
				}
				else if(ret == -2)
				{
					printf("error : invalid file descriptor\n");
				}
				continue;
			}
			else if((strcasecmp(command[0],"close"))==0)
			{
				ret = close_file(command[1]);
				if(ret == 0)
				{
					printf("All file descriptor related to file '%s' are closed\n",command[1]);
				}
				else if(ret == -2)
				{
					printf("Invalid file name or file does not exist\n");
				}
				else if(ret == -3)
				{
					printf("File was not opened\n");
				}
				else
				{
					printf("Unable to close the file\n");
				}
				continue;
			}
			else if((strcasecmp(command[0],"delete"))==0)
			{
				ret = delete_file(command[1]);
				if(ret == 0)
				{
					printf("File deleted\n");
				}
				else if(ret == -2)
				{
					printf("File not found\n");
				}
				else
				{
					printf("Unable to delete the file\n");
				}
				continue;
			}
			else if((strcasecmp(command[0],"write"))==0)
			{
				char data[1024] = {'\0'};
				printf("Enter the data U want to write : \n");
				scanf(" %[^'\n']s",data);
				ret = write_into_file(command[1],data,strlen(data));
				if(ret>0)
				{
					printf("%d bytes gets written into file\n",ret);
				}
				else if(ret == -1)
				{
					printf("Invalid parameters\n");
				}
				else if(ret == -2)
				{
					printf("Invalid file name or File does not exist\n");
				}
				else if(ret == -3)
				{
					printf("There is no permission to write into file or try opening file in write mode\n");
				}
				else if(ret == -4)
				{
					printf("File size exceeded\n");
				}
				else if(ret == -5)
				{
					printf("First open the file to write data\n");
				}
				else
				{
					printf("Unable to write in the file\n");
				}
				continue;
			}
			else if((strcasecmp(command[0],"read"))==0)
			{
				char data[1024]={'\0'};
				ret = read_file(command[1],data,1024);
				if(ret == -1)
			 	{
			 		printf("Invalid parameters\n");
			 	}
			 	else if(ret == -2)
			 	{
			 		printf("Invalid File name or File does not exist\n");
			 	}
			 	else if(ret == -3)
			 	{
			 		printf("There is no read permission\n");
			 	}
			 	else if(ret == -4)
			 	{
			 		printf("offset is at end of the file\nPlease change offset using 'lseek' to read file\n");
			 	}
			 	else if(ret == -5)
				{
					printf("First open the file to read data\n");
				}
			 	else
			 	{
			 		printf("\n-----------------------------------------\n");
			 		printf("%s\n",data);
			 		printf("\n-----------------------------------------\n");
			 	}
			 	continue;
			}
			else
			{
				printf("command not found\n");
				printf("type \"help\" to know about commands\n");
				continue;
			}	
		}
		else if(count==3)
		{
			if(strcmp(command[0],"create") == 0)
			 {
			 	int mode = 0;
			 	if(strcasecmp(command[2],"r")==0 || (atoi(command[2])==4))
			 	{
			 		mode = 4;
			 	}
			 	else if(strcasecmp(command[2],"w")==0 || (atoi(command[2])==2))
			 	{
			 		mode = 2;
			 	}
			 	else if(strcasecmp(command[2],"rw")==0 || (atoi(command[2])==6))
			 	{
			 		mode = 6;
			 	}
			 	else
			 	{
			 		printf("error : invalid permission\n");
			 		continue;
			 	}
				 ret = create_file(command[1],mode);
				 if(ret >= 0)
				 {
				 	printf("File is successfully created with file descriptor : %d\n",ret);
				 }
				 else if(ret == -1)
				 {
				 	printf("ERROR : Incorrect parameters\n");
				 }
				 else if(ret == -2)
				 {
				 	printf("ERROR : There is no inodes\n");
				 }
				 else if(ret == -3)
				 {
				 	printf("ERROR : File already exists\n");
				 }
				 else if(ret == -4)
				 {
				 	printf("ERROR : Memory allocation failure\n");
				 }
				 continue;
			 }
			 else if(strcmp(command[0],"open") == 0)
			 {
			 	int mode = 0;
			 	if((strcasecmp(command[2],"r")==0) || (atoi(command[2])==4))
			 	{
			 		mode = 4;
			 	}
			 	else if((strcasecmp(command[2],"w")==0) || (atoi(command[2])==2))
			 	{
			 		mode = 2;
			 	}
			 	else if((strcasecmp(command[2],"rw")==0) || (atoi(command[2])==6))
			 	{
			 		mode = 6;
			 	}
			 	else
			 	{
			 		printf("invalid mode");
			 		continue;
			 	}
			 	ret = open_file(command[1],mode);
			 	if(ret>0)
			 	{
			 		printf("File successfully opened with file descriptor %d\n",ret);
			 	}
			 	else if(ret == -1)
			 	{
			 		printf("Invalid parameters\n");
			 	}
			 	else if(ret == -2)
			 	{
			 		printf("File does not exists\n");
			 	}
			 	else if(ret == -3)
			 	{
			 		printf("Permission error\n");
			 	}
			 	continue;
			 }
			 else if(strcmp(command[0],"read") == 0)
			 {
			 	char *data=(char *)malloc(atoi(command[2]));
			 	ret = read_file(command[1],data,atoi(command[2]));
			 	if(ret == -1)
			 	{
			 		printf("Invalid parameters\n");
			 	}
			 	else if(ret == -2)
			 	{
			 		printf("Invalid File name : File does not exist\n");
			 	}
			 	else if(ret == -3)
			 	{
			 		printf("There is no read permission\n");
			 	}
			 	else
			 	{
			 		printf("\n-----------------------------------------\n");
			 		printf("%s\n",data);
			 	}
			 	continue;
			 }
			 else if((strcasecmp(command[0],"truncate"))==0)
			{
				ret = truncate_file(command[1],atoi(command[2]));
				if(ret == 0)
				{
					printf("size truncated successfully\n");
				}
				else if(ret == -1)
				{
					printf("Invalid parameter\n");
				}
				else if(ret == -2)
				{
					printf("File size exceeds\n");
				}
				else if(ret == -3)
				{
					printf("Invalid file name or file does not exist\n");
				}
				else if(ret == -4)
				{
					printf("first open file to truncate file\n");
				}
				else if(ret == -5)
				{
					printf("unable to truncate file because of unknown error\n");
				}
				continue;
			}
			 else
			 {
				 printf("\nERROR : Command not found !!!\n");
				 printf("type \"help\" to know about commands\n");
				 continue;
			 }
			
		}
		else if(count==4)
		{
			if((strcasecmp(command[0],"lseek"))==0)
			{
				ret = lseek_file(command[1],atoi(command[2]),command[3]);
				if(ret==0)
				{
					
				}
				else if(ret == -1)
				{
					printf("Invalid parameters\n");
				}
				else if(ret == -2)
				{
					printf("Invalid file name or file does not exist\n");
				}
				else if(ret == -3)
				{
					printf("open the file to change the offset\n");
				}
				else if(ret == -4)
				{
					printf("offset exceeds file size\n");
				}
				else if(ret == -5)
				{
					printf("error : bad command or flag\n");
					printf("type \"help\" to know more about command\n");
				}
			}
			else
			{
				printf("Command not found\n");
			}
			continue;
		}
		else
		{
			printf("ERROR : Bad command or file name\n");
			printf("type \"help\" to know about commands\n");
			continue;
		}
	}

	return 0;
}