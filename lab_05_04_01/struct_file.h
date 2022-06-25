#ifndef __STRUCT_FILE_H__
#define __STRUCT_FILE_H__

#include <stdio.h>

typedef struct
{
    void *pstruct;
    size_t size;
} struct_t;

int get_struct_by_pos(FILE *f, long pos, struct_t *obj);
int put_struct_by_pos(FILE *f, long pos, struct_t *obj);
long file_size(FILE *f);
int swap_structs(FILE *f, long pos1, long pos2, size_t struct_size);
int sort_structs(FILE *f, size_t struct_size, int (*cmp)(struct_t *, struct_t *));
int copy_structs_if(FILE *src, size_t struct_size, int (*cmp)(struct_t *), FILE *dst);
int remove_structs_if(FILE *f, size_t struct_size, int (*cmp)(struct_t *));
int aggregates(FILE *f, size_t struct_size, double (*aggr)(struct_t *));
int print_structs(FILE *f, size_t struct_size, void (*print)(struct_t *));

#endif // __STRUCT_FILE_H__
