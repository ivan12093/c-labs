#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "struct_file.h"
#include "errors.h"

int get_struct_by_pos(FILE *f, long pos, struct_t *obj)
{
    long initial = ftell(f);
    if (initial == -1L)
        return FTELL_FAILED;
    
    if (fseek(f, pos, SEEK_SET))
        return FSEEK_FAILED;

    if (!fread(obj->pstruct, obj->size, 1, f))
        return FREAD_FAILED;

    if (fseek(f, initial, SEEK_SET))
        return FSEEK_FAILED;

    return EXIT_SUCCESS;
}

int put_struct_by_pos(FILE *f, long pos, struct_t *obj)
{
    long initial = ftell(f);
    if (initial == -1L)
        return FTELL_FAILED;

    if (fseek(f, pos, SEEK_SET))
        return FSEEK_FAILED;
    
    if (!fwrite(obj->pstruct, obj->size, 1, f))
        return FWRITE_FAILED;

    if (fseek(f, initial, SEEK_SET))
        return FSEEK_FAILED;

    return EXIT_SUCCESS;
}

long file_size(FILE *f)
{
    long initial = ftell(f);
    if (initial == -1L)
        return -1L;

    if (fseek(f, 0L, SEEK_END))
        return -1L;

    long size = ftell(f);
    if (size == -1L)
        return -1L;

    if (fseek(f, 0L, SEEK_END))
        return -1L;

    return size;
}

int swap_structs(FILE *f, long pos1, long pos2, size_t struct_size)
{
    int return_code = EXIT_SUCCESS;

    struct_t obj1 = {.pstruct = malloc(struct_size), .size = struct_size};
    struct_t obj2 = {.pstruct = malloc(struct_size), .size = struct_size};

    if ((return_code = get_struct_by_pos(f, pos1, &obj1)))
        goto swap_structs_exit;
    
    if ((return_code = get_struct_by_pos(f, pos2, &obj2)))
        goto swap_structs_exit;

    if ((return_code = put_struct_by_pos(f, pos1, &obj2)))
        goto swap_structs_exit;

    if ((return_code = put_struct_by_pos(f, pos2, &obj1)))
        goto swap_structs_exit;

swap_structs_exit:

    free(obj1.pstruct);
    free(obj2.pstruct);
    return return_code;
}

int sort_structs(FILE *f, size_t struct_size, int (*cmp)(struct_t *, struct_t *))
{
    long size = file_size(f);
    if (size == -1L)
        return FILE_LEN_ERR;

    struct_t min = {.pstruct = malloc(struct_size), .size = struct_size};
    struct_t obj = {.pstruct = malloc(struct_size), .size = struct_size};
    long min_pos;

    int return_code = EXIT_SUCCESS;
    
    for (size_t i = 0; i < (size_t)size - struct_size; i += struct_size)
    {
        min_pos = i;
        if ((return_code = get_struct_by_pos(f, i, &min)))
            goto sort_structs_exit;

        for (size_t j = i + struct_size; j < (size_t)size; j += struct_size)
        {
            if ((return_code = get_struct_by_pos(f, j, &obj)))
                goto sort_structs_exit;
            
            if (cmp(&obj, &min) < 0)
            {
                memcpy(min.pstruct, obj.pstruct, struct_size);
                min_pos = j;
            }
        }

        if ((return_code = swap_structs(f, min_pos, i, struct_size)))
            goto sort_structs_exit;
    }

sort_structs_exit:

    free(min.pstruct);
    free(obj.pstruct);

    return EXIT_SUCCESS;
}

int copy_structs_if(FILE *src, size_t struct_size, int (*cmp)(struct_t *), FILE *dst)
{
    int return_code = EXIT_SUCCESS;
    struct_t obj = {.pstruct = malloc(struct_size), .size = struct_size};

    long size = file_size(src);
    if ((size_t)size < struct_size)
    {
        return_code = NO_CONTENT;
        goto copy_structs_if_exit;
    }

    long dst_pos = ftell(dst);
    if (dst_pos == -1L)
    {
        return_code = FTELL_FAILED;
        goto copy_structs_if_exit;
    }

    for (long src_pos = 0; src_pos < size; src_pos += struct_size)
    {
        if ((return_code = get_struct_by_pos(src, src_pos, &obj)))
            goto copy_structs_if_exit;
        
        if (cmp(&obj))
        {
            if ((return_code = put_struct_by_pos(dst, dst_pos, &obj)))
                goto copy_structs_if_exit;
            dst_pos += struct_size;
        }
    }

    long diff_pos = ftell(dst);
    if (diff_pos == -1L)
    {
        return_code = FTELL_FAILED;
        goto copy_structs_if_exit;
    }

    if (diff_pos == dst_pos)
    {
        return_code = NO_CONTENT;
        goto copy_structs_if_exit;
    }

copy_structs_if_exit:

    free(obj.pstruct);
    return return_code;
}

int remove_structs_if(FILE *f, size_t struct_size, int (*cmp)(struct_t *))
{
    int return_code;
    int fd = fileno(f);
    if (fd == -1)
        return FD_GET_ERR;
    
    long size = file_size(f);
    long write_pos = 0;

    struct_t obj = {.pstruct = malloc(struct_size), .size = struct_size};

    for (long read_pos = 0L; read_pos < size; read_pos += struct_size)
    {
        if ((return_code = get_struct_by_pos(f, read_pos, &obj)))
            goto remove_structs_if_exit;

        if (!cmp(&obj))
        {
            if ((return_code = put_struct_by_pos(f, write_pos, &obj)))
                goto remove_structs_if_exit;

            write_pos += struct_size;
        }
    }

    if (write_pos == 0)
    {
        return_code = NO_CONTENT;
        goto remove_structs_if_exit;
    }

    if ((return_code = ftruncate(fd, write_pos)))
        goto remove_structs_if_exit;

remove_structs_if_exit:

    free(obj.pstruct);
    return EXIT_SUCCESS;
}

int aggregates(FILE *f, size_t struct_size, double (*aggr)(struct_t *))
{
    int return_code = 0;

    long size = file_size(f);

    if ((size_t)size < struct_size)
        return NO_CONTENT;

    struct_t obj = {.pstruct = malloc(struct_size), .size = struct_size};

    for (size_t pos = 0; pos < (size_t)size; pos += struct_size)
    {
        if ((return_code = get_struct_by_pos(f, pos, &obj)))
            goto aggregates_exit;
        
        aggr(&obj);
    }

aggregates_exit:

    free(obj.pstruct);
    return return_code;
}

int print_structs(FILE *f, size_t struct_size, void (*print)(struct_t *))
{
    int return_code;
    
    long size = file_size(f);
    if (size == -1L)
        return NO_CONTENT;

    struct_t obj = {.pstruct = malloc(struct_size), .size = struct_size};

    for (long read_pos = 0; read_pos < size; read_pos += struct_size)
    {
        if ((return_code = get_struct_by_pos(f, read_pos, &obj)))
            goto print_structs_exit;
        print(&obj);
    }

print_structs_exit:

    free(obj.pstruct);
    return EXIT_SUCCESS;
}
