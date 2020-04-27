#include "Sum.h"

int Sum(const struct SumArgs *args) {
  int i,sum = 0;
  // TODO: your code here 
  for (i = args->begin; i < args->end; i++){
     sum+=args->array[i];
  }
  return sum;
}