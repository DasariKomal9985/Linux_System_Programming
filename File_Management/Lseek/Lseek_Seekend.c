#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[30];

    int fd = open("seekend.txt", O_RDWR);
    if (fd < 0) return 1;

    // Get full file size
    int size2 = lseek(fd, 0, SEEK_END);
    printf("The size of file is %d\n", size2);

    // Reset pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read full file
    int n = read(fd, buffer, size2);
    write(1, buffer, n);

    close(fd);
}



/*
 
echo -n "komaldasariraois" > seekend.txt
for file set no extra garbage...
*/
