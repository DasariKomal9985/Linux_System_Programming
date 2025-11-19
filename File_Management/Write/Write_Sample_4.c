#include<unistd.h>
#include<stdio.h>
int main()
{
        int size;
        size = write(1,"hello komal\n",sizeof("hello komal\n")-1);
        printf("the size of string is %d\n",size);
}
