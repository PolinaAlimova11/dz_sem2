#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {//структура книги
    char zach[11];
    char famil[150];
    char name[150];
    char otch[150];
    char fak[10];
    char spec[150];
};

struct user {
    char log[20];
    char pass[20];
    char stud;
    char book;
};

struct book {//структура книги
    char ind[11];
    char fio[150];
    char name[150];
    char num1[10];
    char num2[10];
};

struct book* array_book(int line_file){//сохдание массива структур и заполнение его из файла
    struct book* arr_struct = (struct book *)malloc(line_file*sizeof(struct book));
    FILE *file = fopen("book.csv", "r");
    char str[100];

    for (int i =0; i<line_file; i++){
        fgets(str, 1000, file);
        strcpy(arr_struct[i].ind, strtok(str, ";"));
        strcpy(arr_struct[i].fio, strtok(NULL, ";"));
        strcpy(arr_struct[i].name, strtok(NULL, ";"));
        strcpy(arr_struct[i].num1, strtok(NULL, ";"));
        strcpy(arr_struct[i].num2, strtok(NULL, "\n"));
    }
    fclose(file);

    return arr_struct;
}

void print_file(struct book *arr_struct, int line_file)
{
    FILE *file = fopen("book.csv", "w");
    for (int i = 0; i<line_file; i++){
        fprintf (file, "%s;%s;%s;%s;%s\n", arr_struct[i].ind, arr_struct[i].fio, arr_struct[i].name, arr_struct[i].num1, arr_struct[i].num2);
    }
    fclose(file);
}

struct book *delete(struct book *arr_struct, int line_file, int number)
{
    struct book *arr = (struct book *)malloc((line_file-1)*sizeof(struct book));

    for (int i = 0; i<number; i++){
        strcpy(arr[i].ind, arr_struct[i].ind);
        strcpy(arr[i].fio, arr_struct[i].fio);
        strcpy(arr[i].name, arr_struct[i].name);
        strcpy(arr[i].num1, arr_struct[i].num1);
        strcpy(arr[i].num2, arr_struct[i].num2);
    }
    //пропускаем элемент с нужным индексом
    for (int i = (number+1); i<line_file; i++){
        strcpy(arr[i-1].ind, arr_struct[i].ind);
        strcpy(arr[i-1].fio, arr_struct[i].fio);
        strcpy(arr[i-1].name, arr_struct[i].name);
        strcpy(arr[i-1].num1, arr_struct[i].num1);
        strcpy(arr[i-1].num2, arr_struct[i].num2);
    }
    for (int i = 0; i<(line_file-1); i++){
        printf ("%s,%s", arr[i].ind, arr[i].fio);
    }


    free(arr_struct);
    return arr;


}

void edit(struct book *arr_struct, int j){
    char str[1000], c;
    int i = 0;
    printf ("Book: %s;%s;%s;%s;%s\n", arr_struct[j].ind, arr_struct[j].fio, arr_struct[j].name, arr_struct[j].num1, arr_struct[j].num2);
    printf ("Enter new book details\n");
    c = getchar();
    c = getchar();
    while ( c != '\n'){
        str[i] = c;
        i++;
        c = getchar();
    }
    str[i]='\0';
    strcpy(arr_struct[j].ind, strtok(str, ";"));
    strcpy(arr_struct[j].fio, strtok(NULL, ";"));
    strcpy(arr_struct[j].name, strtok(NULL, ";"));
    strcpy(arr_struct[j].num1, strtok(NULL, ";"));
    strcpy(arr_struct[j].num2, strtok(NULL, "\0"));
    printf ("Data changed successfully\n");
}

int line_f(FILE *file){//подсчитывает количество строк в файле
    int line_file = 0;
    //FILE *file = fopen("students.csv", "r");
    if (file == NULL)
        return -1;
    else
    {
        while (! feof(file))//пока не конец файла
        {
            if (fgetc(file) == '\n')//считаем количество строк
                line_file++;
        }
        line_file++;//последняя строчка не содержит знака конца строки
        fclose(file);
        return line_file;
    }

}

struct student* array_student(int line_file){//сохдание массива структур и заполнение его из файла
    struct student* arr_struct = (struct student *)malloc(line_file*sizeof(struct student));
    FILE *file = fopen("students.csv", "r");
    char str[100];

