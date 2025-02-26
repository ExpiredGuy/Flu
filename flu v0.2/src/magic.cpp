#include "board.h"
#include "position.h"
#include "magic.h"

uint64_t flu_bishop_attacks_slow(const uint64_t flu_occ, const int flu_sq)
{
	return flu_sliding_attacks_slow(flu_occ, flu_sq, flu_diag_masks, flu_flip_vertical) | flu_sliding_attacks_slow(flu_occ, flu_sq, flu_antidiag_masks, flu_flip_vertical);
}

uint64_t flu_flip_vertical(uint64_t flu_x)
{
	constexpr uint64_t flu_y = 0x00FF00FF00FF00FF;
	constexpr uint64_t flu_z = 0x0000FFFF0000FFFF;
	flu_x = ((flu_x >> 8) & flu_y) | ((flu_x & flu_y) << 8);
	flu_x = ((flu_x >> 16) & flu_z) | ((flu_x & flu_z) << 16);
	flu_x = (flu_x >> 32) | (flu_x << 32);
	return flu_x;
}

void flu_init_magics(uint64_t flu_attack_table[], flu_magic flu_magics[], const uint64_t* flu_masks, uint64_t(*flu_func)(uint64_t, int), const uint64_t* flu_magic_numbers)
{
	int flu_size = 0;
	for (int flu_i = 0; flu_i < 64; flu_i++)
	{
		flu_magic& flu_m = flu_magics[flu_i];
		flu_m.flu_mask = flu_masks[flu_i];
		flu_m.flu_shift = 64 - flu_popcnt(flu_m.flu_mask);
		flu_m.flu_ptr = flu_i == 0 ? flu_attack_table : flu_magics[flu_i - 1].flu_ptr + flu_size;
		flu_m.flu_magic = flu_magic_numbers[flu_i];
		uint64_t flu_n = flu_size = 0;
		do
		{
			flu_m.flu_ptr[flu_m.flu_index(flu_n)] = flu_func(flu_n, flu_i);
			flu_size++;
			flu_n = flu_n - flu_m.flu_mask & flu_m.flu_mask;
		} while (flu_n);
	}
}
//-------------------------------------------//
uint64_t flu_rankattacks(const uint64_t flu_occ, const int flu_sq)
{
	const unsigned int flu_file = flu_sq & 7;
	const unsigned int flu_rkx8 = flu_sq & 56;
	const unsigned int flu_rank_occ_x2 = flu_occ >> flu_rkx8 & static_cast<unsigned long long>(2) * 63;       
	const uint64_t flu_attacks = flu_rank_attacks[4 * flu_rank_occ_x2 + flu_file];         
	return flu_attacks << flu_rkx8;
}
//-------------------------------------------//
uint64_t flu_rook_attacks_slow(const uint64_t flu_occ, const int flu_sq)
{
	return flu_rankattacks(flu_occ, flu_sq) | flu_sliding_attacks_slow(flu_occ, flu_sq, flu_file_masks, flu_flip_vertical);
}
//-------------------------------------------//
uint64_t flu_sliding_attacks_slow(const uint64_t flu_occ, const int flu_sq, const uint64_t* flu_masks, uint64_t(*flu_func)(uint64_t))
{
	uint64_t flu_f = flu_occ & flu_masks[flu_sq];
	uint64_t flu_r = flu_func(flu_f);
	flu_f -= flu_square_masks[flu_sq];
	flu_r -= flu_square_masks[flu_sq ^ 56];
	const uint64_t flu_r2 = flu_func(flu_r);
	flu_f ^= flu_r2;
	flu_f &= flu_masks[flu_sq];
	return flu_f;
}
