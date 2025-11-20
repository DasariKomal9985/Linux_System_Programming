#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
int main()
{
	char  buffer[50];
	int fd = open("Seekset.txt",O_RDWR);
	int size = lseek(fd, 5, SEEK_SET);
	printf("the position of Set is %d\n and Original is  :::::::: Hi Komal Dasari How R U its 9985798499\n",size);
	read(fd,buffer,10);
	write(1, buffer, 10);
	
}
