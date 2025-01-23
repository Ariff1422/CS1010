/**
 * CS1010 Semester 1 AY24/25
 * Exercise 7: Sudoku
 *
 * @file: sudoku.c
 * @author: Ariff Muhammed (Group B06)
 */
#include "cs1010.h"
#include <unistd.h>

#define EMPTY '.'

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void print_row_file(char *row)
{
  for (int i = 0; i < 9; i += 1) {
    putchar(row[i]);
    if (i == 2 || i == 5) {
      cs1010_print_string("│");
    }
  }
  putchar('\n');
}

void print_row_screen(char *row)
{
  for (int i = 0; i < 9; i += 1) {
    if (row[i] == EMPTY) {
      cs1010_print_string(YELLOW);
      putchar(row[i]);
      cs1010_print_string(RESET);
    } else {
      putchar(row[i]);
    }
    if (i == 2 || i == 5) {
      cs1010_print_string(RED);
      cs1010_print_string("│");
      cs1010_print_string(RESET);
    }
  }
  putchar('\n');
}

void print_sudoku_file(char puzzle[9][9])
{
  for (int i = 0; i < 9; i += 1) {
    print_row_file(puzzle[i]);
    if (i == 2 || i == 5) {
      cs1010_println_string("───┼───┼───");
    }
  }
}

void print_sudoku_screen(char puzzle[9][9])
{
  cs1010_clear_screen();
  for (int i = 0; i < 9; i += 1) {
    print_row_screen(puzzle[i]);
    if (i == 2 || i == 5) {
      cs1010_print_string(RED);
      cs1010_println_string("───┼───┼───");
      cs1010_print_string(RESET);
    }
  }
  usleep(10 * 1000);
}

void print_sudoku(char puzzle[9][9])
{
  if (isatty(fileno(stdout))) {
    print_sudoku_screen(puzzle);
  } else {
    print_sudoku_file(puzzle);
  }
}
/*long* find_start_end_pt(long res[2], long number){
  if (number < 3){
    res[1] = 2;
  }
  else if (number < 6){
    res[0] = 3;
    res[1] = 5;
  }
  else{
    res[0] = 6;
    res[1] = 8;
  }
  return res;
}*/

bool is_valid_placement(char puzzle[9][9], long row, long column, char current)
{
  for (long i = 0; i < 9; i += 1) {
    if (puzzle[i][column] == current) {
      return false;
    }
    if (puzzle[row][i] == current) {
      return false;
    }
    if (puzzle[3 * (row / 3) + i / 3][3 * (column / 3) + i % 3] == current) {
      return false;
    }
  }
  /*long rowbox = row / 3;
  long colbox = column / 3;
  for (long i = rowbox * 3 - 1; i <= (rowbox) * 3 + 2; i += 1){
    for (long j = colbox * 3 - 1; i <= (colbox) * 3 + 2; j += 1){
      if (puzzle[i][j] == current){
        return false;
      }
    }
  }*/
  return true;
} /*
 bool solve_sudoku(char puzzle[9][9]){
   for (long row = 0; row < 9; row += 1){
     for (long col = 0; col < 9; col += 1){
       if (puzzle[row][col] != EMPTY){
         print_sudoku(puzzle);
       }
       if (puzzle[row][col] == EMPTY){

         for (char try = '1'; try <= '9'; try += 1){
           if (is_valid_placement(puzzle, row, col, try)){
             puzzle[row][col] = try;
             print_sudoku(puzzle);
             if (solve_sudoku(puzzle)){
               //print_sudoku(puzzle);
               return true;
             }
             puzzle[row][col] = EMPTY;
             print_sudoku(puzzle);
           }
         }
         //print_sudoku(puzzle);
       return false;
      }
      //print_sudoku(puzzle);
     }
   }
   print_sudoku(puzzle);
   return true;
 }
 */
bool solve_sudoku(char puzzle[9][9], long row, long col)
{
  print_sudoku(puzzle);
  if (col == 9) {
    // print_sudoku(puzzle);
    row += 1;
    col = 0; // Move to next row
  }
  if (row == 9) {
    return true; // Solved entire puzzle
  }

  if (puzzle[row][col] != EMPTY) {
    // print_sudoku(puzzle);
    return solve_sudoku(puzzle, row, col + 1); // Move to next column
  }

  for (char try = '1'; try <= '9'; try += 1) {
    if (is_valid_placement(puzzle, row, col, try)) {
      puzzle[row][col] = try;
      // print_sudoku(puzzle);

      if (solve_sudoku(puzzle, row, col + 1)) {
        // print_sudoku(puzzle);
        return true;
      }

      puzzle[row][col] = EMPTY; // Undo the move
      // print_sudoku(puzzle);
    }
  }

  return false;
}
int main()
{
  char puzzle[9][9];

  for (size_t i = 0; i < 9; i += 1) {
    char *line = cs1010_read_line();
    if (line == NULL) {
      cs1010_println_string("Memory allocation failed");
      return 1;
    }
    for (size_t j = 0; j < 9; j += 1) {
      if (line[j] == '\n') {
        break;
      }
      puzzle[i][j] = line[j];
    }
    free(line);
  }
  // print_sudoku(puzzle);
  if (solve_sudoku(puzzle, 0, 0)) {
    print_sudoku(puzzle);
  } else {
    cs1010_println_string("no solution");
  }
}
