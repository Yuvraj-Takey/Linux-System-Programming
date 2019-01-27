/*
 *	a function that uses the C standard I/O library (stdio) functions getc and putc to copy
 * the input file to the output file one character at a time
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */
 
 #include <stdio.h>
 #include <fcntl.h>
 
 int main(int argc, char **argv)
 {
 	// check for argument count
 	if(argc != 3)
 	{
 		printf("[SORRY] : insufficient argument\n");
 		printf("help : <executable> <input_file> <output_file>\n\n");
 		return -1;
 	}
 	
 	FILE *r_fp = NULL, *w_fp = NULL;
 	int retval = 0;
 	char ch = ' ';
 	
 	// open the first file
 	r_fp = fopen(argv[1],"r");
 	if(r_fp == NULL)
 	{
 		perror("unable open first file ");
 		return -1;
 	}
 	
 	// open the second file
 	w_fp = fopen(argv[2],"w");
 	if(w_fp == NULL)
 	{
 		perror("unable open second file ");
 		return -1;
 	}
 	
 	// perform the operation
 	// iterate till end of file
 	while((ch = getc(r_fp)) != EOF)
 	{
 		// write the data into output file
 		retval = putc(ch,w_fp);
 		if(retval == EOF)
 		{
 			perror("issue while writing in file ");
 		}
 	}
 
 	// close both the files	
 	fclose(r_fp);
 	fclose(w_fp);
 	
 	printf("Execution completed\n\n");	
 	return 0;
 }
 
