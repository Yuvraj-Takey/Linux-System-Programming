/*
 *	a program demonstrates the usage of fstat system call to retrieve the details of file.
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <time.h>
 #include <fcntl.h>
 
 #define MAXNAME	100
 
 /**************************************************************************************************************
	Function			: file_Info()
	Description			: This function displays the file information
	Input				: int
	Return				: nothing

	@author : Yuvraj Takey
*/
void file_Info(int fd)
{
	// check for bad descripter
	if(fd < 0)
	{
		return;
	}
	
	int retval = 0;
	struct stat buff;
	
	// get the file info
	retval = fstat(fd,&buff);
	if(retval < 0)
	{
		perror("fstat ");
		return ;
	}
	
	// display the file info
	printf("[INODE] : %ld\n", buff.st_ino);
	printf("[HARDL] : %ld\n", buff.st_nlink);
	printf("[UIDF_] : %d\n", buff.st_uid);
	printf("[GIDF_] : %d\n", buff.st_gid);
	printf("[SIZET] : %d\n", buff.st_gid);
	printf("[BLOCK] : %ld\n", buff.st_blocks);
	
	// get the time
	printf("[LASTA] : %s", ctime(&buff.st_atime));
	printf("[LASTM] : %s", ctime(&buff.st_mtime));
	printf("[LASTI] : %s", ctime(&buff.st_ctime));
	
}
 
 int main()
 {
 	int i_fd = 0;
 	char f_name[MAXNAME] = {"\0"};
 	
 	// accept the input
 	printf("Kindly enter the name of file\n");
 	scanf("%[^'\n']",f_name);
 	
 	// open the file
 	i_fd = open(f_name,O_RDONLY);
 	if(i_fd < 0)
 	{
 		perror("unable to open the file ");
 		return -1;
 	}
 	
 	// calling to function
 	file_Info(i_fd);
 	
 	return 0;
 }
