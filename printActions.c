#include <stdio.h>

void print_welcome(void)
{
  putchar('\n');
  puts("   W E L C O M E   ");
  printf(" _____ _____ _____\n|     |     |     |\n|  T  |  I  |  C  |\n|_____|_____|_____|\n|     |     |     |\n|  T  |  A  |  C  |\n|_____|_____|_____|\n|     |     |     |\n|  T  |  O  |  E  |\n|_____|_____|_____|\n\n");
}

void print_separator(void)
{
  puts("<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>\n");
}

void print_game_field(const char (*game_field)[3])
{
  printf(" _____ _____ _____\n|     |     |     |\n|  %c  |  %c  |  %c  |\n|_____|_____|_____|\n|     |     |     |\n|  %c  |  %c  |  %c  |\n|_____|_____|_____|\n|     |     |     |\n|  %c  |  %c  |  %c  |\n|_____|_____|_____|\n\n", game_field[0][0], game_field[0][1], game_field[0][2], game_field[1][0], game_field[1][1], game_field[1][2], game_field[2][0], game_field[2][1], game_field[2][2]);
  print_separator();
}

void print_made_moves(const char *who, const char row, const char col)
{
  printf("The %s made a move: row - %d, col - %d.\n", who, row, col);
}