#include<unistd.h>
int main()
{
        write(1,"hello komal",12);
}


/*

write() is a Linux system call used to send data from your process to a file, device, pipe, socket, terminal, etc.

ssize_t write(int fd, const void *buf, size_t count);

Parameters

fd → File descriptor
buf → Pointer to memory where your data is store
count → Number of bytes to write


Return value
>= 0 → Number of bytes actually written
-1 → Error, and errno is set







🚀 What Happens When You Call write()
1. User Program Calls the GLIBC Wrapper
write(1, "Hello", 5);                       It isn’t calling the kernel directly.
It calls the glibc wrapper function:

ssize_t write(int fd, const void *buf, size_t count)
{
    // prepares registers
    // triggers syscall instruction
}

GLIBC job:
Validate arguments
Set the correct system call number
Execute syscall instruction




2. Registers Are Loaded
| Register | Meaning                            |
| -------- | ---------------------------------- |
| `rax`    | System call number (`1` for write) |
| `rdi`    | File descriptor                    |
| `rsi`    | Buffer address                     |
| `rdx`    | Count                              |

rax = 1      // write syscall number
rdi = fd
rsi = buf
rdx = count






3. CPU Enters Kernel Mode (Privilege Level 0)
syscall

This instruction:

Switches CPU from user mode → kernel mode
Jumps into Linux syscall entry point
Saves user registers
Changes stack to kernel stack




4. Kernel Finds the Write Handler

sys_call_table[1] → sys_write()


asmlinkage ssize_t sys_write(unsigned int fd,
                             const char __user *buf,
                             size_t count)






                             
5. Kernel Validates Everything

Checks whether fd is valid for this process
Checks the file descriptor flags (write allowed?)
Checks whether the buffer pointer is accessible
Copies data from user-space → kernel-space using copy_from_user()
Why copy?
→ direct access to user memory is dangerous.





6. Kernel Calls the File’s Write Function

Every file descriptor is linked to a file_operations structure.

For a terminal → tty_write()
For a file → ext4_file_write_iter()
For a socket → sock_write_iter()
For a pipe → pipe_write()

file->f_op->write_iter(file, buf, count);





7. Data Reaches Destination


If writing to a file

Goes to filesystem cache (page cache)
Mark pages as "dirty"
Will be flushed to disk later by kernel

If writing to a terminal

Printed on your screen immediately

If writing to a pipe

Stored in pipe buffer
Process on the other end reads it

If writing to a socket

Sent to network stack
TCP/IP handles transmission




8. Kernel Returns to User Space

rax = number of bytes written
OR
rax = -errno (negative) on error

sysret
Switches back to user mode.




9. GLIBC Wrapper Converts Errors

-EBADF

GLIBC:
Converts to -1
Sets errno = EBADF


if (write(...) == -1) {
    perror("write");
}



*/

