/**
 * CS1010 Semester 1 AY24/25
 * Exercise 7: maze
 *
 * @file: maze.c
 * @author: Ariff Muhammed (Group B06)
 */
#include "cs1010.h"
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL '#'
#define USER '@'

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

/**
 * Print one row of the maze to the screen (with colors)
 *
 * @param[in] maze_row The 1D array representing a row of maze.
 */
void print_maze_row_with_color(char *maze_row)
{
  long l = (long)strlen(maze_row);
  for (long j = 0; j < l; j++) {
    if (maze_row[j] == EMPTY) {
      cs1010_print_string(BLUE);
    } else if (maze_row[j] == USER) {
      cs1010_print_string(RED);
    } else {
      cs1010_print_string(YELLOW);
    }
    putchar(maze_row[j]);
  }
  cs1010_println_string("");
  cs1010_print_string(RESET);
}

/**
 * Print the maze to the screen.
 *
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long nrows, long steps)
{
  if (isatty(fileno(stdout))) {
    cs1010_clear_screen();
  }
  for (long i = 0; i < nrows; i += 1) {
    if (!isatty(fileno(stdout))) {
      cs1010_println_string(maze[i]);
    } else {
      print_maze_row_with_color(maze[i]);
    }
  }
  cs1010_println_long(steps);
  if (isatty(fileno(stdout))) {
    usleep(100 * 1000);
  }
}

bool visit(char **maze, bool **visited, long x, long y, long m, long n,
           long *steps)
{
  /*
   if (x < 0 || x >= m|| y < 0|| y >= n || maze[x][y] == WALL || visited[x][y])
   { return false;
   }
   if (x == 0 || x == m - 1 || y == 0 || y == n - 1) {
     maze[x][y] = USER;
     (*steps)++;
     print_maze(maze, m, *steps);
     maze[x][y] = EMPTY;
     return true;
   }


   visited[x][y] = true;
   maze[x][y] = USER;
   //(*steps)++;
   print_maze(maze, m, *steps);
   (*steps)+= 1;
   //maze[x][y] = EMPTY;
   //visited[x][y] = false;


   long const dx[] = {-1, 0, 1, 0};
   long const dy[] = {0, 1, 0, -1};

   for (long i = 0; i < 4; i += 1) {
     long new_x = x + dx[i];
     long new_y = y + dy[i];
     if (new_x >= 0 && new_x < m && new_y >= 0 && new_y < n &&
         maze[new_x][new_y] == EMPTY) {
       maze[x][y] = USER;
       print_maze(maze,m,(*steps) + 1);
       if (visit(maze, visited, new_x, new_y, m, n, steps)) {
         //visited[new_x][new_y] = false;
         return true;
       }
     }
   }

   maze[x][y] = EMPTY;
   visited[x][y] = false;
   (*steps)++;
   print_maze(maze, m, *steps);
   //visited[x][y] = true;
   //maze[x][y] = EMPTY;
   return false;
   */
  if (x == 0 || x == m - 1 || y == 0 || y == n - 1) {
    maze[x][y] = USER;
    print_maze(maze, m, *steps);
    maze[x][y] = EMPTY;
    return true;
  }

  visited[x][y] = true;

  if (x > 0 && maze[x - 1][y] == EMPTY && !visited[x - 1][y]) {
    maze[x][y] = USER;
    print_maze(maze, m, (*steps)++);
    maze[x][y] = EMPTY;
    if (visit(maze, visited, x - 1, y, m, n, steps)) {
      return true;
    }
  }

  if (y < n - 1 && maze[x][y + 1] == EMPTY && !visited[x][y + 1]) {
    maze[x][y] = USER;
    print_maze(maze, m, (*steps)++);
    maze[x][y] = EMPTY;
    if (visit(maze, visited, x, y + 1, m, n, steps)) {
      return true;
    }
  }

  if (x < m - 1 && maze[x + 1][y] == EMPTY && !visited[x + 1][y]) {
    maze[x][y] = USER;
    print_maze(maze, m, (*steps)++);
    maze[x][y] = EMPTY;
    if (visit(maze, visited, x + 1, y, m, n, steps)) {
      return true;
    }
  }

  if (y > 0 && maze[x][y - 1] == EMPTY && !visited[x][y - 1]) {
    maze[x][y] = USER;
    print_maze(maze, m, (*steps)++);
    maze[x][y] = EMPTY;
    if (visit(maze, visited, x, y - 1, m, n, steps)) {
      return true;
    }
  }

  maze[x][y] = USER;
  print_maze(maze, m, (*steps)++);
  maze[x][y] = EMPTY;

  return false;
}

int main()
{
  long m = cs1010_read_long();
  long n = cs1010_read_long();
  char **maze = calloc((size_t)m, sizeof(char *));
  bool **visited = calloc((size_t)m, sizeof(bool *));
  if (maze == NULL || visited == NULL) {
    free(maze);
    free(visited);
    return 1;
  }
  long start_x;
  long start_y;
  for (long i = 0; i < m; i += 1) {
    maze[i] = cs1010_read_line();
    visited[i] = calloc((size_t)n, sizeof(bool));
    if (maze[i] == NULL || visited[i] == NULL) {
      for (long j = 0; j <= i; j += 1) {
        free(maze[j]);
        free(visited[j]);
      }
      free(maze);
      free(visited);
      return 1;
    }
    size_t line_length = strlen(maze[i]);
    if (maze[i][line_length - 1] == '\n') {
      maze[i][line_length - 1] = '\0';
    }
    for (long j = 0; j < n; j += 1) {
      if (maze[i][j] == USER) {
        start_x = i;
        start_y = j;
      }
    }
  }
  long steps = 0;
  visit(maze, visited, start_x, start_y, m, n, &steps);
  for (long i = 0; i < m; i += 1) {
    free(maze[i]);
    free(visited[i]);
  }
  free(maze);
  free(visited);
}
