#include <stdio.h>

void players_move_error_message(const char is_row, const char is_less)
{
  printf("The %s index you entered is %s than possible.\n", !is_row ? "ROW" : "COLUMN", !is_less ? "LESS" : "GREATER");
}

void check_players_move_error(const char (*game_field)[3], const char player_row, const char player_col, const char symbol_o, const char symbol_x)
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

  if (game_field[player_row - 1][player_col - 1] == symbol_o || game_field[player_row - 1][player_col - 1] == symbol_x)
  {
    printf("The field at these coordinates is already occupied.\n");
  }
}