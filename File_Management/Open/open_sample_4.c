#include<unistd.h>
#include<fcntl.h>
int main()
{
        char buffer[50];
        int fd = open("random2.txt",O_CREAT | O_WRONLY,0642);
        int size = read(0,buffer,20);
        write(fd,buffer,size);
}

