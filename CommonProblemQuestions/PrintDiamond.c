/*
   * Written by  : Keith Brewer
   * Date Written: 10/20/2013
   *
   * This program was written as an exercise to a common knowledge test/thought
   * process evaluation question during interviews. It took about 15-20 minutes
   * from the very start of the problem, through drawing the figure out and 
   * figuring out the algorithm, to writing, testing, debugging, and optimizing
   * the code. In that time, there were about 2 previous iterations of it. 
*/

#include <stdio.h>
#include <stdlib.h>

void printDiamond (int width);
void printRow     (int spaceCount, int starCount);

int main(void)
{
    printDiamond(15);

    return 0;
}

//will print a diamond with at least 3 levels
//width is the max width of the diamond; i.e. the number of stars in middle row
void printDiamond(int width)
{
    if(width < 3) //min width of 3 makes diamond at least 3 rows
        width = 3;

    if((width % 2) == 0) //make sure the max width is odd
        width++;

    int level = 0; //which row of the diamond we are currently on
    //make top half of diamond
    for(int starCount = 1; starCount <= width; starCount += 2, level++)
    {
        int spaceCount = (width / 2) - level; //how many spaces before the stars

        printRow(spaceCount, starCount);
    }

    level -= 2; 
    //make bottom half of diamond
    for(int starCount = width - 2; starCount > 0; starCount -= 2, level--)
    {
        int spaceCount = (width / 2) - level;

        printRow(spaceCount, starCount);
    }

    return;
}

//prints a single row
void printRow(int spaceCount, int starCount)
{
    for(int i = 0; i < spaceCount; i++)
        printf(" ");
    for(int i = 0; i < starCount; i++)
        printf("*");
    putchar('\n');

    return;
}
