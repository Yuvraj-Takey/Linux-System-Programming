/*
 *	a C program to list for every file in a directory, its inode numberand file name
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
	Function			: ls_command()
	Description			: This function implements $ls -ai1 command
	Input				: nothing
	Return				: nothing

	@author : Yuvraj Takey
*/
 void ls_command()
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
 		printf(" >  %ld \t %s\n",d_read -> d_ino,d_read -> d_name);
	 		
 	}// end of while

	printf("\n"); 
	
	// close the directory
 	closedir(f_dir);
 
 
 }
 
 int main()
 { 	
 	// calling to function
 	ls_command();
 		
 	return 0;
 }
