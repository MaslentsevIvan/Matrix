#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <windows.h>


struct in_data_int
{
    bool is_int = 0;
    int num = -1;
};


enum bool_entering_words
{
    BOOL_ROW_WORDS = 0,
    BOOL_LINES_WORDS = 1,
    BOOL_COLUMN_WORDS = 2,
};


enum color_codes
{
    RED = 4,
    GREEN = 10,
    WHITE = 15,
    WARNING = 244,
};


const char ROW_WORDS[] = "\nСколько рядов вы хотите ввести? ";
const char LINES_WORDS[] = "\nВведите количество столбцов для ";
const char COLUMN_WORDS[] = "Введите значание столбца №";


void print_warnings_for_users();
void scan_individ(struct in_data_int* const coeff);
void scan_individ_assign(struct in_data_int* const coeff, const int ch, const int i, char* entrance_data);
void cleaning_buffer();
void entering_int_numbers(int* const number, const bool_entering_words where_called, const int how_much_called);
bool entering_addit_cond(const int where_called, const int numb);
void print_mass(int** const data, const int size_x);
void mipt_cleaning(int*** data, const int quant_rows_0, const int quant_rows_1);
int entering_matrix(int*** data);


int main()
{
    setlocale(LC_ALL, "Russian");
    print_warnings_for_users();
    int** data[2] = { 0 };
    int quant_rows_0 = entering_matrix(&data[0]);
    int quant_rows_1 = entering_matrix(&data[1]);
    print_mass(data[0], quant_rows_0);
    printf("\n");
    print_mass(data[1], quant_rows_1);
    mipt_cleaning(data, quant_rows_0, quant_rows_1);
}


//Предупреждения для пользователей
void print_warnings_for_users()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, WARNING);
    printf("При вводе можно вводить не более 10 символов!!!\n");
    SetConsoleTextAttribute(hConsole, WHITE);
}


//Считывание чисел int
void scan_individ(struct in_data_int* const coeff)
{
    assert(coeff != NULL);

    int ch = 0;
    char entrance_data[11] = { 0 };
    int i = 0;
    for (i = 0; i < 11; i++)
    {
        ch = getchar();
        entrance_data[i] = ch;
        if (ch == EOF || ch == 26)
            break;
        if (ch == '\n')
        {
            i++;
            break;
        }
    }
    i--;
    scan_individ_assign(coeff, ch, i, entrance_data); /*Присваивание переменных после ввода в функции scan_individ*/
}


//Присваивание переменных после ввода в функции scan_individ
void scan_individ_assign(struct in_data_int* const coeff, const int ch, const int i, char* entrance_data)
{
    assert(coeff != NULL);
    assert(entrance_data != NULL);

    if ((i == 0 && ch == 10) || (ch == 26 || ch == -1))
    {
        printf("Ошибка!\nМожно вводить только числа.");
        (*coeff).is_int = 0;
    }
    else if (i == 10 && ch != '\n')
    {
        cleaning_buffer(); /*Очистка буффера ввода*/
        printf("Можно вводить не более десяти символов!");
        (*coeff).is_int = 0;
    }
    else
    {
        entrance_data[i] = '\0';
        char* endptr = NULL;
        const int num = strtol(entrance_data, &endptr, 10);
        if (*endptr == '\0') {
            (*coeff).is_int = 1;
            (*coeff).num = num;
        }
        else
        {
            printf("Ошибка!\nМожно вводить только натуральные числа.");
            (*coeff).is_int = 0;
        }
    }
}


//Очистка буффера ввода
void cleaning_buffer()
{
    int ch = 0;
    while ((ch = getchar()) != '\n' && ch != EOF) {}
}


//Функция для считывания целых чисел
void entering_int_numbers(int* const number, const bool_entering_words where_called, const int how_much_called)
{
    assert(number != NULL);

    const char* entering_words = 0;
    struct in_data_int follow_eq;
    do
    {
        follow_eq.is_int = 0;
        follow_eq.num = -1;
        if (where_called == BOOL_ROW_WORDS)
        {
            entering_words = ROW_WORDS;
            printf(entering_words);
        }
        else if (where_called == BOOL_LINES_WORDS)
        {
            entering_words = LINES_WORDS;
            printf("%s%d строки: ", entering_words, how_much_called);
        }
        else if (where_called == BOOL_COLUMN_WORDS)
        {
            entering_words = COLUMN_WORDS;
            printf("%s%d: ", entering_words, how_much_called);
        }
        scan_individ(&follow_eq); /*Считывание чисел int*/
        if (follow_eq.is_int != 0)
        {
            if (follow_eq.num > 0)
                *number = follow_eq.num;
        }
    } while (follow_eq.is_int == 0 || entering_addit_cond(where_called, follow_eq.num) == 0);
}


//Дополнительные условия при вводе
bool entering_addit_cond(const int where_called, const int numb)
{
    if (where_called == BOOL_ROW_WORDS || where_called == BOOL_LINES_WORDS)
    {
        if (numb <= 0)
            printf("Ошибка!\nМожно вводить только натуральные числа.");
        return (numb > 0);
    }
    else if (where_called == BOOL_COLUMN_WORDS)
        return 1;
    else
        return 0;
}


//Функция для распечатки массива
void print_mass(int** const data, const int size_x)
{
    assert(data != 0);

    for (int i = 0; i < size_x; i++)
    {
        for (int j = 0; j < data[size_x][i]; j++)
        {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}


//Ввод матрицы
int entering_matrix(int*** data)
{
    int quant_rows = 0;
    entering_int_numbers(&quant_rows, BOOL_ROW_WORDS, 1);
    *data = (int**)calloc(quant_rows + 1, sizeof(int*));
    (*data)[quant_rows] = (int*)(calloc(quant_rows, sizeof(int)));
    for (int i = 0; i < quant_rows; i++)
    {
        int quant_columns = 0;
        entering_int_numbers(&quant_columns, BOOL_LINES_WORDS, i + 1);
        (*data)[i] = (int*)(calloc(quant_columns, sizeof(int)));
        (*data)[quant_rows][i] = quant_columns;
        for (int j = 0; j < quant_columns; j++)
        {
            entering_int_numbers(&((*data)[i][j]), BOOL_COLUMN_WORDS, j + 1);
        }
    }
    return quant_rows;
}


//Очистка динамической памяти
void mipt_cleaning(int*** data, const int quant_rows_0, const int quant_rows_1)
{
    assert(data != NULL);

    int quant_rows;
    for (int i = 0; i < 2; i++)
    {
        if (i == 0)
            quant_rows = quant_rows_0;
        else if (i == 1)
            quant_rows = quant_rows_1;
        for (int j = 0; j < quant_rows; j++)
        {
            free(data[i][j]);
        }
    }
    free(data);
}
