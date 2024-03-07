#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct student //record of each student
{
    char name[20];
    char rollno[20];
    int marks;
};

int lines = 0; // to count number of records in student.csv

struct student *stud_records;

char compute_grade(struct student temp)// to compute
{
    int m = temp.marks;
    if (m >= 90)
        return 'S';
        
    else if (m >= 80 && m < 90)
        return 'A';
    else if (m >= 70 && m < 80)
        return 'B';
    else if (m >= 60 && m < 70)
        return 'C';

    else if (m >= 50 && m < 60)
        return 'D';

    else if (m >= 40 && m < 50)
        return 'E';

    else
        return 'U';
}

void write_file(struct student temp)
{
    FILE *out;
    char file[25];

    sprintf(file, "%s.txt", temp.rollno);
    out = fopen(file, "w"); // to erase off the content present in the file
    char str[100], *word;
    char grade;

    out = fopen(file, "a"); // to appennd word by word using fprintf
    FILE *tem;
    tem = fopen("template.txt", "r");

    for (int k = 0; k < 10; k++)
    {
        char *a = fgets(str, 100, tem);
        word = strtok(str, " ");
        

        while (word != NULL)
        {
            if (strcmp(word, "{name}") == 0)
                fprintf(out, " %s", temp.name);

            else if (strcmp(word, "{name},\n") == 0)
                fprintf(out, " %s,\n", temp.name);

            else if (strcmp(word, "{rollno}") == 0)
                fprintf(out, " %s", temp.rollno);

            else if (strcmp(word, "{rollno})\n") == 0)
                fprintf(out, " %s)\n", temp.rollno);

            else if (strcmp(word, "{marks}") == 0)
                fprintf(out, " %d", temp.marks);

            else if (strcmp(word, "{grade}.\n") == 0)
            {
                grade = compute_grade(temp);
                fprintf(out, " %c\n", grade);
            }
            else
                fprintf(out, " %s", word);

            printf("%s",word);
            word = strtok(NULL, " ");
        }
    }
    fclose(tem);
    fclose(out);
}

void read_csv()
{
    FILE *in, *k;
    char str[40];
    char *name, *roll, *m, *file;
    int marks, j;
    in = fopen("student.csv", "r");

    struct student st[lines];
    for (int k = 0; k < lines; k++)
    {
        char *a = fgets(str, 40, in);

        name = strtok(str, ",");
        strcpy(st[k].name, name); // copy name number to the structure to store it as element

        roll = strtok(NULL, ",");
        strcpy(st[k].rollno, roll); // copy roll number to the structure to store it as element

        m = strtok(NULL, ",");
        marks = atoi(m);
        st[k].marks = marks;

        if (marks >= 0)
            write_file(st[k]); // writes the template into the respective file

        else
            printf("As the marks for the student %s is negative no template is formed.", name);
    }
}

int main()
{
    FILE *in;
    in = fopen("student.csv", "r");
    char c;
    int flag;
    while ((c = getc(in)) != EOF)
    {
        if (c == '\n')
        {
            flag = 1;
            lines++; // to count the number of records in student.csv
        }
    }

    if (flag == 1)
        lines++;

    fclose(in);

    read_csv(); // to read the contents of student.csv

    return 0;
}