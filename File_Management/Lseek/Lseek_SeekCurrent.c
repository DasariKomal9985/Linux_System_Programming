#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	char buffer[70];
	int fd = open("Seekcurrent.txt",O_RDWR);
	//Lseek Current
	read(fd, buffer, 5);
	write(1, buffer, 5);
	int size = lseek(fd, 10, SEEK_CUR);
	printf("The current position is %d\n The Original Test is ::::::HIKomaliswaitingpleasegoquickits9985798499\n",size);
	read(fd, buffer, 20);
	write(1, buffer, 20);
}
