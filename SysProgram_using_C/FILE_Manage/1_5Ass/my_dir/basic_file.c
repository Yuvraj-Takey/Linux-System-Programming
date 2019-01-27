/*
 *	a C program in Linux that opens an input file for reading and an output file for writing.
 * The names of the files should be command line arguments.
 *
 *	@DSSD	- Yuvraj Takey
 */
 
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 
 int main(int argc, char **argv)
 {
 	// check for argument count
 	if(argc != 3)
 	{
 		printf("[SORRY] : insufficient argument\n");
 		printf("help : <executable> <input_file> <output_file>\n\n");
 		return -1;
 	}
 	
 	int r_fd = 0, w_fd = 0, retval = 0;
 	
 	// open the first file
 	r_fd = open(argv[1],O_RDONLY);
 	if(r_fd < 0)
 	{
 		printf("[INFO_] : file not found, trying to create the file\n");
 		
 		// create the input file
 		r_fd = open(argv[1], O_RDONLY | O_CREAT);
 		if(r_fd < 0)
 		{
 			perror("can not create ");
 		}
 		else
 		{
 			printf("[DONE_] : input file is created successfully\n");
 		}
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
 	
 	// close the opened files
 	close(r_fd);
 	close(w_fd);
 
 	printf("\n");
 	return 0;
 }