    for (int i =0; i<line_file; i++){
        fgets(str, 1000, file);
        strcpy(arr_struct[i].zach, strtok(str, ";"));
        strcpy(arr_struct[i].famil, strtok(NULL, ";"));
        strcpy(arr_struct[i].name, strtok(NULL, ";"));
        strcpy(arr_struct[i].otch, strtok(NULL, ";"));
        strcpy(arr_struct[i].fak, strtok(NULL, ";"));
        strcpy(arr_struct[i].spec, strtok(NULL, "\n"));
    }
    fclose(file);

    return arr_struct;
}

struct user* array_user(int line_file){//сохдание массива структур и заполнение его из файла
    struct user* arr_user = (struct user *)malloc(line_file*sizeof(struct user));
    FILE *file = fopen("users.csv", "r");
    char str[100];

    for (int i =0; i<line_file; i++){
        fgets(str, 1000, file);
        strcpy(arr_user[i].log, strtok(str, ";"));
        strcpy(arr_user[i].pass, strtok(NULL, ";"));
        strcpy(&arr_user[i].stud, strtok(NULL, ";"));
        strcpy(&arr_user[i].book, strtok(NULL, "\n"));
    }
    fclose(file);

    return arr_user;
}

void print_file_student(struct student *arr_struct, int line_file)
{
    FILE *file = fopen("students.csv", "w");
    for (int i = 0; i<line_file; i++){
        fprintf (file, "%s;%s;%s;%s;%s;%s\n", arr_struct[i].zach, arr_struct[i].famil, arr_struct[i].name, arr_struct[i].otch, arr_struct[i].fak, arr_struct[i].spec);
    }
    fclose(file);
}

struct student *delete_student(struct student *arr_struct, int line_file, int number)
{
    struct student *arr = (struct student *)malloc((line_file-1)*sizeof(struct student));

    for (int i = 0; i<number; i++){
        strcpy(arr[i].zach, arr_struct[i].zach);
        strcpy(arr[i].famil, arr_struct[i].famil);
        strcpy(arr[i].name, arr_struct[i].name);
        strcpy(arr[i].otch, arr_struct[i].otch);
        strcpy(arr[i].fak, arr_struct[i].fak);
        strcpy(arr[i].spec, arr_struct[i].spec);
    }
    //пропускаем элемент с нужным индексом
    for (int i = (number+1); i<line_file; i++){
        strcpy(arr[i-1].zach, arr_struct[i].zach);
        strcpy(arr[i-1].famil, arr_struct[i].famil);
        strcpy(arr[i-1].name, arr_struct[i].name);
        strcpy(arr[i-1].otch, arr_struct[i].otch);
        strcpy(arr[i-1].fak, arr_struct[i].fak);
        strcpy(arr[i-1].spec, arr_struct[i].spec);
    }

    free(arr_struct);
    return arr;
}

void edit_student(struct student *arr_struct, int j){
    char str[1000], c;
    int i = 0;
    printf ("Student: %s;%s;%s;%s;%s;%s\n", arr_struct[j].zach, arr_struct[j].famil, arr_struct[j].name, arr_struct[j].otch, arr_struct[j].fak, arr_struct[j].spec);
    printf ("Enter new student details\n");
    c = getchar();
    c = getchar();
    while ( c != '\n'){
        str[i] = c;
        i++;
        c = getchar();
    }
    str[i]='\0';
    strcpy(arr_struct[j].zach, strtok(str, ";"));
    strcpy(arr_struct[j].famil, strtok(NULL, ";"));
    strcpy(arr_struct[j].name, strtok(NULL, ";"));
    strcpy(arr_struct[j].otch, strtok(NULL, ";"));
    strcpy(arr_struct[j].fak, strtok(NULL, ";"));
    strcpy(arr_struct[j].spec, strtok(NULL, "\0"));
    printf ("Data changed successfully\n");
}

