/**
 * CS1010 Semester 1 AY24/25
 * Exercise 6: Sort
 *
 * @file: sort.c
 * @author: Ariff Muhammed (Group B06)
 */
#include "cs1010.h"
/*
size_t switch_index(long *list, size_t n){
  for (size_t i = n - 1; i >= 0; i -= 1){
    if (list[i] < list[i - 1]){
      return i;
    }
  }
  return -1;
}*/

/*void insert(long *list, size_t curr){
  size_t i = curr;
  long temp = list[curr];
  while (i >= 1 && temp <list[i - 1]){
    a[i] = a[i - 1];
    i -= 1;
  }
  a[i] = temp;
}*/

/*void insertion_sort(size_t n, long *list){
  for (size_t curr = 1; curr < n; curr += 1){
    insert(list, curr);
  }
}*/

/*void counting_sort(size_t n, const long in[], long out[], long max){
  size_t *freq = calloc((size_t)max + 1,sizeof(size_t));
  for (size_t i = 0; i < n; i += 1){
    freq[in[i]] += 1;
  }
  size_t outpos = 0;
  for (long i = 0; i <= max; i += 1){
    for (size_t j = outpos; j < outpos + freq[i]; j += 1){
      out[j] = i;
    }
    outpos += freq[i];
  }
  free(freq);
}
*/

void sort(size_t n, const long list[], long out[])
{
  size_t i = 0;
  size_t j = n - 1;
  size_t k = n - 1;
  while (i <= j) {
    if (list[j] > list[i]) {
      out[k] = list[j];
      k -= 1;
      j -= 1;
    } else if (list[i] >= list[j]) {
      out[k] = list[i];
      k -= 1;
      i += 1;
    }
    /* else{
       out[k] = list[i];
       out[k-1] = list[j];
       k -= 2;
       j -= 1;
       i += 1;
     }*/
  }
}

int main()
{
  size_t n = cs1010_read_size_t();
  long *list = cs1010_read_long_array(n);

  /*long max = 0;
  if (list[0] > list[n - 1]){
    max = list[0];
  }else{
    max = list[n - 1];
  }*/
  long *sorted_list = calloc(n, sizeof(long));
  if (sorted_list == NULL) {
    return 1;
  }
  sort(n, list, sorted_list);
  for (size_t i = 0; i < n; i += 1) {
    cs1010_println_long(sorted_list[i]);
  }
  free(sorted_list);
  free(list);
  return 0;
}
