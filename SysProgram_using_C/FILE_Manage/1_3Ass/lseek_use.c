/*
 *	a C program that uses lseek system call to copy the contents of one file into another file at position 100.
 *
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>

 #define POSITION	100
 #define MAXBUFF	255
 
 int main(int argc, char **argv)
 {
 	// check for argument count
 	if(argc != 3)
 	{
 		printf("[SORRY] : insufficient argument\n");
 		printf("help : <executable> <input_file> <output_file>\n\n");
 		return -1;
 	}
 	
 	int r_fd = 0, w_fd = 0, retval = 0, offset = 0;
 	char buff[MAXBUFF] = {"\0"};
 	
 	// open the first file
 	r_fd = open(argv[1],O_RDONLY);
 	if(r_fd < 0)
 	{
		perror("can not open ");
 	}
 	else
 	{
 		printf("[DONE_] : input file is opened successfully\n");
 	}

	// open the second file
 	w_fd = open(argv[2],O_WRONLY);
 	if(w_fd < 0)
 	{
 		printf("[INFO_] : file not found, trying to create the file\n");
 		
 		// create the output file
 		w_fd = open(argv[2], O_WRONLY | O_CREAT);
 		if(w_fd < 0)
 		{
 			perror("can not create ");
 		}
 		else
 		{
 			printf("[DONE_] : output file is created successfully\n");
 		}
 	}
 	else
 	{
 		printf("[DONE_] : output file is opened successfully\n");
 	}
 
 	// get the 100th offset by using lseek function
 	offset = lseek(r_fd,POSITION,SEEK_CUR);
 	
 	// iterate while till end of the file
 	while((retval = read(r_fd, buff, MAXBUFF)) != 0)
 	{
 		// write the data into new file
 		retval = write(w_fd, buff, retval);
 		if(retval < 0)
 		{
 			perror("unable to write");
 		}
 	}
 	
 	// close the opened files
 	close(r_fd);
 	close(w_fd);
 
 	printf("\n");
 	return 0;
 }
