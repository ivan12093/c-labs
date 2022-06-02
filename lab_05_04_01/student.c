#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <math.h>

#include "student.h"

double gpa(student_t *student)
{
    double sum = 0;
    for (int i = 0; i < NUM_OF_SUBJECTS; ++i)
        sum += (student->grades)[i];
    
    double gpa = sum / NUM_OF_SUBJECTS;
    return gpa;
}

void print_student(student_t *student)
{
    printf("%s\n%s\n", student->surname, student->name);
    for (int i = 0; i < NUM_OF_SUBJECTS; ++i)
        printf("%"PRIu32" ", student->grades[i]);
    printf("\n");
}

int cmp_students_by_surname_name(student_t *st1, student_t *st2)
{
    int cmp_surnames = strcmp(st1->surname, st2->surname);
    if (!cmp_surnames)
        return strcmp(st1->name, st2->name);
    
    return cmp_surnames;
}

int is_student_surname_sw_str(student_t *student, char *str)
{
    return strstr(student->surname, str) == student->surname;
}

int cmp_gpa_with_val(student_t *student, double val)
{
    double st_gpa = gpa(student);
    if (fabs(st_gpa - val) < EPS)
        return 0;
    else if (st_gpa > val)
        return 1;
    return -1;
}
