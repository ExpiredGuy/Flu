#pragma once
#include "position.h"
#include "thread.h"

int flu_evaluate(const Position& flu_p);

inline flu_materialhashentry* flu_get_material_entry(const Position& flu_p)
{
	return &flu_p.my_thread->material_table[flu_p.materialhash & flu_material_hash_size_mask];
}

inline constexpr int flu_pawn_eg = 150;
inline constexpr int flu_pawn_mg = 100;
inline constexpr int flu_knight_eg = 440;
inline constexpr int flu_knight_mg = 370;
inline constexpr int flu_bishop_eg = 530;
inline constexpr int flu_bishop_mg = 430;
inline constexpr int flu_bishop_pair = 80;
inline constexpr int flu_rook_eg = 950;
inline constexpr int flu_rook_mg = 730;
inline constexpr int flu_queen_eg = 1660;
inline constexpr int flu_queen_mg = 1240;
inline constexpr int flu_king_eg = 0;
inline constexpr int flu_king_mg = 0;
inline constexpr int flu_move_tempo = 30;

inline int flu_piece_values[2][14] = {
	{0, 0, flu_pawn_mg, flu_pawn_mg, flu_knight_mg, flu_knight_mg, flu_bishop_mg, flu_bishop_mg, flu_rook_mg, flu_rook_mg, flu_queen_mg, flu_queen_mg, 0, 0},
	{0, 0, flu_pawn_eg, flu_pawn_eg, flu_knight_eg, flu_knight_eg, flu_bishop_eg, flu_bishop_eg, flu_rook_eg, flu_rook_eg, flu_queen_eg, flu_queen_eg, 0, 0}
};

inline int flu_non_pawn_value[14] = { 0, 0, 0, 0, flu_knight_mg, flu_knight_mg, flu_bishop_mg, flu_bishop_mg, flu_rook_mg, flu_rook_mg, flu_queen_mg, flu_queen_mg, 0, 0 };
