#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>


#include "utils.h"

struct SumArgs {
  int *array;
  int begin;
  int end;
};

int Sum(const struct SumArgs *args) {
  int i,sum = 0;
  // TODO: your code here 
  for (i = 0; i < sizeof(args); i++){
      if(i+1!=sizeof(args)) {
            sum = GetMinMax(array, i*array_part, (i+1)*array_part);}
        else {
            sum = GetMinMax(array, i*array_part, (i+1)*array_part+(array_size%pnum));}
  }
  return sum;
}

void *ThreadSum(void *args) {
  struct SumArgs *sum_args = (struct SumArgs *)args;
  return (void *)(size_t)Sum(sum_args);
}

int main(int argc, char **argv) {
  /*
   *  TODO:
   *  threads_num by command line arguments
   *  array_size by command line arguments
   *	seed by command line arguments
   */

  uint32_t threads_num = 0;
  uint32_t array_size = 0;
  uint32_t seed = 0;
  pthread_t threads[threads_num];

  /*
   * TODO:
   * your code here
   * Generate array here
   */

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);


  struct SumArgs args[threads_num];
  uint32_t i;
  for (i = 0; i < threads_num; i++) {
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args)) {
      printf("Error: pthread_create failed!\n");
      return 1;
    }
  }

  int total_sum = 0;
  for (i = 0; i < threads_num; i++) {
    int sum = 0;
    pthread_join(threads[i], (void **)&sum);
    total_sum += sum;
  }

  free(array);
  printf("Total: %d\n", total_sum);
  return 0;
}
