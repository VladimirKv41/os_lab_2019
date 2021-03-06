#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <getopt.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
  /*int seed = -1;
  int array_size = -1;
  int pnum = -2;*/
  int seed = 13;
  int array_size = 10;
  int pnum = 2;
  bool with_files = false;

  while (true) {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"seed", required_argument, 0, 0},
                                      {"array_size", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"by_files", no_argument, 0, 'f'},
                                      {0, 0, 0, 0}};
    /*printf("%d\n",seed);
    printf("%d\n",array_size);
    printf("%d\n",pnum);  
    seed=atoi(argv[1]);  
    array_size=atoi(argv[2]);
    pnum=atoi(argv[3]);
    printf("%d\n",seed);
    printf("%d\n",array_size);
    printf("%d\n",pnum); */                           
    int option_index = 0;
    int c = getopt_long(argc, argv, "f", options, &option_index);
    //int c = getopt_long(argc, argv, "f:012", options, &option_index);
    //c=0;
    //option_index=3;
    if (c == -1) break;
      switch (c) {
      case 0:
        switch (option_index) {
          case 0:
            seed = atoi(optarg);
            // your code here
            // error handling
            printf ("option seed with arg %d", seed);
            break;
          case 1:
            array_size = atoi(optarg);
            // your code here
            // error handling
            printf ("option array_size with arg %d", array_size);
            break;
          case 2:
            pnum = atoi(optarg);
            // your code here
            // error handling
            printf ("option pnum with arg %d", pnum);
            break;
          case 3:
            with_files = true;
            break;

          defalut:
            printf("Index %d is out of options\n", option_index);
        }
        break;
      case 'f':
        with_files = true;
        break;

      case '?':
        break;

      default:
        printf("getopt returned character code 0%o?\n", c);
    }
    break;
  }
  //printf("%d\n",optind);
  //printf("%d\n",argc);
  //optind=5;
  if (optind < argc) {
    printf("Has at least one no option argument\n");
    return 1;
  }

  if (seed == -1 || array_size == -1 || pnum == -1) {
    printf("Usage: %s --seed \"num\" --array_size \"num\" --pnum \"num\" \n",
           argv[0]);
    return 1;
  }

  int *array = malloc(sizeof(int) * array_size);
  GenerateArray(array, array_size, seed);
  int active_child_processes = 0;

  struct timeval start_time;
  gettimeofday(&start_time, NULL);
  int i;
  FILE *fp;
  int p[2];
  pipe(p);
  for (i = 0; i < pnum; i++) {
    pid_t child_pid = fork();
    if (child_pid >= 0) {
      // successful fork
      active_child_processes += 1;
      if (child_pid == 0) {
        int array_part=array_size/pnum;
        struct MinMax part_min_max;
        if(i+1!=pnum) {
            part_min_max = GetMinMax(array, i*array_part, (i+1)*array_part);}
        else {
            part_min_max = GetMinMax(array, i*array_part, (i+1)*array_part+(array_size%pnum));}
        //printf("%d\n",part_min_max.min);
        //printf("%d\n",part_min_max.max);
        // parallel somehow
        if (with_files) 
        {
          // use files here
          fp=fopen("text.txt", "a+");
          fprintf(fp, "%d\n",part_min_max.min);
          fprintf(fp, "%d\n",part_min_max.max);
          fclose(fp);

        } else 
        {
          // use pipe here
          write(p[1], &part_min_max.min, sizeof(int));
          write(p[1], &part_min_max.max, sizeof(int));
        }
        return 0;
      }

    } else {
      printf("Fork failed!\n");
      return 1;
    }
  }

  while (active_child_processes > 0) {
    // your code here
    int status;
    wait(&status);
    active_child_processes -= 1;
  }

  struct MinMax min_max;
  min_max.min = INT_MAX;
  min_max.max = INT_MIN;

  for (i = 0; i < pnum; i++) {
    int min = INT_MAX;
    int max = INT_MIN;

    if (with_files) {
      // read from files
       fp=fopen("text.txt", "r");
       fscanf(fp, "%d%d\n",&min,&max);
       //printf("%d,",min);
       //printf("%d,",max);
       fclose(fp);
    } else {
      // read from pipes
      read(p[0], &min, sizeof(int));
      read(p[0], &max, sizeof(int));
      //printf("%d,",min);
      //printf("%d,",max);
    }

    if (min < min_max.min) min_max.min = min;
    if (max > min_max.max) min_max.max = max;
  }

  struct timeval finish_time;
  gettimeofday(&finish_time, NULL);

  double elapsed_time = (finish_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_time += (finish_time.tv_usec - start_time.tv_usec) / 1000.0;

  free(array);
  printf("Min: %d\n", min_max.min);
  printf("Max: %d\n", min_max.max);
  printf("Elapsed time: %fms\n", elapsed_time);
  fflush(NULL);
  return 0;
}