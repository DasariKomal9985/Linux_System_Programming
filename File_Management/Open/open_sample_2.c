#include<unistd.h>
#include<fcntl.h>
int main()
{
        char buffer[50];
        int fd = open("random.txt",O_RDONLY);
        int size = read(fd,buffer,20);
        write(1,buffer,size);
}
