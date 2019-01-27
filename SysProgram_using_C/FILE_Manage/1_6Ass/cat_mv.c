/*
 * Implement cat and mv commands in linux using system calls.
 *
 *	@Author	- Yuvraj Takey
 *	@Title	- Linux_System_Programming
 */

 #include <stdio.h>
 #include <string.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>
 
 #define MAXBUF	255
 #define STDIN	1
 
 /**************************************************************************************************************
	Function			: cat_command()
	Description			: This function implements $cat command
	Input				: char*
	Return				: nothing

	@author : Yuvraj Takey
*/
 void cat_command(char *file_name)
 {
 	char buff[MAXBUF] = {"\0"};
 	int i_fd = 0, retval = 0;
 	
 	// open the given file
 	i_fd = open(file_name,O_RDONLY);
 	if(i_fd < 0)
 	{
 		perror("unable to open the file ");
 		return ;
 	}
 	
 	// iterate till file not reached till end
 	while((retval = read(i_fd,buff,MAXBUF)) != 0)
 	{
 		retval = write(STDIN,buff,retval);
 		if(retval < 0)
 		{
 			perror("issue while writing on screen ");
 		}
 	}
 }
 
 /**************************************************************************************************************
	Function			: mv_command()
	Description			: This function implements $mv command
	Input				: char*, char*
	Return				: nothing

	@author : Yuvraj Takey
*/
 void mv_command(char *old, char *new)
 {
 	int retval = 0;
 	
 	// making hardlink to old file with new file
 	retval = link(old,new);
 	if(retval < 0)
 	{
 		perror("issue while linking ");
 		return;
 	}
 	
 	// removing the old file
 	retval = unlink(old);
 	if(retval < 0)
 	{
 		perror("issue while unlinking old file ");
 	}
 	else
 	{
 		printf("[DONE_] : operation is successfully completed\n");
 	}
 }
 
 
 int main(int argc, char **argv)
 {
 	// check for argument count
 	if((argc < 3) && (argc > 4))
 	{
 		printf("[SORRY] : insufficient argument\n");
 		printf("help : <executable> <command> <input_file> <output_file>,if any\n\n");
 		return -1;
 	}
 	
 	// checking for cat command
 	if(strcmp(argv[1],"cat") == 0)
 	{
 		cat_command(argv[2]);
 	
 	}// checking for mv command
 	else if(strcmp(argv[1],"mv") == 0)
 	{
 		mv_command(argv[2],argv[3]);
 	}
 	else
 	{
 		printf("[SORRY] : command not found\n");
 	} 	
 	
 	return 0;
}
