/*
read() reads data from a file, device, pipe, or socket into a buffer in your program.

ssize_t read(int fd, void *buf, size_t count);


Parameters

fd → File descriptor
buf → Pointer to memory where data should be stored
count → Maximum number of bytes you want to read


Return value

> 0 → Number of bytes actually read
0 → End of file (EOF)
-1 → Error (errno set)



🚀 What Happens When You Call read()

1. Your Program Calls the GLIBC read() Wrapper


read(fd, buffer, 100);

It goes to the GLIBC wrapper which:
Validates arguments
Places the system call number in rax (for x86-64)
Places fd, buf, count in registers
Executes syscall

| Register | Meaning          |
| -------- | ---------------- |
| `rax`    | 0 (read syscall) |
| `rdi`    | fd               |
| `rsi`    | buffer pointer   |
| `rdx`    | count            |


Then syscall switches CPU to kernel mode.




2. Kernel Locates the System Call Handler

sys_call_table[0] → sys_read()

asmlinkage ssize_t sys_read(unsigned int fd,
                            char __user *buf,
                            size_t count)


3. Kernel Validates Everything

Is fd valid?
Does this fd support reading?
Is buf a valid user-space address?
Is count reasonable?
If anything is wrong:
Returns -EBADF, -EFAULT, etc.



4. Kernel Calls the File’s Read Function

struct file_operations {
    read_iter;
    write_iter;
    ioctl;
    ...
}
file->f_op->read_iter(file, iov, count);
Different fd → different read behavior

File → ext4_file_read_iter()
Device → driver’s read function
Pipe → pipe_read()
Socket → sock_read_iter()



5. Data Flows Into Kernel Buffers


Depending on type:

File (Disk):

Data may already be in page cache → fast read
If not → kernel loads block from disk → page cache → user buffer

Terminal / Keyboard:

Uses line buffering
Blocks until you press Enter (canonical mode)

Pipe:

Blocks if pipe is empty
Reads whatever is there

Socket:

Reads from TCP/UDP receive buffer
Might return partial data




6. Kernel Copies Data to User Buffer

copy_to_user(buf, kernel_data, nbytes);
This copies bytes from kernel memory → your buffer. If it fails, returns -EFAULT.




7. Kernel Returns to User Mode

Return value is set:

Number of bytes read
0 → end-of-file
-errno → error

GLIBC translates:

Negative → return -1
Set errno to that error
Back to your program.





#include <unistd.h>
#include <fcntl.h>

int main() {
    char buf[100];

    int fd = open("test.txt", O_RDONLY);

    int n = read(fd, buf, sizeof(buf));
    if (n < 0) return 1;

    write(1, buf, n);   // echo to stdout

    close(fd);
}




When you call open():

glibc wrapper → syscall
kernel opens file → returns fd


When you call read():

kernel copies file data into a kernel buffer
kernel copies that data into your buf


When you call write():

kernel takes your buffer
writes it to terminal output buffer
text appears on your screen


When you call close():

kernel frees file structures
fd number becomes available

*/

#include<unistd.h>
int main()
{
        char buf[30];
        int size = read(0,buf,30);
        write(1,buf,size);
}



