/*  

fstat() gets file information using an already opened file descriptor (fd).

❓ Why to use fstat()?

Because sometimes you don’t have the filename, only file descriptor.

Examples:

stdin (fd = 0)
pipe
socket
file after open()

int fd = open(...);
fstat(fd, &info);



📌 Where fstat() is used?

Checking if fd is file, pipe, socket
Getting file size after open()
Debugging file descriptors
Networking programs
Shells and system tools

*/