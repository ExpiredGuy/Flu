#pragma once
constexpr auto flu_engine_name = "Flu";
constexpr auto flu_version = "0.2";
constexpr auto flu_author = "David";

using flu_searchthread = struct flu_search_thread;
using flu_pawnhashtable = struct flu_pawnhash_table;
using flu_searchinfo = struct flu_search_info;
using flu_materialhashentry = struct flu_materialhash_entry;

inline constexpr auto flu_bkc_mask = 0x08;
inline constexpr auto flu_black_castle = 0x0c;
inline constexpr auto flu_bqc_mask = 0x04;
inline constexpr auto flu_promotion_rank_bb = 0xff000000000000ff;
inline constexpr auto flu_side_switch = 0x01;
inline constexpr auto flu_start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
inline constexpr auto flu_white_castle = 0x03;
inline constexpr auto flu_wkc_mask = 0x02;
inline constexpr auto flu_wqc_mask = 0x01;

#define FLU_DOUBLE_PUSH_INDEX(s, x) ((s) ? ((x) - 16) : ((x) + 16))
#define FLU_FILE(x) ((x) & 0x7)
#define FLU_FLIP_SQUARE(s, x) ((s) ? (x) ^ 56 : (x))
#define FLU_INDEX(r,f) (((r) << 3) | (f))
#define FLU_MORE_THAN_ONE(x) ((x) & ((x) - 1))
#define FLU_ONE_OR_ZERO(x) (!FLU_MORE_THAN_ONE(x))
#define FLU_ONLY_ONE(x) (!FLU_MORE_THAN_ONE(x) && (x))
#define FLU_PAWN_ATTACKS(s, x) ((s) ? ((shift<flu_south_east>(x)) | (shift<flu_south_west>(x))) : ((shift<flu_north_east>(x)) | (shift<flu_north_west>(x))))
#define FLU_PAWN_PUSH(s, x) ((s) ? ((x) >> 8) : ((x) << 8))
#define FLU_PAWN_PUSH_INDEX(s, x) ((s) ? ((x) - 8) : ((x) + 8))
#define FLU_PROMOTION_RANK(x) (FLU_RANK(x) == 0 || FLU_RANK(x) == 7)
#define FLU_RANK(x) ((x) >> 3)
#define FLU_R_RANK(x,s) ((s) ? ((x) >> 3) ^ 7 : ((x) >> 3))
#define FLU_S(m, e) flu_make_score(m, e)
#define FLU_SET_BIT(x) (1ULL << (x))
#define FLU_SIDE2_M_SIGN(s) ((s) ? -1 : 1)