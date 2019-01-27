/*
 *	a C program for deleting the directory by using rmdir().
 *
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
 #include <stdio.h>
 #include <unistd.h>
 #define MAXDIR		100
 
 int main()
 {
 	int retval = 0;
 	char dir_name[MAXDIR] = {"\n"};
 	
 	printf("kindly enter the name of directory\n");
 	scanf("%[^'\n']",dir_name);
 	
 	//deleting directory
 	retval = rmdir(dir_name);
 	if(retval < 0)
 	{
 		perror("rmdir ");
 	}
 	else
 	{
 		printf("[DONE_] : given directory file is sucessfully removed\n");
 	}
 	
 	return 0;
 }
