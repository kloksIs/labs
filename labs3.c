#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define LIM_NUM 2000000000 //По модулю
#define LIM_LEN_NUM 10 //Зависит от LIM_NUM
#define SWAP_STR 4 //Строка с которой меняем и считаем сумму
#define ADD_STR 2 //Доп. строка подсчёта суммы
#define N 2 //Длина массива с id строк суммы

//Просмотр превышения лимита по модулю. Если превышен, то 1
int exceed_limit(int Num){
    if ((Num >= LIM_NUM)||(Num <= -LIM_NUM)){
        return 1;
    }
    else return 0;
}
//Получаем число чисел в строке, если ошибка, то 0
int get_len_str(FILE *f){
    short in_num = TRUE;
    int count = 1;
    char c = fgetc(f);
    char prev_c = EOF;
    //Проверка что первый символ цифра или минус
    if ( ((c < '0') || (c > '9')) && (c != '-')){
        printf("Первый символ не число в строке №");
        return 0;
    }

    //Проход по строке и счёт кол-ва чисел
    while ((c != '\n') && (c != EOF)){
        if (exceed_limit(count)){
            printf("Превышено допустимое число чисел в строке №");
            return 0;
        }
        if ((c >= '0') && (c <= '9')){
            if (!in_num){
                count++;
            }
            in_num = TRUE;
        }
        else if (c == '-'){
            if (prev_c != ' '){
                printf("Не корректная запись с минусом №");
                return 0;
            }
        }
        else if (c == ' '){
            if (prev_c == ' '){
                printf("Лишний пробел в строке №");
                return 0;
            }
            in_num = FALSE;
        }
        else {
            printf("Недопустимый символ в строке №");
            return 0;
        }
        prev_c = c;
        c = fgetc(f);
    }
    return count;
}
//Получаем и выводим кол-во столбцов и строк, если ошибка, то 0
int get_size_matrix(FILE *f, int *wid, int *len){
    int check_len = 0; 
    //Проверяем, чтобы строки были одинаковой длины и без ошибок
    while (!feof(f)){
        if (exceed_limit(*wid)){
            printf("Превышено допустимое число строк\n");
            return 0;
        }

        (*wid)++;
        check_len = get_len_str(f);
        if (check_len == 0){
            printf("%d\n", *wid);
            return 0;
        }
        if ((check_len != *len)){
            if (*wid != 1){
                printf("Строка №%d имеет другую размерность. Матрица некорректна\n", *wid);
                return 0;
            }
            else *len = check_len;
        }
    }
    return 1;
}
//Освобождение памяти всей матрицы
int free_matrix_memory(int **Matrix_memory,int str){
    for (int i = 0; i < str; i++){
        free(Matrix_memory[i]);
    }
    free(Matrix_memory);
}
//Поменять местами 1 и 2 строчки
void swap_str(int *str_el1, int *str_el2, int stb){
    int a;
    for (int i = 0; i < stb; i++){
        a = str_el1[i];
        str_el1[i] = str_el2[i];
        str_el2[i] = a;
    }
}
int main(int argc, char **argv){
    //Открытие и проверка файла
    if (argc != 2){
        printf("Заданы не верные аргументы\n");
        return 1;
    }
    if (strlen(argv[1]) > 100){
        printf("У файла слишком большое название");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (!file){
        printf("Error occurred while opening %s\n", argv[1]);
        return 1;
    }

    //Просмотр и сбор информации о матрице
    int str = 0, stb = 0;
    if (!get_size_matrix(file, &str, &stb)){
        printf("Ошибка чтения матрицы на этапе подготовки. Убедитесь, что у строк одинаковый размер. ");
        printf("Количество строк, столбцов и элементы матрицы не должны превышать %d\n", LIM_NUM);
        return 1;
    }
    if (str < 4){
        printf("Матрица не соответствует заданию, т.к. строк меньше 4\n");
        return 1;
    }


    //Выделение памяти и получение эл-ов матрицы
    rewind(file);
    int **Matrix = (int**)malloc(sizeof(int *)*str);
    if (!Matrix){
        printf("Ошибка выделения памяти\n");
        return 1;
    }
    for (int i = 0; i < str; i++) {
        Matrix[i] = (int *)malloc(sizeof(int)*stb);
        if (!Matrix[i]){
            printf("Ошибка выделения памяти\n");
            return 1;
        }
        for (int j = 0; j < stb; j++){
            if (fscanf(file,"%d" ,&Matrix[i][j]) == 0){
                printf("Ошибка чтения матрицы на этапе приведение элементов в число\n");
                free_matrix_memory(Matrix, str);
                return 1;
            }
        }  
    }  

    //Основная работа
    int min_el = Matrix[0][0];
    int id_min_el_str = 0;
    for (int i = 0; i < str; i++){
        for (int j = 0; j < stb; j++){
            if (Matrix[i][j] < min_el){
                min_el = Matrix[i][j];
                id_min_el_str = i;
            } 
        }
    }
    swap_str(Matrix[SWAP_STR-1], Matrix[id_min_el_str], stb);
    int result = 0;
    int arr_str[N] = {ADD_STR-1, SWAP_STR-1};
    for (int i = 0; i < N; i++){
        for (int j = 0; j < stb; j++){
            result = result + Matrix[arr_str[i]][j];
        }
    }
    //Вывод информации
    printf("\n");
    for (int i = 0; i < str; i++){
        for (int j = 0; j < stb; j++){
            printf("%d ", Matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nCумма 2 и 4 строчки = %d\n", result);
    
    //Отчистка памяти
    free_matrix_memory(Matrix, str);
    fclose(file);
    return 0;
}
