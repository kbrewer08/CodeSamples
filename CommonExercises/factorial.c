#include <stdio.h>

int factorial_itr(const int num, const int pow);
int factorial_rec(const int num, const int pow);


int main(void)
{
    int x = 5;
    int y = 5;

    puts("");
    printf("iterative: %d ^ %d = %d\n", x, y, factorial_itr(x, y));
    printf("recursive: %d ^ %d = %d\n", x, y, factorial_rec(x, y));

    return 0;
}

int factorial_itr(const int num, const int pow)
{
    int sum = 1;

    for(int i = 1; i <= pow; i++)
        sum *= num;

    return sum;
}

int factorial_rec(const int num, const int pow)
{
    if(pow == 1)
        return num;

    return num * factorial_rec(num, pow - 1);
}
