# Assignment on System Calls and files

1. Write a C program in Linux that opens an input file for reading and an
output file for writing. The names of the files should be command line
arguments.

2. Implement a function that uses the C standard I/O library (stdio)
functions getc and putc to copy the input file to the output file one
character at a time

3. Implement a C program that uses lseek system call to copy the contents
of one file into another file at position 100.

4. Develop a program using file system calls (open, create, read, link, write,
lseek, close, unlink) that determines the length of a file without using a
loop in the code

5. Implement ls and ls -l command in linux using directory system calls
(opendir, readdir, closedir).

6. Implement cat and mv commands in linux using system calls.

7. Write a C program to list for every file in a directory, its inode number
and file name.

8. Write a C program that redirects standard output to a file. Hint: ls > file

9. Write a C program which scans the directory and prints the directory
listing except regular files and directories. (Prints special files).

10. Write a C program for creating symbolic link and hard links to a file and
identify the difference between them.

11. Write a C program for deleting the directory by using rmdir().

12. Write a program to demonstrate the usage of dup2 system call. If we
read through the duplicated file descriptor, we will continue from the
previous update in file pointer.

13. Write a program demonstrates the usage of fstat system call to
retrieve the details of file.

14. Write a program demonstrates the usage of stat( ) system call, to
print different attributes of a file which includes size, inode number,
whether it is a regular file or directory etc..
