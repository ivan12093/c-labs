#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUF_SIZE 257
#define WORD_SIZE 17

#define EMPTY_STRING 1
#define BUFFER_OVERFLOW 2
#define TOO_LONG_WORD 3
#define NO_WORDS 4

int scan_string(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
        return EMPTY_STRING;

    if (buf[strlen(buf) - 1] != '\n')
        return BUFFER_OVERFLOW;
    
    return EXIT_SUCCESS;
}

size_t str_split(const char *s, const char *delim, char (*words)[WORD_SIZE])
{
    size_t words_len = 0;

    char copy_s[BUF_SIZE];
    strcpy(copy_s, s);

    char *first_word = strtok(copy_s, delim);
    if (first_word == NULL)
        return words_len;
    if (strlen(first_word) > WORD_SIZE - 1)
        return SIZE_MAX;

    strcpy(words[words_len], first_word);
    ++words_len;
    
    char *word;
    while ((word = strtok(NULL, delim)) != NULL)
    {
        if (strlen(word) > WORD_SIZE - 1)
            return SIZE_MAX;
        strcpy(words[words_len], word);
        ++words_len;
    }
    return words_len;
}

size_t str_unique(const char *s, char *dst)
{
    size_t len_dst = 0;
    for (size_t i = 0; s[i] != '\0'; ++i)
        if ((char *)s + i == strchr(s, s[i]))
        {
            dst[len_dst] = s[i];
            ++len_dst;
        }
    dst[len_dst] = '\0';
    return len_dst;
}

void join(char (*words)[WORD_SIZE], size_t len, char *dst)
{
    dst[0] = '\0';
    char sep = ' ';
    char transformed[WORD_SIZE];
    for (size_t i = 1; i < len; ++i)
        if (strcmp(words[len - 1], words[len - i - 1]))
        {
            str_unique(words[len - i - 1], transformed);
            strcat(dst, transformed);
            strncat(dst, &sep, 1);
        }
    dst[strlen(dst) - 1] = '\0';
}

int main(void)
{
    char str[BUF_SIZE];
    scan_string(str, BUF_SIZE);

    const char *delim = " ,;:-.!?\n";
    char words[BUF_SIZE][WORD_SIZE];
    size_t words_count = str_split(str, delim, words);

    if (!words_count)
        return NO_WORDS;

    if (words_count == SIZE_MAX)
        return TOO_LONG_WORD;

    char transformed[BUF_SIZE];
    join(words, words_count, transformed);
    printf("Result: %s\n", transformed);
}