#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "checkGameField.c"
#include "checkPlayersMoveError.c"
#include "printActions.c"

#define SYMBOL_X 'X'
#define SYMBOL_O 'O'
#define SYMBOL_QUIT 'q'

char game_field[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
char computer_symbol;
char player_symbol;

void clear_buffer(void)
{
  unsigned int ch;

  while ((ch = getchar()) != EOF && ch != '\n')
    ;
}

char get_player_symbol(void)
{
  char symbol;

  while (1)
  {
    printf("Please select the symbol X or O: ");
    symbol = toupper(getchar());
    clear_buffer();

    if (symbol == SYMBOL_X || symbol == SYMBOL_O)
    {
      if (symbol == SYMBOL_X)
      {
        computer_symbol = SYMBOL_O;
        player_symbol = SYMBOL_X;
      }
      else
      {
        computer_symbol = SYMBOL_X;
        player_symbol = SYMBOL_O;
      }

      print_separator();
      return symbol;
    }
  }
}

char get_num(char in_num)
{
  return in_num ? rand() % in_num : in_num;
}

int main(void)
{
  srand(time(NULL));
  print_welcome();
  get_player_symbol();

  printf("Alright, now your symbol is: %c.\n\n", player_symbol);
  print_separator();

  char is_player_starts = rand() % 2;
  printf("The game starts: %s.\n\n", is_player_starts ? "Player" : "Computer");
  print_separator();

  char current_symbol;
  bool first_move = true;
  int player_row;
  int player_col;
  char moves = 0;
  char row_check = 0;
  char col_check = 1;

  while (tolower(current_symbol) != SYMBOL_QUIT)
  {

    if (!is_player_starts)
    {
      char computer_row = get_num(3);
      char computer_col = get_num(3);

      if (!first_move)
      {
        print_made_moves("PLAYER", player_row, player_col);
      }

      print_made_moves("COMPUTER", computer_row + 1, computer_col + 1);

      game_field[computer_row][computer_col] = computer_symbol;

      print_game_field(game_field);
    }
    else
    {
      printf("Enter the row and column number separated by a space: ");

      while (1)
      {
        scanf("%d %d", &player_row, &player_col);
        clear_buffer();

        if (player_row > 0 && player_row < 4 && player_col > 0 && player_col < 4 && game_field[player_row - 1][player_col - 1] == ' ')
        {
          game_field[player_row - 1][player_col - 1] = player_symbol;
          putchar('\n');
          break;
        }
        else
        {
          check_players_move_error(game_field, player_row, player_col, SYMBOL_O, SYMBOL_X);
          putchar('\n');
          printf("Please try entering other coordinates: ");
        }
      }
    }

    is_player_starts = !is_player_starts;
    moves++;

    if (first_move)
    {
      first_move = false;
    }

    if (moves > 4 && (check_game_field_horizon_vertical(game_field, row_check, player_symbol, print_game_field) || check_game_field_horizon_vertical(game_field, col_check, player_symbol, print_game_field) || check_game_field_left_to_right(game_field, player_symbol, print_game_field) || check_game_field_right_to_left(game_field, player_symbol, print_game_field)))
    {
      break;
    }
  }

  return 0;
}