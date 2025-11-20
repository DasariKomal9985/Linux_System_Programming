/*


✅ What is stat()?

stat() is a system call that retrieves information about a file using its filename/path.


It gives you:

file size
file permissions
owner
inode number
timestamps
file type (directory, regular file, symlink, etc.)


❓ Why we have to use stat()?
Because you cannot get file information using open(), read(), or write().

Only stat() provides complete metadata.


🔧 How to use stat()?

stat("file.txt", &info);

filename (path)
a pointer to struct stat


📌 Where to use stat()?

Check if file exists
Check file type (directory? regular file?)
Get file size
Implement commands like ls, find, cp, mv, rm
Before reading the file


*/

#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat st;

    if (stat("random.txt", &st) == 0) {
        printf("stat(): File size = %ld\n", st.st_size);
        printf("stat(): File inode = %ld\n", st.st_ino);
        printf("stat(): Permissions = %o\n", st.st_mode & 0777);
    } else {
        perror("stat failed");
    }
}

