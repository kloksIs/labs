#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

void bubble_sort(int *array, int size);

void insertion_sort(int *array, int size);

void sort_array_merge(int *array, int size);
#endif