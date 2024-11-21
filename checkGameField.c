#include <stdio.h>
#include <stdbool.h>

void print_win_or_lose(const char current_symbol, const char player_symbol)
{
  current_symbol == player_symbol ? printf("You WIN!\n") : printf("You lose...\n");
}

bool check_game_field_horizon_vertical(const char (*game_field)[3], const char row, const char player_symbol, void (*print_game_field)(const char (*game_field)[3]))
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
        print_game_field(game_field);
        print_win_or_lose(current_symbol, player_symbol);
        return true;
      }
    }
  }

  return false;
}

bool check_game_field_left_to_right(const char (*game_field)[3], const char player_symbol, void (*print_game_field)(const char (*game_field)[3]))
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
      print_game_field(game_field);
      print_win_or_lose(current_symbol, player_symbol);
      return true;
    }
  }

  return false;
}

bool check_game_field_right_to_left(const char (*game_field)[3], const char player_symbol, void (*print_game_field)(const char (*game_field)[3]))
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
      print_game_field(game_field);
      print_win_or_lose(current_symbol, player_symbol);
      return true;
    }
  }

  return false;
}