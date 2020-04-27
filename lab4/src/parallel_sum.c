#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>


#include "utils.h"
#include "Sum.h"

#include <sys/time.h>

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

  uint32_t threads_num = atoi(argv[1]);
  uint32_t array_size = atoi(argv[2]);
  uint32_t seed = atoi(argv[3]);
  pthread_t threads[threads_num];
  if (threads_num <= 0 || seed <= 0 || array_size <= 0) {
    printf("Usage: %s threads_num \"num\" seed \"num\" array_size \"num\" \n",
           argv[0]);
    return 1;
  }
  /*
   * TODO:
   * your code here
   * Generate array here
   */

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  struct SumArgs args[threads_num];
  uint32_t i;
  for (i = 0; i < threads_num; i++){
      args[i].begin=i*array_size/threads_num;
      args[i].end=(i+1)*array_size/threads_num;
      if(i==threads_num-1) args[i].end+=array_size%threads_num;
      args[i].array=array;
  }
  for (i = 0; i < threads_num; i++) {
    if (pthread_create(&threads[i], NULL, ThreadSum, (void *)&args[i])) {
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

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;
  free(array);
  printf("Total: %d\n", total_sum);
  printf("Elapsed time: %fms\n", elapsed_time);
  return 0;
}
