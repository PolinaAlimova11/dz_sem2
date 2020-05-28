#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <windows.h>

struct book {//структура книги
    char ind[10];
    char fio[150];
    char name[150];
    char num1[10];
    char num2[10];
};

int line_f(){//подсчитывает количество строк в файле
    int line_file = 0;
    FILE *file = fopen("book.csv", "r");
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

struct book* array(int line_file){//сохдание массива структур и заполнение его из файла
    struct book* arr_struct = (struct book *)malloc(line_file*sizeof(struct book));
    FILE *file = fopen("book.csv", "r");
    char str[100];

    for (int i =0; i<line_file; i++){
        fgets(str, 10, file);//почему-то только 9 чисел, НЕ ПОНИМАЮ
        strcpy(arr_struct[i].ind, str);
        fgetc(file);
        fgets(str, 1000, file);
        strcpy(arr_struct[i].fio, strtok(str, ";"));
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

struct book * delete(struct book *arr_struct, int line_file, int number)
{
    struct book *arr = (struct book *) malloc((line_file--) * sizeof(struct book));//создаём массив для дублирования
    int j = 0;
    for (int i = 0; i < (line_file--); i++) {
        if (j != number) {
            strcpy(arr[i].ind, arr_struct[j].ind);
            strcpy(arr[i].fio, arr_struct[j].fio);
            strcpy(arr[i].name, arr_struct[j].name);
            strcpy(arr[i].num1, arr_struct[j].num1);
            strcpy(arr[i].num1, arr_struct[j].num1);
            j++;
        } else
            j++;

    }
    line_file--;
    arr_struct = realloc(arr_struct, line_file * sizeof(struct book));

    for (int i = 0; i < line_file; i++) {
        strcpy(arr_struct[i].ind, arr[i].ind);
        printf ("%s %s", arr[i].ind, arr_struct[i].ind);
        strcpy(arr_struct[i].fio, arr[i].fio);
        strcpy(arr_struct[i].name, arr[i].name);
        strcpy(arr_struct[i].num1, arr[i].num1);
        strcpy(arr_struct[i].num1, arr[i].num1);
    }

    free(arr);

    return arr_struct;
}

void edit(struct book *arr_struct, int j){
    char str[1000], c;
    int i = 0;
    printf ("Book: %s %s %s %s %s\n", arr_struct[j].ind, arr_struct[j].fio, arr_struct[j].name, arr_struct[j].num1, arr_struct[j].num2);
    printf ("Enter new book details\n");
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

int main(){
    FILE *file;//указатель на файл
    int line_file = line_f();//количество строчек в файле
    struct book *arr_struct = array(line_file);//запись в массив структур из файла

    printf ("Menu:\n"
            "1 - Add book(+)\n"
            "2 - Delete book(-)\n"
            "3 - Edit book information\n"
            "4 - Change the number of books available\n"
            "0 - Exit\n");
    int com;

    while(1){
        scanf("%d", &com);
    if (com == 0)
    {
        print_file(arr_struct, line_file);//печать в файл массива структур
        break;
    }

    if (com == 1){//ДОБАВЛЕНИЕ КНИГИ
        char isbn[9];
        printf ("Enter ISBN:\n");
        scanf ("%s", &isbn);//считываем индекс
        int f=0;//флаг

        for (int i = 0; i<line_file; i++){
            if (strcmp(isbn, arr_struct[i].ind) == 0)//сравниваем индекс с индексами из массива
                f = 1;
        }

        if (f == 0){//ничего не нашли ПОМЕНЯТЬ ФЛАГ
            arr_struct = (struct book *)realloc(arr_struct, (line_file+1)*sizeof(struct book));
            strcpy(arr_struct[line_file].ind, isbn);
            printf ("Enter author:\n");
            scanf ("%s", arr_struct[line_file].fio);
            printf ("Enter name:\n");
            scanf ("%s", arr_struct[line_file].name);
            printf ("Enter how many books:\n");
            scanf ("%s", arr_struct[line_file].num1);
            printf ("Enter how many books are available:\n");
            scanf ("%s", arr_struct[line_file].num2);
            line_file++;

        } else
            printf ("The book is already there(error)\n");
    }

    if (com == 2){// УДАЛИТЬ КНИГУ
        char isbn[9];
        int number;//номер книги в списке
        printf ("Enter ISBN:\n");
        scanf ("%s", &isbn);//считываем индекс
        int f=0;//флаг

        for (int i = 0; i<line_file; i++){
            if (strcmp(isbn, arr_struct[i].ind) == 0) {//сравниваем индекс с индексами из массива
                f = 1;
                number = i;
            }
        }

        if (f == 1) {//если книга имеется
            arr_struct = delete(arr_struct, line_file, number);//удаление книги
            print_file(arr_struct, line_file);
            printf ("Book deleted\n");
        }
        else
            printf ("No books in the library\n");
    }

    if (com == 3){// РЕДАКТИРОВАТЬ КНИГУ
        char isbn[9];
        int number;//номер книги в списке
        printf ("Enter ISBN:\n");
        scanf ("%s", &isbn);//считываем индекс
        int f=0, j;//флаг

        for (int i = 0; i<line_file; i++){
            if (strcmp(isbn, arr_struct[i].ind) == 0) {//сравниваем индекс с индексами из массива
                f = 1;
                j = i;
            }
        }
        if ( f == 1){
            edit(arr_struct, j);
        } else
            printf ("No books in the library\n");

    }

    if (com == 4){
        char isbn[9];
        int number;//номер книги в списке
        printf ("Enter ISBN:\n");
        scanf ("%s", &isbn);//считываем индекс
        int f=0;//флаг

        for (int i = 0; i<line_file; i++){
            if (strcmp(isbn, arr_struct[i].ind) == 0) {//сравниваем индекс с индексами из массива
                f = 1;
                number = i;
            }
        }

        printf ("Total books/books in stock:\n");
        int num_1 = atoi(arr_struct[number].num1);
        int num_2 = atoi(arr_struct[number].num2);
        printf ("%d %d\n", num_1, num_2);
        printf ("Enter the number of books available\n");
        int num;
        scanf ("%d", &num);

        if (num > num_1)
            printf ("There aren’t so many books in the library\n");
            else
        {
            //char str_num[10];
            itoa(num, arr_struct[number].num2, 10);
            printf ("Number of books changed\n");
        }
    }
    for (int i = 0; i<line_file; i++){
        printf ("%s;%s;%s;%s;%s\n", arr_struct[i].ind, arr_struct[i].fio, arr_struct[i].name, arr_struct[i].num1, arr_struct[i].num2);
    }
}
    free(arr_struct);
    return 0;
