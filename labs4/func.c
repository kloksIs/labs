#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"
#define FALSE 0
#define TRUE 1

void swap(int *el1, int *el2) {
    int temp = *el2;
    *el2 = *el1;
    *el1 = temp;
}

void bubble_sort(int *array, int size) {
    int flag_swap;
    for (int j = 1; j < size; j++) {
        flag_swap = FALSE;
        for (int i = 0; i < size - j; i++) {
            if (array[i] > array[i+1]) {
                swap(&array[i], &array[i+1]);
                flag_swap = TRUE;
            }
        }
        if (!flag_swap) {
            break;
        }
    }
}

void insertion_sort(int *array, int size) {
    int key, j;
    for (int i = 1; i < size; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && key < array[j]) {
            array[j+1] = array[j];
            j = j - 1;
        }
        array[j+1] = key;
    }
    
}
static void merge(int *array, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Используем динамическое выделение памяти для временных массивов L и R
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));
    if (L == NULL || R == NULL) exit(1); // Обработка ошибки

    // Копируем данные
    memcpy(L, array + left, n1 * sizeof(int));
    memcpy(R, array + mid + 1, n2 * sizeof(int));

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k++] = L[i++];
        } else {
            array[k++] = R[j++];
        }
    }
    while (i < n1) array[k++] = L[i++];
    while (j < n2) array[k++] = R[j++];

    free(L);
    free(R);
}

static void merge_sort_recursive(int *array, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    merge_sort_recursive(array, left, mid);
    merge_sort_recursive(array, mid + 1, right);
    merge(array, left, mid, right);
}

void sort_array_merge(int *array, int size) {
    if (array == NULL || size <= 1) {
        return;
    }
    // Запускаем приватный рекурсивный алгоритм для всего массива
    merge_sort_recursive(array, 0, size - 1);
}
