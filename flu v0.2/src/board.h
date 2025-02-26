#pragma once
#include <cstdint>
#include "magic.h"

constexpr uint64_t flu_rook_magics[] = {
	0x0a80004000801220, 0x8040004010002008, 0x2080200010008008, 0x1100100008210004,
	0xc200209084020008, 0x2100010004000208, 0x0400081000822421, 0x0200010422048844,
	0x0800800080400024, 0x0001402000401000, 0x3000801000802001, 0x4400800800100083,
	0x0904802402480080, 0x4040800400020080, 0x0018808042000100, 0x4040800080004100
};

constexpr uint64_t flu_bishop_magics[] = {
	0x40106000a1160020, 0x0020010250810120, 0x2010010220280081, 0x002806004050c040,
	0x0002021018000000, 0x2001112010000400, 0x0881010120218080, 0x1030820110010500,
	0x0000120222042400, 0x2000020404040044, 0x8000480094208000, 0x0003422a02000001,
	0x000a220210100040, 0x8004820202226000, 0x0018234854100800, 0x0100004042101040
};

inline int flu_mvvlva[14][14];
inline int flu_reductions[2][64][64];
inline int flu_square_distance[64][64];
inline s_magic flu_bishop_tbl[64];
inline s_magic flu_rook_tbl[64];
inline uint64_t flu_antidiag_masks[64];
inline uint64_t flu_battacks[5248];
inline uint64_t flu_between_masks[64][64];
inline uint64_t flu_bishop_masks[64];
inline uint64_t flu_castling_rights[64];
inline uint64_t flu_color_masks[64];
inline uint64_t flu_diag_masks[64];
inline uint64_t flu_distance_rings[64][8];
inline uint64_t flu_ept_helper[64];
inline uint64_t flu_file_masks[64];
inline uint64_t flu_king_ring[64];
inline uint64_t flu_neighbor_masks[64];
inline uint64_t flu_passed_pawn_masks[2][64];
inline uint64_t flu_pawn_2_pushes[2][64];
inline uint64_t flu_pawn_2_pushesfrom[2][64];
inline uint64_t flu_pawn_attacks[2][64];
inline uint64_t flu_pawn_attacks_from[2][64];
inline uint64_t flu_pawn_blocker_masks[2][64];
inline uint64_t flu_pawn_pushes[2][64];
inline uint64_t flu_pawn_pushesfrom[2][64];
inline uint64_t flu_phalanx_masks[64];
inline uint64_t flu_pseudo_attacks[7][64];
inline uint64_t flu_rank_masks[64];
inline uint64_t flu_r_attacks[102400];
inline uint64_t flu_ray_masks[64][64];
inline uint64_t flu_rook_masks[64];
inline uint64_t flu_square_masks[64];
void flu_init_boards();
uint64_t flu_bishop_attacks(uint64_t flu_occ, int flu_sq);
uint64_t flu_rook_attacks(uint64_t flu_occ, int flu_sq);