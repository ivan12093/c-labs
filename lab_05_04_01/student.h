#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <inttypes.h>

#define SURNAME_LEN 25
#define NAME_LEN 10
#define NUM_OF_SUBJECTS 4

#define EPS 1e-6

typedef struct
{
    char surname[SURNAME_LEN + 1];
    char name[NAME_LEN + 1];
    uint32_t grades[NUM_OF_SUBJECTS];
} student_t;

double gpa(student_t *student);
void print_student(student_t *student);
int cmp_gpa_with_val(student_t *student, double val);
int cmp_students_by_surname_name(student_t *st1, student_t *st2);
int is_student_surname_sw_str(student_t *student, char *str);

#endif // __STUDENT_H__
