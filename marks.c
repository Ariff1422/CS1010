/**
 * CS1010 Semester 1 AY24/25
 * Exercise 6: Marks
 *
 * @file: marks.c
 * @author: Ariff Muhammed (Group B06)
 */
#include "cs1010.h"
void counting_sort(size_t n, long in[], char **names)
{
  /*size_t freq[101] = {0};
  for (size_t i = 0; i < n; i += 1){
    freq[in[i]] += 1;
  }*/
  for (size_t i = 0; i <= 100; i += 1) {
    // if (freq[i] > 0){
    for (size_t j = 0; j < n; j += 1) {
      if (in[j] == (long)i) {
        cs1010_print_long(in[j]);
        cs1010_print_string(" ");
        cs1010_println_string(names[j]);
      }
    }
    //}
  }
}

int main()
{
  size_t n = cs1010_read_size_t();
  char **names = calloc(n, sizeof(char *));
  long *score = calloc(n, sizeof(long));
  if (names == NULL || score == NULL) {
    cs1010_println_string("Memory allocation failed");
    free(names);
    free(score);
    return 1;
  }

  for (size_t i = 0; i < n; i += 1) {
    names[i] = cs1010_read_word();
    score[i] = cs1010_read_long();
  }
  counting_sort(n, score, names);
  for (size_t i = 0; i < n; i += 1) {
    free(names[i]);
  }
  free(names);
  free(score);
}
