/*
 *	a C program which scans the directory and prints the directory listing except regular files and directories. (Prints special files).
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
 
 #define MAXDIR		50
 #define MAXFILE	50
 #define MAXCMD		10
 #define TRUE		1
 #define FALSE		0
 
 /**************************************************************************************************************
	Function			: special_files()
	Description			: This function displays all the special files exist in current directory
	Input				: nothing
	Return				: nothing

	@author : Yuvraj Takey
*/
 void special_files()
 {
 	DIR *f_dir = NULL;
 	struct dirent *d_read = NULL;
 
 	// open the directory file
 	f_dir = opendir(".");
 	if(f_dir == NULL)
 	{
 		perror("issue in openning directory file");
 		return ;
 	}
 	
 	// read the directory till end
 	while((d_read = readdir(f_dir)) != NULL)
 	{
 		// parcing the special files
 		if((d_read -> d_type != DT_REG) && (d_read -> d_type != DT_DIR))
 		{
 			printf(" >  %ld \t %s\n",d_read -> d_ino,d_read -> d_name);
 		}
	 		
 	}// end of while

	printf("\nExecution completed \n"); 
	
	// close the directory
 	closedir(f_dir);
 
 
 }
 
 int main()
 { 	
 	// calling to function
 	special_files();
 		
 	return 0;
 }
