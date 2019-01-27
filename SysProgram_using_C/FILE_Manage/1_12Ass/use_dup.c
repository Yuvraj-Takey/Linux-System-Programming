/*
 *	a program to demonstrate the usage of dup2 system call. If we read through the duplicated file descriptor,
 * we will continue from the previous update in file pointer.
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
 #include <stdio.h>
 #include <fcntl.h>
 #include <unistd.h>
 #include <string.h>
 
 #define MAXFILE	100
 #define MAXBUFF	20
 
 int main()
 {
 	char file_name[MAXFILE] = {"\0"}, buff[MAXBUFF] = {"\0"};
 	int fd = 0, d_fd = 0, retval = 0;
 	
 	printf("Kindly enter the file name\n");
 	scanf("%[^'\n']",file_name);
 	
 	//open the file
 	fd = open(file_name,O_RDONLY);
 	if(fd < 0)
 	{
 		perror("unable to open the file ");
 	}
 	
 	// using dup2 system call
 	retval = dup2(fd,d_fd);
 	if(retval < 0)
 	{
 		perror("issue in dup2 ");
 	}
 	
 	// read the file using duplicated file descripter
 	retval = read(d_fd,buff,MAXBUFF);
 	if(retval < 0)
 	{
 		perror("read using dup2 ");
 	}
 	else
 	{
 		printf("[DUP2] : [%s]\n",buff);
 	}
 	
 	// flush the buffer
 	memset(buff,0,MAXBUFF);
 	
 	// read using previous descripter
 	retval = read(fd,buff,MAXBUFF);
 	if(retval < 0)
 	{
 		perror("read using normal ");
 	}
 	else
 	{
 		printf("[NORM] : [%s]\n",buff);
 	}
 	
 	return 0;
 }
