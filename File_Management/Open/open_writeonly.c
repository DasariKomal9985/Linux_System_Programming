#include<unistd.h>
#include<fcntl.h>
int main()
{
        char buffer[50];
        int fd = open("random.txt",O_WRONLY);
        write(fd,"Hello Komal How R U ?\n",sizeof(fd));
}
