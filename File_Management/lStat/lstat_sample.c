/*



lstat() is exactly like stat() but it does NOT follow symbolic links.

❓ Why use lstat()?

Because sometimes you want info about:

✔ the symlink itself
NOT
✖ the file the link points to


lstat("mylink", &info);


📌 Where lstat() is used?

programs like ls -l, find, tar, cp -a
when working with symbolic links
backup tools
file system crawlers








*/


#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat st;

    if (lstat("mylink", &st) == 0) {
        printf("lstat(): Link size (path length) = %ld\n", st.st_size);

        if (S_ISLNK(st.st_mode))
            printf("lstat(): It is a symbolic link\n");
        else
            printf("lstat(): It is NOT a symbolic link\n");

    } else {
        perror("lstat failed");
    }
}













/*

   
lstat(): Link size (path length) = 10
lstat(): It is a symbolic link



mylink  →  random.txt


r a n d o m . t x t
1 2 3 4 5 6 7 8 9 10




| Field                       | What it represents                 |
| --------------------------- | ---------------------------------- |
| st_size                     | Length of link path ("random.txt") |
| st_mode                     | S_IFLNK                            |
| st_ino                      | inode of symlink file              |
| *NOT* size of original file | correct and expected               |



*/
