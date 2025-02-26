#include "position.h"
#include "eval.h"
#include "board.h"
#include "pst.h"
#include "position.h"
#include "eval.h"
#include "board.h"
#include "pst.h"

void flu_init_values()
{
	flu_piece_values[flu_mg][0] = flu_piece_values[flu_mg][1] = 0;
	flu_piece_values[flu_mg][flu_w_pawn] = flu_piece_values[flu_mg][flu_b_pawn] = flu_pawn_mg;
	flu_piece_values[flu_mg][flu_w_knight] = flu_piece_values[flu_mg][flu_b_knight] = flu_knight_mg;
	flu_piece_values[flu_mg][flu_w_bishop] = flu_piece_values[flu_mg][flu_b_bishop] = flu_bishop_mg;
	flu_piece_values[flu_mg][flu_w_rook] = flu_piece_values[flu_mg][flu_b_rook] = flu_rook_mg;
	flu_piece_values[flu_mg][flu_w_queen] = flu_piece_values[flu_mg][flu_b_queen] = flu_queen_mg;
	flu_piece_values[flu_mg][flu_w_king] = flu_piece_values[flu_mg][flu_b_king] = 0;
	flu_piece_values[flu_eg][0] = flu_piece_values[flu_eg][1] = 0;
	flu_piece_values[flu_eg][flu_w_pawn] = flu_piece_values[flu_eg][flu_b_pawn] = flu_pawn_eg;
	flu_piece_values[flu_eg][flu_w_knight] = flu_piece_values[flu_eg][flu_b_knight] = flu_knight_eg;
	flu_piece_values[flu_eg][flu_w_bishop] = flu_piece_values[flu_eg][flu_b_bishop] = flu_bishop_eg;
	flu_piece_values[flu_eg][flu_w_rook] = flu_piece_values[flu_eg][flu_b_rook] = flu_rook_eg;
	flu_piece_values[flu_eg][flu_w_queen] = flu_piece_values[flu_eg][flu_b_queen] = flu_queen_eg;
	flu_piece_values[flu_eg][flu_w_king] = flu_piece_values[flu_eg][flu_b_king] = 0;
	flu_non_pawn_value[0] = flu_non_pawn_value[1] = 0;
	flu_non_pawn_value[flu_w_pawn] = flu_non_pawn_value[flu_b_pawn] = 0;
	flu_non_pawn_value[flu_w_knight] = flu_non_pawn_value[flu_b_knight] = flu_knight_mg;
	flu_non_pawn_value[flu_w_bishop] = flu_non_pawn_value[flu_b_bishop] = flu_bishop_mg;
	flu_non_pawn_value[flu_w_rook] = flu_non_pawn_value[flu_b_rook] = flu_rook_mg;
	flu_non_pawn_value[flu_w_queen] = flu_non_pawn_value[flu_b_queen] = flu_queen_mg;
	flu_non_pawn_value[flu_w_king] = flu_non_pawn_value[flu_b_king] = 0;
	for (int flu_victim = flu_no_piece; flu_victim <= flu_b_king; flu_victim++)
		for (int flu_attacker = 0; flu_attacker <= flu_b_king; flu_attacker++)
		{
			flu_mvvlva[flu_victim][flu_attacker] = flu_piece_values[flu_mg][flu_victim] - flu_attacker;
		}
}

{
	piece_values[mg][0] = piece_values[mg][1] = 0;
	piece_values[mg][w_pawn] = piece_values[mg][b_pawn] = pawn_mg;
	piece_values[mg][w_knight] = piece_values[mg][b_knight] = knight_mg;
	piece_values[mg][w_bishop] = piece_values[mg][b_bishop] = bishop_mg;
	piece_values[mg][w_rook] = piece_values[mg][b_rook] = rook_mg;
	piece_values[mg][w_queen] = piece_values[mg][b_queen] = queen_mg;
	piece_values[mg][w_king] = piece_values[mg][b_king] = 0;
	piece_values[eg][0] = piece_values[eg][1] = 0;
	piece_values[eg][w_pawn] = piece_values[eg][b_pawn] = pawn_eg;
	piece_values[eg][w_knight] = piece_values[eg][b_knight] = knight_eg;
	piece_values[eg][w_bishop] = piece_values[eg][b_bishop] = bishop_eg;
	piece_values[eg][w_rook] = piece_values[eg][b_rook] = rook_eg;
	piece_values[eg][w_queen] = piece_values[eg][b_queen] = queen_eg;
	piece_values[eg][w_king] = piece_values[eg][b_king] = 0;
	non_pawn_value[0] = non_pawn_value[1] = 0;
	non_pawn_value[w_pawn] = non_pawn_value[b_pawn] = 0;
	non_pawn_value[w_knight] = non_pawn_value[b_knight] = knight_mg;
	non_pawn_value[w_bishop] = non_pawn_value[b_bishop] = bishop_mg;
	non_pawn_value[w_rook] = non_pawn_value[b_rook] = rook_mg;
	non_pawn_value[w_queen] = non_pawn_value[b_queen] = queen_mg;
	non_pawn_value[w_king] = non_pawn_value[b_king] = 0;
	for (int victim = no_piece; victim <= b_king; victim++)
		for (int attacker = 0; attacker <= b_king; attacker++)
		{
			mvvlva[victim][attacker] = piece_values[mg][victim] - attacker;
		}
}

