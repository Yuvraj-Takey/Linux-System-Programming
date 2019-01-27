/*
 *	a program demonstrates the usage of stat( ) system call, to print different attributes of a file
 * which includes size, inode number, whether it is a regular file or directory etc..
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
	Function			: stat_cmd()
	Description			: This function displays all file information
	Input				: char *
	Return				: nothing

	@author : Yuvraj Takey
*/
 void stat_cmd(char *file)
 {
 	struct stat f_stat;
 	struct tm *time; 
 	int retval = 0;

 	// readed single entry from directory
 	retval = stat(file,&f_stat);
 	if(retval < 0)
 	{
 		perror("stat ");
 		return;
 	}
 	
 	// print the result
 	// get the inode
 	printf("[INODE] : %ld \n",f_stat.st_ino);
 	
 	// print the file type
 	switch((f_stat.st_mode & S_IFMT))
 	{
 		case S_IFSOCK:
 		{
 			printf("[TYPEF] : Socket file\n");
 			break;
 		}
 		case S_IFLNK:
 		{
 			printf("[TYPEF] : Link file\n");
 			break;
 		}
 		case S_IFREG:
 		{
 			printf("[TYPEF] : Regular file\n");
 			break;
 		}
 		case S_IFBLK:
 		{
 			printf("[TYPEF] : Blk_Device file\n");
 			break;
 		}
 		case S_IFDIR:
 		{
 			printf("[TYPEF] : Directory file\n");
 			break;
 		}
 		case S_IFCHR:
 		{
 			printf("[TYPEF] : Char_device file\n");
 			break;
 		}
 		case S_IFIFO:
 		{
 			printf("[TYPEF] : FIFO pipe file\n");
 			break;
 		}
 		default:
 		{
 			printf("[SORRY] : unable to get file type\n");
 			break;
 		}
 	}
 	
 	
 	// print the file permission
 	printf("[PERMF] : ");
 	(f_stat.st_mode & S_IRUSR) ?	printf("r") : printf("-");
 	(f_stat.st_mode & S_IWUSR) ?	printf("w") : printf("-");
 	(f_stat.st_mode & S_IXUSR) ?	printf("x") : printf("-");
 	(f_stat.st_mode & S_IRGRP) ?	printf("r") : printf("-");
 	(f_stat.st_mode & S_IWGRP) ?	printf("w") : printf("-");
 	(f_stat.st_mode & S_IXGRP) ?	printf("x") : printf("-");
 	(f_stat.st_mode & S_IROTH) ?	printf("r") : printf("-");
 	(f_stat.st_mode & S_IWOTH) ?	printf("w") : printf("-");
 	(f_stat.st_mode & S_IXOTH) ?	printf("x \n") : printf("- \n");
 	
 	// get the link count
 	printf("[LINKS] : %ld \n",f_stat.st_nlink);
 		
 	// print the UID and GID name
 	printf("[UIDF_] : %d \n",f_stat.st_uid);
 		
 	// print the UID and GID name
 	printf("[GIDF_] : %d \n",f_stat.st_gid);
 	
 	// print the file size
 	printf("[SIZE_] : %5ld \n",f_stat.st_size);
 		
 	// print the last modification time
 	time = localtime(&f_stat.st_mtime);
 	
 	// print the modification time
 	printf("[TIMEM] : ");
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
 	
 	printf("%d %02d:%d \n",time->tm_mday,time->tm_hour,time->tm_min);	
 	printf("\n");
 }
 
 int main()
 {
 	char accept[MAXCMD] = {"\0"};
 	
 	// accept the input
 	printf("Kindly enter the filename\n");
 	scanf("%[^'\n']s",accept);
 	
 	// calling to function
 	stat_cmd(accept);
 		
 	return 0;
 }
