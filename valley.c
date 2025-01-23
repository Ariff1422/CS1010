/**
 * CS1010 Semester 1 AY24/25
 * Exercise 6: Valley
 *
 * @file: valley.c
 * @author: Ariff Muhammed (Group B06)
 */
#include "cs1010.h"
long find_target(long list[], size_t i, size_t j)
{
  size_t mid = (i + j) / 2;
  if (mid == 0 || mid == j) {
    return list[mid];
  }
  if (list[mid] < list[mid + 1] && list[mid - 1] > list[mid]) {
    return list[mid];
  }
  if (list[mid] > list[mid + 1] && list[mid] < list[mid - 1]) {
    return find_target(list, mid + 1, j);
  }
  return find_target(list, i, mid - 1);
}

int main()
{
  size_t n = cs1010_read_size_t();
  long *list = cs1010_read_long_array(n);
  if (list == NULL) {
    cs1010_println_string("Memory allocation failed");
    free(list);
    return 1;
  }
  cs1010_println_long(find_target(list, 0, n - 1));
  free(list);
}
