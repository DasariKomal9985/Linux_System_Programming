#include<unistd.h>
#include<fcntl.h>
int main()
{
        char buffer[50];
        int fd = open("random.txt",O_RDONLY);
        int size = read(fd,buffer,20);
        int fd1 = open("random1.txt",O_CREAT | O_WRONLY, 0642);
        write(fd1,buffer,size);
}
