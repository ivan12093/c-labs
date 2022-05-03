#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 257

#define EMPTY_STRING 1
#define BUFFER_OVERFLOW 2

int scan_string(char *buf, size_t size)
{
    int chr;
    size_t len = 0;
    while ((chr = getchar()) != '\0' && chr != EOF && len < size)
    {
        buf[len] = (char) chr;
        ++len;
    }
    if (!len)
        return EMPTY_STRING;
    buf[len] = '\0';
    if (getchar() != EOF)
        return BUFFER_OVERFLOW;
    return EXIT_SUCCESS;
}

int is_number(const char *s)
{
    const char *digits = "0123456789";
    
    if (strlen(s) < 15)
        return 0;

    int check_operator_code = s[0] == '(' && strspn(s + 1, digits) == 3 && s[4] == ')';
    int check_number1 = s[5] == '-' && strspn(s + 6, digits) == 3 && s[9] == '-';
    int check_number2 = strspn(s + 10, digits) == 2 && s[12] == '-' && strspn(s + 13, digits) >= 2;

    return check_operator_code && check_number1 && check_number2;
}

int contains_phone_number(const char *s)
{
    for (size_t i = 0; s[i] != 0; ++i)
    {
        if (is_number(s + i))
            return 1;
    }
    return 0;
}

int main(void)
{
    char str[BUF_SIZE];
    int return_code;
    if ((return_code = scan_string(str, BUF_SIZE)))
        return return_code;

    if (contains_phone_number(str))
        puts("YES");
    else
        puts("NO");

    return EXIT_SUCCESS;
}

