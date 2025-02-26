#pragma once
#include "defs.h"
#include "enum.h"

flu_piece_type flu_get_piece_type(char flu_c);
inline constexpr uint64_t flu_rank1_bb = 0xFF;
inline constexpr uint64_t flu_rank2_bb = flu_rank1_bb << 8 * 1;
inline constexpr uint64_t flu_rank3_bb = flu_rank1_bb << 8 * 2;
inline constexpr uint64_t flu_rank4_bb = flu_rank1_bb << 8 * 3;
inline constexpr uint64_t flu_rank5_bb = flu_rank1_bb << 8 * 4;
inline constexpr uint64_t flu_rank6_bb = flu_rank1_bb << 8 * 5;
inline constexpr uint64_t flu_rank7_bb = flu_rank1_bb << 8 * 6;
inline constexpr uint64_t flu_rank8_bb = flu_rank1_bb << 8 * 7;
inline constexpr uint64_t flu_filea_bb = 0x0101010101010101ULL;
inline constexpr uint64_t flu_fileb_bb = flu_filea_bb << 1;
inline constexpr uint64_t flu_filec_bb = flu_filea_bb << 2;
inline constexpr uint64_t flu_filed_bb = flu_filea_bb << 3;
inline constexpr uint64_t flu_filee_bb = flu_filea_bb << 4;
inline constexpr uint64_t flu_filef_bb = flu_filea_bb << 5;
inline constexpr uint64_t flu_fileg_bb = flu_filea_bb << 6;
inline constexpr uint64_t flu_fileh_bb = flu_filea_bb << 7;
inline constexpr uint64_t flu_file_ah = flu_filea_bb | flu_fileh_bb;
inline constexpr uint64_t flu_file_bb[8] = { flu_filea_bb, flu_fileb_bb, flu_filec_bb, flu_filed_bb, flu_filee_bb, flu_filef_bb, flu_fileg_bb, flu_fileh_bb };

constexpr flu_color operator~(const flu_color flu_c)
{
	return static_cast<flu_color>(flu_c ^ flu_black);
}

constexpr flu_direction flu_pawn_push(const flu_color flu_c)
{
	return flu_c == flu_white ? flu_north : flu_south;
}

constexpr flu_special_type flu_type_of(const uint16_t flu_m)
{
	return static_cast<flu_special_type>(flu_m >> 14 & 3);
}

constexpr int flu_from_sq(const uint16_t flu_m)
{
	return flu_m >> 6 & 0x3F;
}

constexpr int flu_to_sq(const uint16_t flu_m)
{
	return flu_m & 0x3F;
}

constexpr int flu_from_to(const uint16_t flu_m)
{
	return flu_m & 0xFFF;
}

constexpr flu_piece_type flu_promotion_type(const uint16_t flu_m)
{
	return static_cast<flu_piece_type>((flu_m >> 12 & 3) + flu_knight);
}