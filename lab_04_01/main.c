#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *my_strpbrk(const char *s, const char *accept)
{
    for (size_t i = 0; s[i] != '\0'; ++i)
        for (size_t j = 0; accept[j] != '\0'; ++j)
            if (s[i] == accept[j])
                return (char *)s + i;

    return NULL;
}

size_t my_strspn(const char *s, const char *accept)
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

size_t my_strcspn(const char *s, const char *reject)
{
    size_t i;
    for (i = 0; s[i] != '\0'; ++i)
        for (size_t j = 0; reject[j] != '\0'; ++j)
            if (s[i] == reject[j])
                return i;
    return i;
}

char *my_strchr(const char *s, int c)
{
    for (size_t i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            return (char *)s + i;
    return NULL;
}
 
char *my_strrchr(const char *s, int c)
{
    char *p = NULL;
    for (size_t i = 0; s[i] != '\0'; ++i)
        if (s[i] == c)
            p = (char *)s + i;
    return p;
}

int compare_strpbrk(const char *s1, const char *s2)
{
    if (my_strpbrk(s1, s2) == strpbrk(s1, s2))
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int compare_strspn(const char *s1, const char *s2)
{
    if (my_strspn(s1, s2) == strspn(s1, s2))
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int compare_strcspn(const char *s1, const char *s2)
{
    if (my_strcspn(s1, s2) == strcspn(s1, s2))
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int compare_strchr(const char *s, int c)
{
    if (my_strchr(s, c) == strchr(s, c))
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int compare_strrchr(const char *s, int c)
{
    if (my_strrchr(s, c) == strrchr(s, c))
        return EXIT_SUCCESS;
    return EXIT_FAILURE;
}

int test_first(int (*cmp)(const char *, const char *))
{
    int total_failed = 0;
    char *s1 = "test_string";
    char *s2 = "pillow";

    if (cmp(s1, s2))
        ++total_failed;

    if (cmp(s2, s1))
        ++total_failed;

    char *s3 = "";
    char *s4 = "ABCDEF";

    if (cmp(s3, s4))
        ++total_failed;

    if (cmp(s4, s3))
        ++total_failed;

    char *s6 = "test";
    if (cmp(s6, s6))
        ++total_failed;

    char *s7 = "ABCDEF";
    char *s8 = "abcdef";

    if (cmp(s7, s8))
        ++total_failed;

    char *s9 = "Hello";
    char *s10 = "Lowr";

    if (cmp(s9, s10))
        ++total_failed;

    if (cmp(s10, s9))
        ++total_failed;

    char *s11 = "wtwtwatgahat";
    char *s12 = "wt";

    if (cmp(s11, s12))
        ++total_failed;

    if (cmp(s12, s11))
        ++total_failed;

    char *s13 = "wtwtwtwtw";
    char *s14 = "a";

    if (cmp(s13, s14))
        ++total_failed;

    if (cmp(s14, s13))
        ++total_failed;

    return total_failed;
}

int test_second(int (*cmp)(const char *, int))
{
    int total_failed = 0;

    char *s1 = "ego sum via veritas et vita";
    char c = 'a';
    if (cmp(s1, c))
        ++total_failed;

    char *s2 = "wingardium leviosa";
    c = 'i';
    if (cmp(s2, c))
        ++total_failed;

    c = 'z';
    if (cmp(s2, c))
        ++total_failed;

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