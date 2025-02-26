#include <algorithm>
#include "position.h"
#include "board.h"
#include "move.h"
#include "search.h"
#include "thread.h"

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#pragma warning(disable: 4244)
#pragma warning(disable: 5054)
#else
#pragma GCC diagnostic ignored "-Wimplicit-fallthrough="
#pragma GCC diagnostic ignored "-Wdeprecated-enum-enum-conversion"
#endif

template <flu_piece_type FluPt>
flu_move* flu_generate_piece_moves(const Position& flu_pos, flu_move* flu_movelist, const uint64_t flu_occ, const uint64_t flu_to_squares, const uint64_t flu_from_mask)
{
	const flu_piece_code flu_pc = flu_make_piece(flu_pos.flu_active_side, FluPt);
	uint64_t flu_from_squares = flu_pos.flu_piece_bb[flu_pc] & flu_from_mask;
	uint64_t flu_tobits = 0ULL;
	while (flu_from_squares)
	{
		const int flu_from = flu_pop_lsb(flu_from_squares);
		if (FluPt == flu_knight)
			flu_tobits = flu_pseudo_attacks[flu_knight][flu_from] & flu_to_squares;
		if (FluPt == flu_bishop || FluPt == flu_queen)
			flu_tobits |= flu_bishop_attacks(flu_occ, flu_from) & flu_to_squares;
		if (FluPt == flu_rook || FluPt == flu_queen)
			flu_tobits |= flu_rook_attacks(flu_occ, flu_from) & flu_to_squares;
		if (FluPt == flu_king)
			flu_tobits = flu_pseudo_attacks[flu_king][flu_from] & flu_to_squares & ~flu_pos.flu_bad_squares();
		while (flu_tobits)
		{
			const int flu_to = flu_pop_lsb(flu_tobits);
			*flu_movelist++ = flu_make_move(flu_from, flu_to, flu_normal);
		}
	}
	return flu_movelist;
}

template <flu_color FluSide, flu_move_type FluMt>
flu_move* flu_generate_pawn_moves(const Position& flu_pos, flu_move* flu_movelist, const uint64_t flu_from_mask = ~0, uint64_t flu_to_mask = ~0);

template <flu_color FluSide>
flu_move* flu_generate_castles(const Position& flu_pos, flu_move* flu_movelist);

template <flu_color FluSide, flu_move_type FluMt>
flu_move* flu_generate_pseudo_legal_moves(const Position& flu_pos, flu_move* flu_movelist, const uint64_t flu_from_mask);

template <flu_color FluSide>
flu_move* flu_generate_evasions(const Position& flu_pos, flu_move* flu_movelist);

template <flu_color FluSide, flu_move_type FluMt>
flu_move* flu_generate_pinned_moves(const Position& flu_pos, flu_move* flu_movelist);

template <flu_color FluSide, flu_move_type FluMt>
flu_move* flu_generate_legal_moves(const Position& flu_pos, flu_move* flu_movelist);

template <flu_move_type FluMt>
flu_move* flu_generate_all(const Position& flu_pos, flu_move* flu_movelist);

template <flu_color FluSide>
flu_move* flu_generate_quiet_checks(const Position& flu_pos, flu_move* flu_movelist);
