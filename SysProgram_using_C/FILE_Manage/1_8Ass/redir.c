/*
 *	C program that redirects standard output to a file
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 
 #define FILE_PERM	0666
 #define STDOUT		1
 
 int main()
 {
 	int i_fd = 0;
 	
 	// close the output stream
 	close(STDOUT);
 	
 	// open the file for output
 	i_fd = open("output",O_WRONLY);
 	if(i_fd < 0)
 	{
 		// if file is not there, create the file
 		i_fd = open("output",O_WRONLY | O_CREAT,FILE_PERM);
 		if(i_fd < 0)
 		{
 			perror("unable to create the file ");
 		}
 		else
 		{
	 		printf("[DONE] : file is successfully created\n");
 		}
 	}
 	else
 	{
 		printf("[DONE] : file is successfully opened\n");
 	}
 	
 	// printing on standard output	
 	printf("Execution completed\n");
 	
 }
