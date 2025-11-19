#include<unistd.h>
#include<fcntl.h>
int main()
{
        char buffer[50];
        int fd = open("random.txt",O_RDWR | O_TRUNC);
        int size = read(0,buffer,30);
        int size2 = write(fd,buffer,size);
        write(1,"Komal Hello How R U ?\n",22);
}
