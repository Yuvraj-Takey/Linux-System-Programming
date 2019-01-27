/*
 *	a program using file system calls that determines the length of a file without using a loop in the code
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
  #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 
 int main(int argc, char **argv)
 {
 	// check for argument count
 	if(argc != 2)
 	{
 		printf("[SORRY] : insufficient argument\n");
 		printf("help : <executable> <input_file>\n\n");
 		return -1;
 	}
 	
 	int r_fd = 0, retval = 0, offset = 0;
 	
 	// open the file
 	r_fd = open(argv[1],O_RDONLY);
 	if(r_fd < 0)
 	{
		perror("unable to open the file");
		return -1;
	}

	// get the last offset of file
	offset = lseek(r_fd, 0 , SEEK_END);
	if(offset < 0)
	{
		perror("unable to seek in file");
	}
	else
	{
		printf("[DONE_] : The length of file is %d\n", offset);
	}
	
	
 	return 0;
 }
