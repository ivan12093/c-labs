#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 257

#define EMPTY_STRING 1
#define BUFFER_OVERFLOW 2

int scan_string(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
        return EMPTY_STRING;

    if (buf[strlen(buf) - 1] != '\n')
        return BUFFER_OVERFLOW;
    
    return EXIT_SUCCESS;
}

int is_number(const char *s)
{
    size_t i = 0;
    const char *digits = "0123456789";
    
    if (s[0] == '+')
        for (i = 1; s[i] != '('; ++i)
            if (strchr(digits, s[i]) == NULL)
                return 0;

    if (strlen(s + i) < 15)
        return 0;

    int check_operator_code = s[i] == '(' && strspn(s + i + 1, digits) == 3 && s[i + 4] == ')';
    int check_number1 = s[i + 5] == '-' && strspn(s + i + 6, digits) == 3 && s[i + 9] == '-';
    int check_number2 = strspn(s + i + 10, digits) == 2 && s[i + 12] == '-' && strspn(s + i + 13, digits) == 2;
    int check_number3 = s[i + 15] == '\0';

    return check_operator_code && check_number1 && check_number2 && check_number3;
}

int contains_phone_number(const char *s)
{
    const char *delim = " 	\t\n\v\f\r";

    char copy_s[BUF_SIZE];
    strcpy(copy_s, s);

    char *word = strtok(copy_s, delim);

    if (word == NULL)
        return 0;

    if (is_number(word))
        return 1;

    while ((word = strtok(NULL, delim)) != NULL)
        if (is_number(word))
            return 1;

    return 0;
}

int main(void)
{
    char str[BUF_SIZE];
    int return_code;
    if ((return_code = scan_string(str, BUF_SIZE)))
        return return_code;

    return_code = contains_phone_number(str);
    if (return_code)
        puts("YES");
    else
        puts("NO");

    return EXIT_SUCCESS;
}

