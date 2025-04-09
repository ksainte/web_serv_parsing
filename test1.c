#include<stdio.h>

void test(char *s)
{
    // *s = "a";
    printf("is  %p\n",s);
}

int main()
{
    char *s;

    s = "a";
    printf("%p\n",s);

    test(s);
    // printf("%s",s);
    printf("%p\n",s);

    s[0] = 'c';


}