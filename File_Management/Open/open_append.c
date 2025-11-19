#include<unistd.h>
#include<fcntl.h>
int main()
{
        char buffer[50];
        int fd = open("random.txt",O_RDWR | O_APPEND);
        write(fd,"ok he left from home\n",22);
}

