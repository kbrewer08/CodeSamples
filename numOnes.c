#include <stdio.h>

int numOnes(unsigned int num);

int main(void)
{
    unsigned int x = 413516;

    printf("There are %d ones in %d", numOnes(x), x);

    return 0;
}

int numOnes(unsigned int num)
{
    int ones = 0;

    for(int i = 0; i < 32; i++)
        if((num >> i) & 0x1)
            ones++;

    return ones;
}
