#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUF_SIZE 257
#define WORD_SIZE 17

#define EMPTY_STRING 1
#define BUFFER_OVERFLOW 2
#define TOO_LONG_WORD 3
#define EMPTY_UNIQUE 4

int scan_string(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
        return EMPTY_STRING;

    if (buf[strlen(buf) - 1] != '\n')
        return BUFFER_OVERFLOW;
    
    return EXIT_SUCCESS;
}

size_t split_str(const char *s, const char *delim, char (*splitted)[WORD_SIZE])
{
    size_t splitted_size = 0;

    char word[WORD_SIZE];
    size_t word_size = 0;
    for (size_t i = 0; s[i] != '\0'; ++i)
        if (strchr(delim, s[i]) == NULL)
        {
            if (word_size + 1 > WORD_SIZE - 1)
                return SIZE_MAX;
            word[word_size] = s[i];
            ++word_size;
        }
        else if (word_size)
        {
            word[word_size] = '\0';
            ++word_size;
            strcpy(splitted[splitted_size], word);
            ++splitted_size;
            word_size = 0;
        }
    if (word_size)
    {
        word[word_size] = '\0';
        ++word_size;
        strcpy(splitted[splitted_size], word);
        ++splitted_size;
        word_size = 0;
    }
    return splitted_size;
}

int contains(char (*strings)[WORD_SIZE], size_t len, const char *s)
{
    for (size_t i = 0; i < len; ++i)
        if (!strcmp(strings[i], s))
            return 1;
    return 0;
}

void print_words(char (*words)[WORD_SIZE], size_t len)
{
    for (size_t i = 0; i < len; ++i)
        printf("%s ", words[i]);
}

size_t unique_words(char (*src1)[WORD_SIZE], size_t len1, char (*src2)[WORD_SIZE], size_t len2, char (*dst)[WORD_SIZE])
{
    size_t dst_size = 0;
    for (size_t i = 0; i < len1; ++i)
        if (!contains(src2, len2, src1[i]) && !contains(dst, dst_size, src1[i]))
        {
            strcpy(dst[dst_size], src1[i]);
            ++dst_size;
        }
    
    for (size_t i = 0; i < len2; ++i)
        if (!contains(src1, len1, src2[i]) && !contains(dst, dst_size, src2[i]))
        {
            strcpy(dst[dst_size], src2[i]);
            ++dst_size;
        }
    return dst_size;
}

int main(void)
{
    const char *delim = " ,;:-.!?\n";
    char str1[BUF_SIZE];
    int is_error = scan_string(str1, BUF_SIZE);
    if (is_error)
        return is_error;
    
    char str2[BUF_SIZE];
    is_error = scan_string(str2, BUF_SIZE);
    if (is_error)
        return is_error;

    char words_array1[BUF_SIZE][WORD_SIZE];
    size_t len1 = split_str(str1, delim, words_array1);
    if (len1 == SIZE_MAX)
        return TOO_LONG_WORD;

    char words_array2[BUF_SIZE][WORD_SIZE];
    size_t len2 = split_str(str2, delim, words_array2);
    if (len2 == SIZE_MAX)
        return TOO_LONG_WORD;

    char unique[BUF_SIZE * 2][WORD_SIZE];
    size_t len_unique = unique_words(words_array1, len1, words_array2, len2, unique);
    if (!len_unique)
        return EMPTY_UNIQUE;

    printf("Result:");
    print_words(unique, len_unique);
    printf("\n");
}
