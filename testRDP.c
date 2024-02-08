#include "m1.h"

#include <stdio.h>

int parse_sum(char **s);
int cal(char **s);
int parse_fac(char **s);

int parse_sum(char **s)
{
    int tmp = cal(s);
    int tmp1;
    while (**s == '+')
    {
        (*s)++;
        tmp1 = cal(s);
        tmp = tmp+ tmp1;
    }
    return (tmp);
}

int cal(char **s)
{
    int tmp2 = parse_fac(s);
    int tmp;
    while (**s == '*')
    {
        (*s)++;
        tmp = parse_fac(s);
        tmp = tmp * tmp2;
    }
    return (tmp);
}

int parse_fac(char **s)
{
    if (**s >= '0' && **s <= '9')
    {
        int a = (**s) - '0';
        (*s)++;
        return(a);
    }   
    else if (**s == '(')
    {
        (*s)++;
        int a = parse_sum(s);
        printf("%d\n", a);
        return (a);
    }
    else 
        printf("expected number got %c", **s);
    return(-1);
}

int main()
{
    char *s= "(1+9)*9"; // should output 82
    int a = parse_sum(&s);
    printf("%d\n", a);
}