/**
 * CS1010 Semester 1 AY24/25
 * Exercise 6: Inversion
 *
 * @file: inversion.c
 * @author: Ariff Muhammed (Group B06)
 */
#include "cs1010.h"

size_t find_mid(long *list, size_t(n))
{
  if (n == 1) {
    return 0;
  }
  for (size_t i = 0; i < n - 1; i += 1) {
    if (list[i] > list[i + 1]) {
      return i;
    }
  }
  return n - 1;
}
size_t count_inversions(long *list, size_t n)
{
  size_t k = find_mid(list, n);
  size_t count = 0;
  if (k == 0) {
    return (n * (n - 1)) / 2;
  }
  if (k == n - 1) {
    return 0;
  }
  size_t i = 0;
  size_t j = n - 1;
  while (k < j) {
    if (list[j] > list[i]) {
      i += 1;
    } else {
      count += (j - i);
      j -= 1;
    }
  }
  return count;
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
  cs1010_println_size_t(count_inversions(list, n));
  free(list);
  return 0;
}
