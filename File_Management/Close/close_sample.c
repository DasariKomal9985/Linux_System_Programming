/*
close() is the system call used to close an open file descriptor.

int close(int fd);


Return value:

0 → success
-1 → failure (and sets errno)


⭐ Why do we need close()?

Every time you call:
open()
read()
write()
accept()
socket()

Linux creates a file descriptor.
You MUST call close() to:
✔ free kernel resources
✔ release locks
✔ flush buffers
✔ avoid running out of file descriptors
✔ avoid memory/resource leaks



🚀 What exactly happens when you call close()

1. You call close(fd) from your program
close(fd);
This calls the GLIBC wrapper.






2. GLIBC wrapper prepares registers

rax = 3 (system call number for close)
rdi = fd


syscall
CPU switches to kernel mode.







3. Kernel finds the correct system call handler

sys_close(fd)




4. Kernel validates fd

Checks:

Is fd valid for this process?
Is it open?
Does it correspond to a file, socket, pipe, etc.?






5. Kernel decreases the reference count

Inside kernel, each open file has a reference count.

fork() duplicates fd
Threads may share fd
dup() creates duplicates






6. Kernel calls correct close() method

Depending on what fd represents, kernel calls:
file → file_operations->release()
socket → sock_close()
pipe → pipe_release()
terminal → tty_release()
This cleans up resources.






7. Kernel removes fd from the process table

Your PCB (Process Control Block) contains an FD table.
fd_table[fd] = NULL;
Now that fd number is freed and can be reused.




8. Returns back to user space

return 0 → success
return -1 → error
GLIBC sets errno if needed.






int fd = open("file.txt", O_RDONLY);
if (fd < 0) return 1;

char buf[100];
int n = read(fd, buf, 100);

write(1, buf, n);

close(fd);   // important







⭐ What happens if you don’t call close() ?

Linux will:

Leak kernel memory
Leave file locks hanging
Prevent other processes from opening the file exclusively
Keep data unflushed
Eventually cause:  Too many open files

("file descriptor exhaustion")
In embedded systems, this is deadly.






⭐ What happens if you close the same fd twice?


close(fd);
close(fd);


Second close → EBADF (Bad file descriptor)


*/








#include <unistd.h>
#include <fcntl.h>

int main() {
    char buf[200];

    // Open file with: read + write + create + truncate
    int fd = open("final_demo.txt",
                  O_RDWR | O_CREAT | O_TRUNC | O_APPEND,
                  0644);
    if (fd < 0) return 1;

    // First write (goes to end because of O_APPEND)
    write(fd, "First line (after truncate)\n", 29);

    // Append another line
    write(fd, "Second line (append mode)\n", 27);

    // Move file offset to beginning for reading
    lseek(fd, 0, SEEK_SET);

    int n = read(fd, buf, sizeof(buf));
    write(1, buf, n);

    close(fd);
}
