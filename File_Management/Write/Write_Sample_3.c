#include<unistd.h>
int main()
{
        write(1, "hello komal\n", sizeof("hello komal\n") - 1);

}
