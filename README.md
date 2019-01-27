# Linux-System-Programming

System programming starts and ends with system calls. System calls (often shortened to syscalls) are function invocations made from
user space—your text editor, favorite game, and so on—into the kernel (the core internals of the system) in order to request
some service or resource from the operating system. System calls range from the familiar, such as read() and write(), to the exotic, such as get_thread_area() and set_tid_address().

### How to Invoking system calls ?
It is not possible to directly link user-space applications with kernel space. For reasons of security and reliability, user-space applications must not be allowed to directly
execute kernel code or manipulate kernel data. Instead, the kernel must provide a mechanism by which a user-space application can “signal” the kernel that it wishes to invoke a system call.
The application tells the kernel which system call to execute and with what parameters via machine registers.

### what are the Libraries required ?
The C library (libc) is at the heart of Unix applications. Even when you’re programming in another language, the C library is most likely in play, wrapped by the higher-level libraries,
providing core services, and facilitating system call invocation. On modern Linux systems, the C library is provided by GNU libc, abbreviated glibc, and pronounced gee-lib-see or, less commonly, glib-see.
The GNU C library provides more than its name suggests. In addition to implementing the standard C library, glibc provides wrappers for system calls, threading support, and basic application facilities.

To date, C++ has taken a backseat to C in system programming. Historically, Linux developers favored C over C++: core libraries, daemons, utilities, and of course the Linux kernel are all written in C.
Where the ascendancy of C++ as a “better C” is all but universal in most non-Linux environments, in Linux C++ plays second fiddle to C.
Nonetheless, you can replace “C” with “C++” without issue. Indeed, C++ is an excellent alternative to C, suitable for any system programming task: C++ code can link to C code, invoke Linux system calls, and utilize glibc.
