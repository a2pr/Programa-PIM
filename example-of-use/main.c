/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <time.h>
int main()
{
    char time_s[50];
    struct tm *p,something;
    p=&something;
    
    something.tm_mday=20;
    something.tm_mon=0;
    something.tm_year=2019;
    
    strftime(time_s, sizeof(time_s), "%x", p);
    printf("%s  ", time_s);

    return 0;
}
