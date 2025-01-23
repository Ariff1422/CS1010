/**
 * CS1010 Semester 1 AY24/25
 * Exercise 8: Digits
 *
 * @file: digits.c
 * @author: Ariff Muhammed (Group B06)
 */

#include "cs1010.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5
#define MAX 999999

typedef struct {
  long label;
  char image[NROWS][NCOLS + 1];
} Digit;

typedef struct {
  long label;
  long distance;
} Neighbor;

long calculate_distance(const Digit *a, const Digit *b)
{
  long distance = 0;
  for (long i = 0; i < NROWS; i++) {
    for (long j = 0; j < NCOLS; j++) {
      if (a->image[i][j] != b->image[i][j]) {
        distance += 1;
      }
    }
  }
  return distance;
}

/*void find_k_nearest_neighbors(const Digit *test_digit, const Digit *train_set,
long train_count, Neighbor neighbors[]) { for (long i = 0; i < K; i+=1) {
        neighbors[i].label = -1;
        neighbors[i].distance = MAX;
    }

    for (long i = 0; i < train_count; i+=1) {
        long distance = calculate_distance(test_digit, &train_set[i]);

        for (long j = 0; j < K; j++) {
            if (distance < neighbors[j].distance ||
                (distance == neighbors[j].distance && train_set[i].label <
neighbors[j].label)) { for (long k = K - 1; k > j; k-=1) { neighbors[k] =
neighbors[k - 1];
                }
                neighbors[j].label = train_set[i].label;
                neighbors[j].distance = distance;
                break;
            }
        }
    }
}*/
void initialize_neighbors(Neighbor neighbors[], long k)
{
  for (long i = 0; i < k; i += 1) {
    neighbors[i].label = -1;
    neighbors[i].distance = MAX;
  }
}

void insert_neighbor(Neighbor neighbors[], long k, long label, long distance)
{
  for (long j = 0; j < k; j += 1) {
    if (distance < neighbors[j].distance ||
        (distance == neighbors[j].distance && label < neighbors[j].label)) {
      for (long l = k - 1; l > j; l -= 1) {
        neighbors[l] = neighbors[l - 1];
      }
      neighbors[j].label = label;
      neighbors[j].distance = distance;
      break;
    }
  }
}

void find_k_nearest_neighbors(const Digit *test_digit, const Digit *train_set,
                              long train_count, Neighbor neighbors[])
{
  initialize_neighbors(neighbors, K);

  for (long i = 0; i < train_count; i += 1) {
    long distance = calculate_distance(test_digit, &train_set[i]);
    insert_neighbor(neighbors, K, train_set[i].label, distance);
  }
}

long classify_digit(const Neighbor neighbors[])
{
  long frequency[10] = {0};
  long min_distance[10];
  for (long i = 0; i < 10; i += 1) {
    min_distance[i] = MAX;
  }

  for (long i = 0; i < K; i += 1) {
    frequency[neighbors[i].label] += 1;
    if (neighbors[i].distance < min_distance[neighbors[i].label]) {
      min_distance[neighbors[i].label] = neighbors[i].distance;
    }
  }

  long most_common = -1;
  long max_frequency = -1;
  for (long i = 0; i < 10; i += 1) {
    if (frequency[i] > max_frequency ||
        (frequency[i] == max_frequency &&
         min_distance[i] < min_distance[most_common])) {
      most_common = i;
      max_frequency = frequency[i];
    }
  }
  return most_common;
}

double compute_accuracy(long total_tests, long correct_tests)
{
  return (double)correct_tests / (double)total_tests * 100.0;
}

int main()
{
  long train_count = cs1010_read_long();
  long test_count;

  Digit *train_set = calloc((size_t)train_count, sizeof(Digit));
  for (long i = 0; i < train_count; i += 1) {
    train_set[i].label = cs1010_read_long();
    for (long j = 0; j < NROWS; j += 1) {
      scanf("%s", train_set[i].image[j]);
    }
  }

  test_count = cs1010_read_long();
  Digit *test_set = calloc((size_t)test_count, sizeof(Digit));
  for (long i = 0; i < test_count; i += 1) {
    test_set[i].label = cs1010_read_long();
    for (long j = 0; j < NROWS; j += 1) {
      scanf("%s", test_set[i].image[j]);
    }
  }

  long correct_tests = 0;
  Neighbor neighbors[K];

  for (long i = 0; i < test_count; i += 1) {
    find_k_nearest_neighbors(&test_set[i], train_set, train_count, neighbors);
    long predicted_label = classify_digit(neighbors);
    printf("%ld %ld\n", test_set[i].label, predicted_label);

    if (predicted_label == test_set[i].label) {
      correct_tests += 1;
    }
  }

  double accuracy = compute_accuracy(test_count, correct_tests);
  printf("%.4lf\n", accuracy);

  free(train_set);
  free(test_set);
  return 0;
}
