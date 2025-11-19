#include<unistd.h>
#include<fcntl.h>
int main()
{
        char buffer[50];
        int fd = open("random.txt",O_RDWR | O_TRUNC);
        write(fd,"komal is waiting please go\n",27);
}
