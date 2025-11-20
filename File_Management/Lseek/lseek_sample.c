/*

lseek() is a system call that moves the file offset (read/write pointer) inside an open file.
This pointer decides where the next read or write happens.


off_t lseek(int fd, off_t offset, int whence);




| Parameter | Meaning                                        |
| --------- | ---------------------------------------------- |
| `fd`      | file descriptor                                |
| `offset`  | value added to reference position              |
| `whence`  | reference point (SEEK_SET, SEEK_CUR, SEEK_END) |


📌 Return Value

Returns new file offset (>= 0)
Returns -1 on error (sets errno)


⭐ 'whence' Options


lseek(fd, 10, SEEK_SET);
1️⃣ SEEK_SET → Set offset FROM the beginning
Move pointer to position 10 from start.

lseek(fd, -5, SEEK_CUR);
2️⃣ SEEK_CUR → Move relative to current position
Move pointer 5 bytes back from current position.

lseek(fd, 0, SEEK_END);
3️⃣ SEEK_END → Move relative to end of file
Go to end of file.



1️⃣ Move to start of file
lseek(fd, 0, SEEK_SET);


2️⃣ Skip first 20 bytes
lseek(fd, 20, SEEK_CUR);


3️⃣ Jump to end of file
lseek(fd, 0, SEEK_END);


4️⃣ Append manually using SEEK_END
lseek(fd, 0, SEEK_END);
write(fd, "New Line\n", 9);


5️⃣ Get the size of file
off_t size = lseek(fd, 0, SEEK_END);


6️⃣ Reset pointer back to start (rewind)
lseek(fd, 0, SEEK_SET);


7️⃣ Move backward inside file
lseek(fd, -10, SEEK_CUR);


8️⃣ Write in the middle of a file (overwrite)
lseek(fd, 6, SEEK_SET);         // jump to offset 6
write(fd, "XYZ", 3);            // overwrite 3 bytes



*/


#include<unistd.h>
#include<fcntl.h>
int main()
{
	char buffer[50];
	int fd = open("Random.txt", O_RDWR);
	read(fd,buffer,10);
	write(1,buffer,10);	//1234567890
	lseek(fd,10,SEEK_CUR);
	read(fd,buffer,10);
	write(1,buffer,10);	//komaldasar
}















