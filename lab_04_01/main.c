#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *my_strpbrk(char *s, char *accept)
{
    for (size_t i = 0; s[i] != '\0'; ++i)
        for (size_t j = 0; accept[j] != '\0'; ++j)
            if (s[i] == accept[j])
                return s + i;
    return NULL;
}

size_t my_strspn(char *s, char *accept)
{
    int flag = 1;
    size_t i;
    for (i = 0; s[i] != '\0'; ++i)
    {
        flag = 0;
        for (size_t j = 0; accept[j] != '\0' && !flag; ++j)
            if (s[i] == accept[j])
                flag = 1;
        if (!flag)
            break;
    }
    return i;
}

size_t my_strcspn(char *s, char *reject)
{
    size_t i;
    for (i = 0; s[i] != '\0'; ++i)
        for (size_t j = 0; reject[j] != '\0'; ++j)
            if (s[i] == reject[j])
                return i;
    return i;
}

char *my_strchr(char *s, int c)
{
    size_t i;
    for (i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            return s + i;
    if (s[i] == c)
        return s + i;
    return NULL;
}
 
char *my_strrchr(char *s, int c)
{
    char *p = NULL;
    size_t i;
    for (i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            p = s + i;
    if (s[i] == c)
        p = s + i;
    return p;
}

int compare_strpbrk(char *s1, char *s2)
{
    return my_strpbrk(s1, s2) == strpbrk(s1, s2);
}

int compare_strspn(char *s1, char *s2)
{
    return my_strspn(s1, s2) == strspn(s1, s2);
}

int compare_strcspn(char *s1, char *s2)
{
    return my_strcspn(s1, s2) == strcspn(s1, s2);
}

int compare_strchr(char *s, int c)
{
    return my_strchr(s, c) == strchr(s, c);
}

int compare_strrchr(char *s, int c)
{
    return my_strrchr(s, c) == strrchr(s, c);
}

int test_first(int (*cmp)(char *, char *))
{
    int total_failed = 0;
    
    char *s1 = "test_string";
    char *s2 = "pillow";

    total_failed += !cmp(s1, s2);
    total_failed += !cmp(s2, s1);

    char *s3 = "";
    char *s4 = "ABCDEF";

    total_failed += !cmp(s3, s4);
    total_failed += !cmp(s4, s3);

    char *s6 = "test";
    total_failed += !cmp(s6, s6);

    char *s7 = "ABCDEF";
    char *s8 = "abcdef";

    total_failed += !cmp(s7, s8);

    char *s9 = "Hello";
    char *s10 = "Lowr";

    total_failed += !cmp(s9, s10);
    total_failed += !cmp(s10, s9);

    char *s11 = "wtwtwatgahat";
    char *s12 = "wt";

    total_failed += !cmp(s11, s12);
    total_failed += !cmp(s12, s11);

    char *s13 = "wtwtwtwtw";
    char *s14 = "a";

    total_failed += !cmp(s13, s14);
    total_failed += !cmp(s14, s13);

    return total_failed;
}

int test_second(int (*cmp)(char *, int))
{
    int total_failed = 0;

    char *s1 = "ego sum via veritas et vita";
    char c = 'a';
    total_failed += !cmp(s1, c);

    char *s2 = "wingardium leviosa";
    c = 'i';
    total_failed += !cmp(s2, c);

    c = 'z';
    total_failed += !cmp(s2, c);

    c = '\0';
    total_failed += !cmp(s2, c);

    return total_failed;
}

int main(void)
{
    int total_failed = test_first(compare_strpbrk);
    total_failed += test_first(compare_strspn);
    total_failed += test_first(compare_strcspn);
    total_failed += test_second(compare_strchr);
    total_failed += test_second(compare_strrchr);
    printf("TESTS FAILED: %d\n", total_failed);
    return EXIT_SUCCESS;
}
