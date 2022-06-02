#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "student.h"
#include "struct_file.h"

static char str_[SURNAME_LEN + 1];
static double val_;

int is_student_surname_sw_str_(struct_t *obj)
{
    return is_student_surname_sw_str((student_t *)obj->pstruct, str_);
}

int is_gpa_less_val_(struct_t *obj)
{
    return gpa((student_t *)obj->pstruct) < val_;
}

double avg_gpa(struct_t *obj)
{
    static size_t count = 0;
    static double gpa_sum = 0.0;

    if (obj == NULL)
    {
        double avg_gpa = gpa_sum / count;
        count = 0;
        gpa_sum = 0.0;
        return avg_gpa;
    }

    gpa_sum += gpa((student_t *)obj->pstruct);
    ++count;
    return gpa_sum / count;
}

void print_student_(struct_t *obj)
{
    print_student((student_t *)obj->pstruct);
}

int cmp_students_by_surname_name_(struct_t *obj1, struct_t *obj2)
{
    return cmp_students_by_surname_name((student_t *)obj1->pstruct, (student_t *)obj2->pstruct);
}

int main(int argc, char **argv)
{
    int return_code = EXIT_SUCCESS;
    FILE *f = NULL;
    FILE *dst = NULL;
    if (argc == 3 && !strcmp(argv[1], "sb"))
    {
        f = fopen(argv[2], "r+b");
        if (f == NULL)
            return FILE_OPEN_ERR;
            
        return_code = sort_structs(f, sizeof(student_t), cmp_students_by_surname_name_);
        if (!return_code)
            return_code = print_structs(f, sizeof(student_t), print_student_);
    }
    else if (argc == 3 && !strcmp(argv[1], "db"))
    {
        f = fopen(argv[2], "r+b");
        if (f == NULL)
            return FILE_OPEN_ERR;
            
        return_code = aggregates(f, sizeof(student_t), avg_gpa);

        if (!return_code)
        {
            val_ = avg_gpa(NULL);
            return_code = remove_structs_if(f, sizeof(student_t), is_gpa_less_val_);
        }
    }
    else if (argc == 5 && !strcmp(argv[1], "fb"))
    {
        if (strlen(argv[4]) > SURNAME_LEN)
            return INCORRECT_ARGS;
                
        f = fopen(argv[2], "rb");
        if (f == NULL)
            return FILE_OPEN_ERR;

        dst = fopen(argv[3], "wb");
        if (dst == NULL)
            return_code = FILE_OPEN_ERR;

        if (!return_code)
        {
            strcpy(str_, argv[4]);
            return_code = copy_structs_if(f, sizeof(student_t), is_student_surname_sw_str_, dst);
        }
    }
    else
        return INCORRECT_ARGS;

    if (f != NULL)
        fclose(f);

    if (dst != NULL)
        fclose(dst);

    return return_code;
}
