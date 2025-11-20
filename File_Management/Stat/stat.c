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



struct stat {
    dev_t     st_dev;     // device number
    ino_t     st_ino;     // inode number
    mode_t    st_mode;    // file type + permissions
    nlink_t   st_nlink;   // number of hard links
    uid_t     st_uid;     // owner
    gid_t     st_gid;     // group
    off_t     st_size;    // file size in bytes
    time_t    st_atime;   // access time
    time_t    st_mtime;   // modification time
    time_t    st_ctime;   // metadata change time
};



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