int main() {
    FILE *file_us;
    file_us = fopen("users.csv", "r");

    int line_us = line_f(file_us);
    struct user *arr_user = array_user(line_us);
    for (int i = 0; i < line_us; i++)
        printf("%s;%s;%c;%c\n", arr_user[i].log, arr_user[i].pass, arr_user[i].stud, arr_user[i].book);

    fclose(file_us);

    char log[20], pass[20];

    printf("Enter login:\n");
    scanf("%s", log);
    printf("Enter password:\n");
    scanf("%s", pass);

    char st, bk;
    int f = -1;

    for (int i = 0; i < line_us; i++) {
        if ((strcmp(log, arr_user[i].log) == 0) &&
            (strcmp(pass, arr_user[i].pass) == 0))//сравниваем индекс с индексами из массива
        {
            f = 1;
            st = arr_user[i].stud;
            bk = arr_user[i].book;
        }
    }
    printf("%c,%c\n", st, bk);
    if (f == -1) {
        printf("User is not found\n");
    } else {
        if ((st == '0') && (bk == '0')) {
            printf("User does not have rights");
        }
        if ((st == '1') && (bk == '0')) {
            FILE *file;//указатель на файл
            file = fopen("students.csv", "r");
            int line_file_student = line_f(file);//количество строчек в файле
            if (line_file_student == -1) {
                printf("Error opening file\n");
            }
            struct student *arr_struct_st = array_student(line_file_student);//запись в массив структур из файла

            for (int i = 0; i < line_file_student; i++) {
                printf("%s;%s;%s;%s;%s;%s\n", arr_struct_st[i].zach, arr_struct_st[i].famil, arr_struct_st[i].name,
                       arr_struct_st[i].otch, arr_struct_st[i].fak, arr_struct_st[i].spec);
            }

            printf("Menu:\n"
                   "1 - Add student(+)\n"
                   "2 - Delete student(-)\n"
                   "3 - Edit student information\n"
                   "4 - View student information\n"
                   "0 - Exit\n");
            int com;

            while (1) {
                scanf("%d", &com);
                if (com == 0) {
                    print_file_student(arr_struct_st, line_file_student);//печать в файл массива структур
                    break;
                }//работает

                if (com == 1) {//ДОБАВЛЕНИЕ КНИГИ
                    char isbn[9];
                    printf("Enter student ID number:\n");
                    scanf("%s", isbn);//считываем индекс
                    int f = 0;//флаг

                    for (int i = 0; i < line_file_student; i++) {
                        if (strcmp(isbn, arr_struct_st[i].zach) == 0)//сравниваем индекс с индексами из массива
                            f = 1;
                    }

                    if (f == 0) {//ничего не нашли
                        char c, str[250];
                        int i = 0;
                        arr_struct_st = (struct student *) realloc(arr_struct_st,
                                                                   (line_file_student + 1) * sizeof(struct student));
                        strcpy(arr_struct_st[line_file_student].zach, isbn);
                        printf("Enter surname:\n");
                        scanf("%s", arr_struct_st[line_file_student].famil);
                        printf("Enter name:\n");
                        scanf("%s", arr_struct_st[line_file_student].name);
                        printf("Enter patronymic:\n");
                        scanf("%s", arr_struct_st[line_file_student].otch);
                        printf("Enter faculty:\n");
                        scanf("%s", arr_struct_st[line_file_student].fak);
                        printf("Enter a specialty:\n");
                        c = getchar();//пропускаем переход на новую строку
                        c = getchar();
                        while (c != '\n') {
                            str[i] = c;
                            i++;
                            c = getchar();
                        }
                        str[i] = '\0';
                        strcpy(arr_struct_st[line_file_student].spec, str);
                        line_file_student++;

                    } else
                        printf("A student with this student ID is already there.(error)\n");
                }//работает

                if (com == 2) {// УДАЛИТЬ КНИГУ
                    char isbn[9];
                    int number;//номер книги в списке
                    printf("Enter student ID number:\n");
                    scanf("%s", isbn);//считываем индекс
                    int f = 0;//флаг
                    number = -1;

                    for (int i = 0; i < line_file_student; i++) {
                        if (strcmp(isbn, arr_struct_st[i].zach) == 0) {//сравниваем индекс с индексами из массива
                            number = i;
                        }
                    }

                    if (number != -1) {//если книга имеется
                        arr_struct_st = delete_student(arr_struct_st, line_file_student, number);//удаление книги
                        line_file_student--;
                        printf("Student deleted\n");
                    } else
                        printf("Student with such student ID does not exist\n");
                }//работает

                if (com == 3) {// РЕДАКТИРОВАТЬ КНИГУ
                    char isbn[9];
                    int number;//номер книги в списке
                    printf("Enter student ID number:\n");
                    scanf("%s", isbn);//считываем индекс
                    int j = -1;//флаг

                    for (int i = 0; i < line_file_student; i++) {
                        if (strcmp(isbn, arr_struct_st[i].zach) == 0) {//сравниваем индекс с индексами из массива
                            j = i;
                        }
                    }
                    if (j != 1) {
                        edit_student(arr_struct_st, j);
                    } else
                        printf("Student with such student ID does not exist\n");

                }//работает

                if (com == 4) {
                    char isbn[9];
                    int number = -1;//номер книги в списке
                    printf("Enter student ID number:\n");
                    scanf("%s", isbn);//считываем индекс

                    for (int i = 0; i < line_file_student; i++) {
                        if (strcmp(isbn, arr_struct_st[i].zach) == 0) {//сравниваем индекс с индексами из массива
                            number = i;
                        }
                    }

                    if (number == -1) {
                        printf("Student with such student ID does not exist\n");
                    } else {
                        printf("Student information:\n");
                        printf("%s;%s;%s;%s;%s;%s\n", arr_struct_st[number].zach, arr_struct_st[number].famil,
                               arr_struct_st[number].name,
                               arr_struct_st[number].otch, arr_struct_st[number].fak, arr_struct_st[number].spec);
                    }
                }//работает
                for (int i = 0; i < line_file_student; i++) {
                    printf("%s;%s;%s;%s;%s;%s\n", arr_struct_st[i].zach, arr_struct_st[i].famil, arr_struct_st[i].name,
                           arr_struct_st[i].otch, arr_struct_st[i].fak, arr_struct_st[i].spec);
                }
            }
            free(arr_struct_st);
        }
        if ((st == '0') && (bk == '1')) {
            FILE *file_book = fopen("book.csv", "r");
            int line_file = line_f(file_book);//количество строчек в файле
            if (line_file == -1) {
                printf("Error opening file\n");
            }
            struct book *arr_book = array_book(line_file);//запись в массив структур из файла

            for (int i = 0; i < line_file; i++) {
                printf("%s;%s;%s;%s;%s\n", arr_book[i].ind, arr_book[i].fio, arr_book[i].name, arr_book[i].num1,
                       arr_book[i].num2);
            }

            printf("Menu:\n"
                   "1 - Add book(+)\n"
                   "2 - Delete book(-)\n"
                   "3 - Edit book information\n"
                   "4 - Change the number of books available\n"
                   "0 - Exit\n");
            int com;

            while (1) {
                scanf("%d", &com);
                if (com == 0) {
                    print_file(arr_book, line_file);//печать в файл массива структур
                    break;
                }//работает

                if (com == 1) {//ДОБАВЛЕНИЕ КНИГИ
                    char isbn[9];
                    printf("Enter ISBN:\n");
                    scanf("%s", isbn);//считываем индекс
                    int f = 0;//флаг

                    for (int i = 0; i < line_file; i++) {
                        if (strcmp(isbn, arr_book[i].ind) == 0)//сравниваем индекс с индексами из массива
                            f = 1;
                    }

                    if (f == 0) {//ничего не нашли ПОМЕНЯТЬ ФЛАГ
                        char string[150], c;
                        int x = 0;
                        arr_book = (struct book *) realloc(arr_book, (line_file + 1) * sizeof(struct book));
                        strcpy(arr_book[line_file].ind, isbn);
                        printf("Enter author:\n");
                        c = getchar();
                        c = getchar();
                        while ( c != '\n'){
                            string[x] = c;
                            x++;
                            c = getchar();
                        }
                        string[x]='\0';
                        strcpy(arr_book[line_file].fio, string);
                        printf("Enter name:\n");
                        c = getchar();
                        c = getchar();
                        while ( c != '\n'){
                            string[x] = c;
                            x++;
                            c = getchar();
                        }
                        string[x]='\0';
                        strcpy(arr_book[line_file].name, string);
                        printf("Enter how many books:\n");
                        scanf("%s", arr_book[line_file].num1);
                        printf("Enter how many books are available:\n");
                        scanf("%s", arr_book[line_file].num2);
                        line_file++;

                    } else
                        printf("The book is already there(error)\n");
                }//работает

                if (com == 2) {// УДАЛИТЬ КНИГУ
                    char isbn[9];
                    int number;//номер книги в списке
                    printf("Enter ISBN:\n");
                    scanf("%s", isbn);//считываем индекс
                    int f = 0;//флаг
                    number = -1;

                    for (int i = 0; i < line_file; i++) {
                        if (strcmp(isbn, arr_book[i].ind) == 0) {//сравниваем индекс с индексами из массива
                            number = i;
                        }
                    }

                    if (number != -1) {//если книга имеется
                        arr_book = delete(arr_book, line_file, number);//удаление книги
                        line_file--;
                        //print_file(arr_struct, line_file);
                        printf("Book deleted\n");
                    } else
                        printf("No books in the library\n");
                }//работает

                if (com == 3) {// РЕДАКТИРОВАТЬ КНИГУ
                    char isbn[9];
                    int number;//номер книги в списке
                    printf("Enter ISBN:\n");
                    scanf("%s", isbn);//считываем индекс
                    int j = -1;//флаг

                    for (int i = 0; i < line_file; i++) {
                        if (strcmp(isbn, arr_book[i].ind) == 0) {//сравниваем индекс с индексами из массива
                            j = i;
                        }
                    }
                    if (j != 1) {
                        edit(arr_book, j);
                    } else
                        printf("No books in the library\n");

                }//работает

                if (com == 4) {
                    char isbn[9];
                    int number;//номер книги в списке
                    printf("Enter ISBN:\n");
                    scanf("%s", isbn);//считываем индекс
                    int f = 0;//флаг

                    for (int i = 0; i < line_file; i++) {
                        if (strcmp(isbn, arr_book[i].ind) == 0) {//сравниваем индекс с индексами из массива
                            f = 1;
                            number = i;
                        }
                    }

                    printf("Total books/books in stock:\n");
                    int num_1 = atoi(arr_book[number].num1);
                    int num_2 = atoi(arr_book[number].num2);
                    printf("%d %d\n", num_1, num_2);
                    printf("Enter the number of books available\n");
                    int num;
                    scanf("%d", &num);

                    if (num > num_1)
                        printf("There aren’t so many books in the library\n");
                    else {
                        //char str_num[10];
                        itoa(num, arr_book[number].num2, 10);
                        printf("Number of books changed\n");
                    }
                }//работает
                for (int i = 0; i < line_file; i++) {
                    printf("%s;%s;%s;%s;%s\n", arr_book[i].ind, arr_book[i].fio, arr_book[i].name,
                           arr_book[i].num1, arr_book[i].num2);
                }
            }
            free(arr_book);
        }
        if ((st == '1') && (bk == '1')) {
            printf("Menu:\n"
                   "1 - Menu of students(+)\n"
                   "2 - Menu of books(-)\n"
                   "0 - Exit\n");

            int com_us = 3;
            while (com_us != 0) {
                scanf("%d", &com_us);
                if (com_us == 1) {
                    FILE *file;//указатель на файл
                    file = fopen("students.csv", "r");
                    int line_file_student = line_f(file);//количество строчек в файле
                    if (line_file_student == -1) {
                        printf("Error opening file\n");
                    }
                    struct student *arr_struct_st = array_student(line_file_student);//запись в массив структур из файла

                    for (int i = 0; i < line_file_student; i++) {
                        printf("%s;%s;%s;%s;%s;%s\n", arr_struct_st[i].zach, arr_struct_st[i].famil,
                               arr_struct_st[i].name,
                               arr_struct_st[i].otch, arr_struct_st[i].fak, arr_struct_st[i].spec);
                    }

                    printf("Menu:\n"
                           "1 - Add student(+)\n"
                           "2 - Delete student(-)\n"
                           "3 - Edit student information\n"
                           "4 - View student information\n"
                           "0 - Exit\n");
                    int com;

                    while (1) {
                        scanf("%d", &com);
                        if (com == 0) {
                            print_file_student(arr_struct_st, line_file_student);//печать в файл массива структур
                            break;
                        }//работает

                        if (com == 1) {//ДОБАВЛЕНИЕ КНИГИ
                            char isbn[9];
                            printf("Enter student ID number:\n");
                            scanf("%s", isbn);//считываем индекс
                            int f = 0;//флаг

                            for (int i = 0; i < line_file_student; i++) {
                                if (strcmp(isbn, arr_struct_st[i].zach) == 0)//сравниваем индекс с индексами из массива
                                    f = 1;
                            }

                            if (f == 0) {//ничего не нашли
                                char c, str[250];
                                int i = 0;
                                arr_struct_st = (struct student *) realloc(arr_struct_st,
                                                                           (line_file_student + 1) *
                                                                           sizeof(struct student));
                                strcpy(arr_struct_st[line_file_student].zach, isbn);
                                printf("Enter surname:\n");
                                scanf("%s", arr_struct_st[line_file_student].famil);
                                printf("Enter name:\n");
                                scanf("%s", arr_struct_st[line_file_student].name);
                                printf("Enter patronymic:\n");
                                scanf("%s", arr_struct_st[line_file_student].otch);
                                printf("Enter faculty:\n");
                                scanf("%s", arr_struct_st[line_file_student].fak);
                                printf("Enter a specialty:\n");
                                c = getchar();//пропускаем переход на новую строку
                                c = getchar();
                                while (c != '\n') {
                                    str[i] = c;
                                    i++;
                                    c = getchar();
                                }
                                str[i] = '\0';
                                strcpy(arr_struct_st[line_file_student].spec, str);
                                line_file_student++;

                            } else
                                printf("A student with this student ID is already there.(error)\n");
                        }//работает

                        if (com == 2) {// УДАЛИТЬ КНИГУ
                            char isbn[9];
                            int number;//номер книги в списке
                            printf("Enter student ID number:\n");
                            scanf("%s", isbn);//считываем индекс
                            int f = 0;//флаг
                            number = -1;

                            for (int i = 0; i < line_file_student; i++) {
                                if (strcmp(isbn, arr_struct_st[i].zach) ==
                                    0) {//сравниваем индекс с индексами из массива
                                    number = i;
                                }
                            }

                            if (number != -1) {//если книга имеется
                                arr_struct_st = delete_student(arr_struct_st, line_file_student,
                                                               number);//удаление книги
                                line_file_student--;
                                printf("Student deleted\n");
                            } else
                                printf("Student with such student ID does not exist\n");
                        }//работает

                        if (com == 3) {// РЕДАКТИРОВАТЬ КНИГУ
                            char isbn[9];
                            int number;//номер книги в списке
                            printf("Enter student ID number:\n");
                            scanf("%s", isbn);//считываем индекс
                            int j = -1;//флаг

                            for (int i = 0; i < line_file_student; i++) {
                                if (strcmp(isbn, arr_struct_st[i].zach) ==
                                    0) {//сравниваем индекс с индексами из массива
                                    j = i;
                                }
                            }
                            if (j != 1) {
                                edit_student(arr_struct_st, j);
                            } else
                                printf("Student with such student ID does not exist\n");

                        }//работает

                        if (com == 4) {
                            char isbn[9];
                            int number = -1;//номер книги в списке
                            printf("Enter student ID number:\n");
                            scanf("%s", isbn);//считываем индекс

                            for (int i = 0; i < line_file_student; i++) {
                                if (strcmp(isbn, arr_struct_st[i].zach) ==
                                    0) {//сравниваем индекс с индексами из массива
                                    number = i;
                                }
                            }

                            if (number == -1) {
                                printf("Student with such student ID does not exist\n");
                            } else {
                                printf("Student information:\n");
                                printf("%s;%s;%s;%s;%s;%s\n", arr_struct_st[number].zach, arr_struct_st[number].famil,
                                       arr_struct_st[number].name,
                                       arr_struct_st[number].otch, arr_struct_st[number].fak,
                                       arr_struct_st[number].spec);
                            }
                        }//работает
                        for (int i = 0; i < line_file_student; i++) {
                            printf("%s;%s;%s;%s;%s;%s\n", arr_struct_st[i].zach, arr_struct_st[i].famil,
                                   arr_struct_st[i].name,
                                   arr_struct_st[i].otch, arr_struct_st[i].fak, arr_struct_st[i].spec);
                        }
                    }
                    free(arr_struct_st);
                }
                if (com_us == 2) {
                    FILE *file = fopen("book.csv", "r");//указатель на файл
                    int line_file = line_f(file);//количество строчек в файле
                    struct book *arr_struct = array_book(line_file);//запись в массив структур из файла

                    for (int i = 0; i < line_file; i++) {
                        printf("%s;%s;%s;%s;%s\n", arr_struct[i].ind, arr_struct[i].fio, arr_struct[i].name,
                               arr_struct[i].num1, arr_struct[i].num2);
                    }

                    printf("Menu:\n"
                           "1 - Add book(+)\n"
                           "2 - Delete book(-)\n"
                           "3 - Edit book information\n"
                           "4 - Change the number of books available\n"
                           "0 - Exit\n");
                    int com;

                    while (1) {
                        scanf("%d", &com);
                        if (com == 0) {
                            print_file(arr_struct, line_file);//печать в файл массива структур
                            break;
                        }//работает

                        if (com == 1) {//ДОБАВЛЕНИЕ КНИГИ
                            char isbn[9];
                            printf("Enter ISBN:\n");
                            scanf("%s", isbn);//считываем индекс
                            int f = 0;//флаг

                            for (int i = 0; i < line_file; i++) {
                                if (strcmp(isbn, arr_struct[i].ind) == 0)//сравниваем индекс с индексами из массива
                                    f = 1;
                            }

                            if (f == 0) {//ничего не нашли ПОМЕНЯТЬ ФЛАГ
                                char string[150], c;
                                int x = 0;
                                arr_struct = (struct book *) realloc(arr_struct, (line_file + 1) * sizeof(struct book));
                                strcpy(arr_struct[line_file].ind, isbn);
                                printf("Enter author:\n");
                                c = getchar();
                                c = getchar();
                                while ( c != '\n'){
                                    string[x] = c;
                                    x++;
                                    c = getchar();
                                }
                                string[x]='\0';
                                strcpy(arr_struct[line_file].fio, string);
                                printf("Enter name:\n");
                                c = getchar();
                                c = getchar();
                                while ( c != '\n'){
                                    string[x] = c;
                                    x++;
                                    c = getchar();
                                }
                                string[x]='\0';
                                strcpy(arr_struct[line_file].name, string);
                                printf("Enter how many books:\n");
                                scanf("%s", arr_struct[line_file].num1);
                                printf("Enter how many books are available:\n");
                                scanf("%s", arr_struct[line_file].num2);
                                line_file++;

                            } else
                                printf("The book is already there(error)\n");
                        }//работает

                        if (com == 2) {// УДАЛИТЬ КНИГУ
                            char isbn[9];
                            int number;//номер книги в списке
                            printf("Enter ISBN:\n");
                            scanf("%s", isbn);//считываем индекс
                            int f = 0;//флаг
                            number = -1;

                            for (int i = 0; i < line_file; i++) {
                                if (strcmp(isbn, arr_struct[i].ind) == 0) {//сравниваем индекс с индексами из массива
                                    number = i;
                                }
                            }

                            if (number != -1) {//если книга имеется
                                arr_struct = delete(arr_struct, line_file, number);//удаление книги
                                line_file--;
                                //print_file(arr_struct, line_file);
                                printf("Book deleted\n");
                            } else
                                printf("No books in the library\n");
                        }//работает

                        if (com == 3) {// РЕДАКТИРОВАТЬ КНИГУ
                            char isbn[9];
                            int number;//номер книги в списке
                            printf("Enter ISBN:\n");
                            scanf("%s", isbn);//считываем индекс
                            int j = -1;//флаг

                            for (int i = 0; i < line_file; i++) {
                                if (strcmp(isbn, arr_struct[i].ind) == 0) {//сравниваем индекс с индексами из массива
                                    j = i;
                                }
                            }
                            if (j != 1) {
                                edit(arr_struct, j);
                            } else
                                printf("No books in the library\n");

                        }//работает

                        if (com == 4) {
                            char isbn[9];
                            int number;//номер книги в списке
                            printf("Enter ISBN:\n");
                            scanf("%s", isbn);//считываем индекс
                            int f = 0;//флаг

                            for (int i = 0; i < line_file; i++) {
                                if (strcmp(isbn, arr_struct[i].ind) == 0) {//сравниваем индекс с индексами из массива
                                    f = 1;
                                    number = i;
                                }
                            }

                            printf("Total books/books in stock:\n");
                            int num_1 = atoi(arr_struct[number].num1);
                            int num_2 = atoi(arr_struct[number].num2);
                            printf("%d %d\n", num_1, num_2);
                            printf("Enter the number of books available\n");
                            int num;
                            scanf("%d", &num);

                            if (num > num_1)
                                printf("There aren’t so many books in the library\n");
                            else {
                                //char str_num[10];
                                itoa(num, arr_struct[number].num2, 10);
                                printf("Number of books changed\n");
                            }
                        }//работает
                        for (int i = 0; i < line_file; i++) {
                            printf("%s;%s;%s;%s;%s\n", arr_struct[i].ind, arr_struct[i].fio, arr_struct[i].name,
                                   arr_struct[i].num1, arr_struct[i].num2);
                        }
                    }
                    free(arr_struct);
                }
            }
        }
    }
        free(arr_user);
        return 0;
}
