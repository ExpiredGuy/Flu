#include <cmath>
#include "position.h"
#include "board.h"
#include "magic.h"

uint64_t flu_bishop_attacks(const uint64_t flu_occ, const int flu_sq)
{
	const s_magic flu_m = flu_bishop_tbl[flu_sq];
	return flu_m.ptr[flu_m.index(flu_occ)];
}

uint64_t flu_rook_attacks(const uint64_t flu_occ, const int flu_sq)
{
	const s_magic flu_m = flu_rook_tbl[flu_sq];
	return flu_m.ptr[flu_m.index(flu_occ)];
}

void flu_init_boards()
{
	for (int flu_i = 1; flu_i < 64; flu_i++)
		for (int flu_j = 1; flu_j < 64; flu_j++)
		{
			flu_reductions[0][flu_i][flu_j] = static_cast<int>(1 + round(log(1.5 * flu_i) * log(flu_j) * 0.55));
			flu_reductions[1][flu_i][flu_j] = static_cast<int>(round(log(1.5 * flu_i) * log(2 * flu_j) * 0.4));
		}
	for (int flu_i = 0; flu_i < 64; flu_i++)
	{
		flu_castling_rights[flu_i] = static_cast<uint64_t>(-1);
		const int flu_rank = FLU_RANK(flu_i);
		const int flu_file = FLU_FILE(flu_i);
		if (flu_rank == 0 && (flu_file == 0 || flu_file == 4))
			flu_castling_rights[flu_i] &= ~flu_wqc_mask;
		if (flu_rank == 0 && (flu_file == 7 || flu_file == 4))
			flu_castling_rights[flu_i] &= ~flu_wkc_mask;
		if (flu_rank == 7 && (flu_file == 0 || flu_file == 4))
			flu_castling_rights[flu_i] &= ~flu_bqc_mask;
		if (flu_rank == 7 && (flu_file == 7 || flu_file == 4))
			flu_castling_rights[flu_i] &= ~flu_bkc_mask;
	}
}