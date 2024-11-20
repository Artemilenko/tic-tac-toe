#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

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

void print_welcome(void)
{
  putchar('\n');
  puts("   W E L C O M E   ");
  printf(" _____ _____ _____\n|     |     |     |\n|  T  |  I  |  C  |\n|_____|_____|_____|\n|     |     |     |\n|  T  |  A  |  C  |\n|_____|_____|_____|\n|     |     |     |\n|  T  |  O  |  E  |\n|_____|_____|_____|\n\n");
}

void separator(void)
{
  puts("<~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~>\n");
}

void players_move_error_message(char is_row, char is_less)
{
  printf("The %s index you entered is %s than possible.\n", !is_row ? "ROW" : "COLUMN", !is_less ? "LESS" : "GREATER");
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

      separator();
      return symbol;
    }
  }
}

void print_game_field(void)
{
  printf(" _____ _____ _____\n|     |     |     |\n|  %c  |  %c  |  %c  |\n|_____|_____|_____|\n|     |     |     |\n|  %c  |  %c  |  %c  |\n|_____|_____|_____|\n|     |     |     |\n|  %c  |  %c  |  %c  |\n|_____|_____|_____|\n\n", game_field[0][0], game_field[0][1], game_field[0][2], game_field[1][0], game_field[1][1], game_field[1][2], game_field[2][0], game_field[2][1], game_field[2][2]);
  separator();
}

char get_num(char in_num)
{
  return in_num ? rand() % in_num : in_num;
}

bool is_field_valid(char symbol, char value, char index)
{
  if ((!symbol || symbol == value) && value != ' ')
  {
    symbol = value;
  }
  else
  {
    return false;
  }

  if (index == 2)
  {
    print_game_field();
    symbol == player_symbol ? printf("You WIN!\n") : printf("You lose...\n");
    return true;
  }
}

bool check_game_field_horizon_vertical(char row)
{
  char current_symbol;

  for (char row_index = 0; row_index < 3; row_index++)
  {
    current_symbol = game_field[!row ? row_index : 0][!row ? 0 : row_index];

    for (char col_index = 0; col_index < 3; col_index++)
    {
      char current_value = game_field[!row ? row_index : col_index][!row ? col_index : row_index];

      if ((!current_symbol || current_symbol == current_value) && current_value != ' ')
      {
        current_symbol = current_value;
      }
      else
      {
        break;
      }

      if (col_index == 2)
      {
        print_game_field();
        current_symbol == player_symbol ? printf("You WIN!\n") : printf("You lose...\n");
        return true;
      }
    }
  }

  return false;
}

bool check_game_field_left_to_right(void)
{
  char current_symbol = game_field[0][0];

  for (char i = 0; i < 3; i++)
  {
    char current_value = game_field[i][i];

    if ((!current_symbol || current_symbol == current_value) && current_value != ' ')
    {
      current_symbol = current_value;
    }
    else
    {
      break;
    }

    if (i == 2)
    {
      print_game_field();
      current_symbol == player_symbol ? printf("You WIN!\n") : printf("You lose...\n");
      return true;
    }
  }

  return false;
}

bool check_game_field_right_to_left(void)
{
  char current_symbol = game_field[0][2];

  for (char i = 0; i < 3; i++)
  {
    char current_value = game_field[i][2 - i];

    if ((!current_symbol || current_symbol == current_value) && current_value != ' ')
    {
      current_symbol = current_value;
    }
    else
    {
      break;
    }

    if (i == 2)
    {
      print_game_field();
      current_symbol == player_symbol ? printf("You WIN!\n") : printf("You lose...\n");
      return true;
    }
  }

  return false;
}

int main(void)
{
  srand(time(NULL));
  print_welcome();
  get_player_symbol();

  printf("Alright, now your symbol is: %c.\n\n", player_symbol);
  separator();

  char is_player_starts = rand() % 2;
  printf("The game starts: %s.\n\n", is_player_starts ? "Player" : "Computer");
  separator();

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
        printf("The PLAYER made a move: row - %d, col - %d.\n", player_row, player_col);
      }

      printf("The COMPUTER made a move: row - %d, col - %d.\n", computer_row + 1, computer_col + 1);

      game_field[computer_row][computer_col] = computer_symbol;

      print_game_field();
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
          if (player_row < 1)
          {
            players_move_error_message(0, 0);
          }
          else if (player_row > 3)
          {
            players_move_error_message(0, 1);
          }
          else if (player_col < 1)
          {
            players_move_error_message(1, 0);
          }
          else if ((player_col > 3))
          {
            players_move_error_message(1, 1);
          }

          if (game_field[player_row - 1][player_col - 1] == SYMBOL_O || game_field[player_row - 1][player_col - 1] == SYMBOL_X)
          {
            printf("The field at these coordinates is already occupied.\n");
          }

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

    if (moves > 4 && (check_game_field_horizon_vertical(row_check) || check_game_field_horizon_vertical(col_check) || check_game_field_left_to_right() || check_game_field_right_to_left()))
    {
      break;
    }
  }

  return 0;
}