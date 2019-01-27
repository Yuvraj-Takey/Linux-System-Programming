/*
 *	Implement ls and ls -l command in linux using directory system calls (opendir, readdir, closedir).
 *
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
 #include <stdio.h>
 #include <dirent.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <string.h>
 #include <time.h>
 #include <pwd.h>
 #include <grp.h>
 
 #define MAXDIR		50
 #define MAXFILE	50
 #define MAXCMD		10
 #define TRUE		1
 #define FALSE		0
 
 /**************************************************************************************************************
	Function			: ls_command()
	Description			: This function implements $ls -l command
	Input				: char *
	Return				: nothing

	@author : Yuvraj Takey
*/
 void ls_command(char *option)
 {
 	char file_name[MAXFILE] = {"\0"};
 	DIR *f_dir = NULL;
 	struct dirent *d_read = NULL;
 	struct stat f_stat;
 	struct tm *time;
 	struct passwd *psd;
 	struct group *gp;
 	int retval = 0;
 	char c_flag = ' ';
 	
 
 	// open the directory file
 	f_dir = opendir(".");
 	if(f_dir == NULL)
 	{
 		perror("issue in openning directory file");
 		return ;
 	}
 	
 	// check for option
 	if(strcmp(option,"-l") != 0)
 	{
 		c_flag = TRUE;
 	}
 	
 	// read the directory till end
 	while((d_read = readdir(f_dir)) != NULL)
 	{
 		if(c_flag == TRUE)
 		{
 			printf(" >  %s\n",d_read -> d_name);
 			continue;
 		}
 		
 		// generate path for stat(combine with directory name)
 		sprintf(file_name,"%s",d_read->d_name);
 	
 		// readed single entry from directory
 		retval = stat(file_name,&f_stat);
 		if(retval < 0)
 		{
 			perror("stat ");
 			break;
 		}
 		
 		// print the result
 		
 		// print the file type
 		switch((f_stat.st_mode & S_IFMT))
 		{
 			case S_IFSOCK:
 			{
 				printf("s");
 				break;
 			}
 			case S_IFLNK:
 			{
 				printf("l");
 				break;
 			}
 			case S_IFREG:
 			{
 				printf("_");
 				break;
 			}
 			case S_IFBLK:
 			{
 				printf("b");
 				break;
 			}
 			case S_IFDIR:
 			{
 				printf("d");
 				break;
 			}
 			case S_IFCHR:
 			{
 				printf("c");
 				break;
 			}
 			case S_IFIFO:
 			{
 				printf("p");
 				break;
 			}
 			default:
 			{
 				printf("[SORRY] : unable to get file type\n");
 				break;
 			}
 		}
 		
 		// print the file permission
 		(f_stat.st_mode & S_IRUSR) ?	printf("r") : printf("-");
 		(f_stat.st_mode & S_IWUSR) ?	printf("w") : printf("-");
 		(f_stat.st_mode & S_IXUSR) ?	printf("x") : printf("-");
 		(f_stat.st_mode & S_IRGRP) ?	printf("r") : printf("-");
 		(f_stat.st_mode & S_IWGRP) ?	printf("w") : printf("-");
 		(f_stat.st_mode & S_IXGRP) ?	printf("x") : printf("-");
 		(f_stat.st_mode & S_IROTH) ?	printf("r") : printf("-");
 		(f_stat.st_mode & S_IWOTH) ?	printf("w") : printf("-");
 		(f_stat.st_mode & S_IXOTH) ?	printf("x ") : printf("- ");
 		
 		// get the link count
 		printf("%ld ",f_stat.st_nlink);
 		
 		// print the UID and GID name
 		psd = getpwuid(f_stat.st_uid);
 		printf("%s ",psd -> pw_name);
 		
 		gp = getgrgid(f_stat.st_gid);
 		printf("%s ",gp -> gr_name);
 	
 		// print the file size
 		printf("%5ld ",f_stat.st_size);
 		
 		// print the last modification time
 		time = localtime(&f_stat.st_mtime);
 		
 		switch(time->tm_mon)
 		{
 			case 0:		printf("Jan ");	break;
 			case 1:		printf("Feb ");	break;
 			case 2:		printf("Mar ");	break;
 			case 3:		printf("Apr ");	break;
 			case 4:		printf("May ");	break;
 			case 5:		printf("Jun ");	break;
 			case 6:		printf("Jul ");	break;
 			case 7:		printf("Aug ");	break;
 			case 8:		printf("Sep ");	break;
 			case 9:		printf("Oct ");	break;
 			case 10:	printf("Nov ");	break;
 			case 11:	printf("Dec ");	break;
 			
 		}
 		printf("%d %02d:%d ",time->tm_mday,time->tm_hour,time->tm_min);
 		
 		// print the file name
 		printf("%s \n",d_read->d_name);
 			
	 		
 	}// end of while

	printf("\n"); 
	
	// close the directory
 	closedir(f_dir);
 
 
 }
 
 int main()
 {
 	char command[MAXCMD] = {"\0"} ,option[MAXCMD] = {"\0"}, accept[MAXCMD] = {"\0"};
 	
 	printf("Enter Your command\n");
 	printf("batch2@dssd-myCode: $ ");
 	scanf("%[^'\n']s",accept);
 	printf("\n");
 	
 	// token
 	sscanf(accept,"%s%s",command,option);

 	// check for correct command
 	if(strcmp(command,"ls") != 0)
 	{
 		printf("[SORRY] : command not found\n");
 		return -1;
 	}
 	
 	// calling to function
 	ls_command(option);
 		
 	return 0;
 }
