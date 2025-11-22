#include <stdio.h>
#include <string.h>
#include <time.h>
#include "head.h"
#define NUMARRAY 4
#define LEN1 10
#define LEN2 1000
#define LEN3 10000
#define LEN4 100000

struct data {
    char name_func[20];
    double time;
    long int len_array;
};

int* get_array_rand(int size) {
    int *array = (int *)malloc(size * sizeof(int));
    if (!array){
        printf("Ошибка в выдлении памяти рандомного массива\n");
        exit(1);
    }
    for (int i = 0; i < size; i++){
        array[i] = rand();
    }
    return array;
}

int* get_clone_array(int* source_array, int size) {
    int* clone_array = (int*)malloc(size * sizeof(int));
    if (clone_array == NULL) {
        return NULL;
    }
    //Клонирование основного массива
    memcpy(clone_array, source_array, size * sizeof(int));
    return clone_array;
}

long double get_time_sort(int *array, int size, void (*sort_type)(int*, int)){
    clock_t start = clock();
    //определённая сортировка

    sort_type(array, size);

    clock_t end = clock();
    long double seconds = (long double)(end - start) / CLOCKS_PER_SEC;
    return seconds;
}

void get_tabl(struct data *res, int size){
    char str[45];
    int length = sizeof(str) - 1;
    memset(str, '-', length);
    str[length] = '\0';

    printf("%s\n", str);
    printf("| %-16s | %-8s | %-8s |\n", "Name Sort", "len_array", "Time");
    printf("%s\n", str);

    for (int i = 0; i < size; i++) {
        //Первая сортировка
        if (strcmp(res[i].name_func, "Bubble Sort        ") == 0) {
            printf("| %-16s |", "Bubble Sort");
            printf("%-10ld | %-8.5lf |\n", res[i].len_array, res[i].time);
            printf("%s\n", str);
        }   
        //Вторая
        if (strcmp(res[i].name_func, "Insertion Sort     ") == 0) {
            printf("| %-16s |", "Insertion Sort");
            printf("%-10ld | %-8.5lf |\n", res[i].len_array, res[i].time);
            printf("%s\n", str);
        }
        //Третья
        if (strcmp(res[i].name_func, "MergeSort          ") == 0) {
            printf("| %-16s |", "MergeSort");
            printf("%-10ld | %-8.5lf |\n", res[i].len_array, res[i].time);
            printf("%s\n", str);
        }
    }
    
}

int main() {
    //Инициализация переменных времени, кол-во перестановок, массива функций
    long double time;
    struct data result[12];
    //Создание массива длин главных массивов и их самих
    long int size_array[NUMARRAY] = {LEN1, LEN2, LEN3, LEN4};
    int** main_array =(int**)malloc(NUMARRAY * sizeof(int*));
    if (!main_array) {
        printf("Ошибка выделения памяти\n");
        exit(1);
    }

    for (int i = 0; i < NUMARRAY; i++) {
        main_array[i] = get_array_rand(size_array[i]);
        if (!main_array[i]) {
        printf("Ошибка выделения памяти\n");
        exit(1);
        }
    }

    //Проверка всех массивов
    int id_in_result = 0;
    for (int i = 0; i < NUMARRAY; i++) {
        int *clone = get_clone_array(main_array[i], size_array[i]);
        if (!clone) {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }
        time = get_time_sort(clone, size_array[i], &bubble_sort);
        strcpy(result[id_in_result].name_func, "Bubble Sort        ");
        result[id_in_result].time = time;
        result[id_in_result].len_array = size_array[i];
        id_in_result++;
        free(clone);



        clone = get_clone_array(main_array[i], size_array[i]);
        if (!clone) {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }
        time = get_time_sort(clone, size_array[i], &insertion_sort);
        strcpy(result[id_in_result].name_func, "Insertion Sort     ");
        result[id_in_result].time = time;
        result[id_in_result].len_array = size_array[i];
        id_in_result++;
        free(clone);


        
        clone = get_clone_array(main_array[i], size_array[i]);
        if (!clone) {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }
        time = get_time_sort(clone, size_array[i], &sort_array_merge);
        strcpy(result[id_in_result].name_func, "MergeSort          ");
        result[id_in_result].time = time;
        result[id_in_result].len_array = size_array[i];
        id_in_result++;
        free(clone);

    }

    //Вывод данных
    get_tabl(result, 12);

    //отчистка памяти
    for (int i = 0; i < NUMARRAY; i++) {
        free(main_array[i]);
    }
    free(main_array);
    return 0;
}
