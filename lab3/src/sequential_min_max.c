#include <stdio.h>
#include <stdlib.h>

#include "find_min_max.h"
#include "utils.h"
// Программа принимает два аргумента - зерно и размер массива.
// Массив заполняется случайными числами и в нем ищется минимальное и максимальное целые числа.
int main(int argc, char **argv) {
  if (argc != 3) {    // если аргумента не два (+ имя функции тоже аргумент)
    printf("Usage: %s seed arraysize\n", argv[0]);
    return 1;
  }

  int seed = atoi(argv[1]);
  if (seed <= 0) { // если зерно не положительное число
    printf("seed is a positive number\n");
    return 1;
  }

  int array_size = atoi(argv[2]);
  if (array_size <= 0) {  // если размер массива не положительное число
    printf("array_size is a positive number\n");
    return 1;
  }
  // выделяется память под массив указанной размерности
  int *array = malloc(array_size * sizeof(int));
  // создается массив из случайных чисел по указанным размеру массива и зерну
  GenerateArray(array, array_size, seed);
  // переменная инициализируется функцией, ищущей минимальное и максимальное числа
  struct MinMax min_max = GetMinMax(array, 0, array_size);
  free(array); // освбождение памяти

  printf("min: %d\n", min_max.min); // вывод минимального числа
  printf("max: %d\n", min_max.max);

  return 0;
}
