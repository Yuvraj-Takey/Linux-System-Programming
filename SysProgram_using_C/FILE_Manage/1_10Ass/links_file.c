/*
 *	a C program for creating symbolic link and hard links to a file and identify the difference between them.
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
 #include <stdio.h>
 #include <unistd.h>
 #include <errno.h>
 #define MAXFILE	250
 
 int main()
 {
 	int retval = 0;
 	char file[MAXFILE] = {"\0"};
 	
 	// accept the input
	printf("Kindly enter the name of existing file in CWD\n"); 
	scanf("%[^'\n']",file);
	
	// create the symbolic link file
	retval = symlink(file,"symlink_file");
	if(retval < 0)
	{
		perror("symlink ");
	}
	else
	{
		printf("[DONE_] : symbolic link is successfully created with name 'symlink_file'\n");
	}
	
	// create hard link file
	retval = link(file,"hrdlink_file");
	if(retval < 0)
	{
		perror("link ");
	}
	else
	{
		printf("[DONE_] : hard link is successfully created with name 'hrdlink_file'\n");
	}
	
	return 0;
	
 }
