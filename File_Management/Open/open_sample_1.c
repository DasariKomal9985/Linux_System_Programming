/*


open() is the system call used to open files, devices, pipes, sockets, directories, etc.


POSIX version:
int open(const char *pathname, int flags);


Full version with permissions:
int open(const char *pathname, int flags, mode_t mode);


📌 What open() returns

On success → file descriptor (integer)
Examples: 3, 4, 5…

On failure → -1
And sets errno (example: ENOENT, EACCES)




| FD | Meaning |
| -- | ------- |
| 0  | stdin   |
| 1  | stdout  |
| 2  | stderr  |


The next open file gets fd = 3.


🚀 How open() Works Internally

1. You call open() from your program

int fd = open("test.txt", O_RDONLY);






2. GLIBC wrapper loads registers

rax = system call number (2 for open)
rdi = pathname pointer
rsi = flags
rdx = mode (if used)
Then executes the syscall instruction → CPU switches to kernel mode.





3. Kernel receives the request

sys_call_table[2] → sys_openat()
Note: Modern Linux redirects open() to openat().






4. Kernel checks permissions

The kernel checks:
Does this file exist?
Do you have permission? (read/write/execute)
Can the directory be accessed?
Valid flags?





5. Kernel resolves pathname → inode

Linux filesystem is inode-based.
Kernel walks the directory tree:
/home/user/test.txt
Find inode for test.txt
Loads inode into memory
Creates a struct file entry in kernel






6. Kernel allocates a file descriptor

Kernel assigns the lowest available FD number.
0  → stdin
1  → stdout
2  → stderr
3  → test.txt  <-- returned by open()





7. Kernel sets access mode & flags

Things like:
O_RDONLY
O_WRONLY
O_RDWR
O_CREAT
O_TRUNC
O_APPEND
Stored inside struct file.



8. open() returns to user space

Returned value:
>= 0 → file descriptor
-1 → failure
GLIBC wrapper updates errno if necessary.




Access Modes

O_RDONLY   → read only
O_WRONLY   → write only
O_RDWR     → read/write


Creation / Opening Behavior

O_CREAT    → create file if not exist
O_EXCL     → fail if file exists (used with O_CREAT)
O_TRUNC    → truncate file to 0 length if exists
O_APPEND   → write to end of file always


open("data.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
Creates if missing, truncates if exists, mode = rw-r--r--



int fd = open("notes.txt", O_RDONLY);
fd = 3



int fd = open("log.txt", O_WRONLY | O_CREAT, 0644);

The third argument 0644 is permission in octal.

Equivalent permissions:
Owner: read + write
Group: read
Others: read










#️⃣ 1. O_RDONLY

Open a file for reading only.

✔ Meaning:

You can only read from the file.
Any write attempt will fail.


int fd = open("data.txt", O_RDONLY);

✔ Use case:

Reading configuration files
Reading logs
Reading any input file






#️⃣ 2. O_WRONLY
Open a file for writing only.

✔ Meaning:

You can only write.
Reading from this fd will fail.

int fd = open("output.txt", O_WRONLY);

✔ Use case:

Writing logs
Writing sensor data
Writing output files
⚠ If the file does not exist → open fails.





#️⃣ 3. O_RDWR

Open file for both reading and writing.

✔ Meaning:

You can read and write
Useful for updating files

int fd = open("notes.txt", O_RDWR);

✔ Use case:

Modify an existing file
Read-modify-write operations





#️⃣ 4. O_CREAT

Create the file if it does not exist.

⚠ This flag MUST be used with a mode argument:

int fd = open("log.txt", O_CREAT | O_WRONLY, 0644);

✔ Meaning:

If file exists → open normally
If file does NOT exist → create it with given permissions

Permissions (mode):

0644 → rw-r--r--
0666 → rw-rw-rw-
0600 → rw-------


int fd = open("data.bin", O_WRONLY | O_CREAT, 0666);

✔ Use case:

Programs that generate files
Log file creation
First-time file creation






#️⃣ 5. O_TRUNC

Erase file contents if the file already exists.

✔ Meaning:

File exists → size becomes 0
File does NOT exist → open fails unless used with O_CREAT

int fd = open("output.txt", O_WRONLY | O_TRUNC);

int fd = open("log.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);


✔ Use case:

Start with an empty file
Overwriting old logs
Removing old text
⚠ Only works with write modes (O_WRONLY or O_RDWR)






#️⃣ 6. O_APPEND

Open the file in append mode.

✔ Meaning:

Every write goes to the end of the file.
lseek is ignored.
No overwrite of previous data.


int fd = open("history.log", O_WRONLY | O_APPEND);

✔ Use case:

Logging
Adding new entries to files
Multi-process safe writing
Because kernel ensures:

write always happens at the end → atomic for each process





| Flag     | Meaning                |
| -------- | ---------------------- |
| O_RDONLY | Read only              |
| O_WRONLY | Write only             |
| O_RDWR   | Read + write           |
| O_CREAT  | Create file if missing |
| O_TRUNC  | Make file empty        |
| O_APPEND | Write always at end    |
| O_EXCL   | Fail if file exists    |


*/




#include<unistd.h>
#include<fcntl.h>
int main()
{
        int fd = open("random.txt",O_WRONLY | O_CREAT | O_TRUNC, 0644);
        write(fd,"Hello Komal\n",12);
        close(fd);
}
