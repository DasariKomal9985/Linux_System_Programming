#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    struct stat st;

    if (stat("random.txt", &st) == -1) {
        perror("stat failed");
        return 1;
    }

    // 1. Basic info
    printf("File size: %ld bytes\n", st.st_size);
    printf("Inode: %ld\n", st.st_ino);

    // 2. Owner info
    printf("Owner UID: %d\n", st.st_uid);
    printf("Group GID: %d\n", st.st_gid);

    // 3. File type
    printf("File type: ");
    if (S_ISREG(st.st_mode)) printf("Regular File\n");
    else if (S_ISDIR(st.st_mode)) printf("Directory\n");
    else if (S_ISLNK(st.st_mode)) printf("Symbolic Link\n");
    else if (S_ISCHR(st.st_mode)) printf("Character Device\n");
    else if (S_ISBLK(st.st_mode)) printf("Block Device\n");
    else if (S_ISFIFO(st.st_mode)) printf("Pipe/FIFO\n");
    else if (S_ISSOCK(st.st_mode)) printf("Socket\n");

    // 4. Permissions
    printf("Permissions: ");
    printf( (st.st_mode & S_IRUSR) ? "r" : "-");
    printf( (st.st_mode & S_IWUSR) ? "w" : "-");
    printf( (st.st_mode & S_IXUSR) ? "x" : "-");
    printf( (st.st_mode & S_IRGRP) ? "r" : "-");
    printf( (st.st_mode & S_IWGRP) ? "w" : "-");
    printf( (st.st_mode & S_IXGRP) ? "x" : "-");
    printf( (st.st_mode & S_IROTH) ? "r" : "-");
    printf( (st.st_mode & S_IWOTH) ? "w" : "-");
    printf( (st.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    // 5. Timestamps
    printf("Last accessed: %s", ctime(&st.st_atime));
    printf("Last modified: %s", ctime(&st.st_mtime));
    printf("Last status change: %s", ctime(&st.st_ctime));

    return 0;
}

