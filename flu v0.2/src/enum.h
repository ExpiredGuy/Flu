#include <cstdint>

enum
{
	flu_a1, flu_b1, flu_c1, flu_d1, flu_e1, flu_f1, flu_g1, flu_h1,
	flu_a2, flu_b2, flu_c2, flu_d2, flu_e2, flu_f2, flu_g2, flu_h2,
	flu_a3, flu_b3, flu_c3, flu_d3, flu_e3, flu_f3, flu_g3, flu_h3,
	flu_a4, flu_b4, flu_c4, flu_d4, flu_e4, flu_f4, flu_g4, flu_h4,
	flu_a5, flu_b5, flu_c5, flu_d5, flu_e5, flu_f5, flu_g5, flu_h5,
	flu_a6, flu_b6, flu_c6, flu_d6, flu_e6, flu_f6, flu_g6, flu_h6,
	flu_a7, flu_b7, flu_c7, flu_d7, flu_e7, flu_f7, flu_g7, flu_h7,
	flu_a8, flu_b8, flu_c8, flu_d8, flu_e8, flu_f8, flu_g8, flu_h8
};

inline constexpr int flu_max_ply = 128;
inline constexpr int flu_max_threads = 32;
enum { flu_value_draw = 0, flu_value_mate = 32000, flu_value_inf = 32001, flu_undefined = 32002, flu_timeout = 32003, flu_won_endgame = 10000, flu_mate_in_max_ply = flu_value_mate - flu_max_ply,
	flu_value_mated = -32000, flu_mated_in_max_ply = flu_value_mated + flu_max_ply };
enum flu_castle_sides { flu_queenside, flu_kingside };
enum flu_color { flu_white, flu_black };
enum flu_direction : int { flu_north = 8, flu_east = 1, flu_south = -8, flu_west = -1, flu_north_east = flu_north + flu_east, flu_south_east = flu_south + flu_east, flu_south_west = flu_south + flu_west, flu_north_west = flu_north + flu_west };
enum flu_eval_terms { flu_material, flu_mobility, flu_knights, flu_bishops, flu_rooks, flu_queens, flu_imbalance, flu_pawns, flu_passers, flu_king_safety, flu_threat, flu_total, flu_phase, flu_scale, flu_tempo, flu_term_nb };
enum flu_game_phase { flu_mg, flu_eg };
enum flu_move : uint16_t { flu_move_none, flu_move_null = 65 };
enum flu_move_type { flu_quiet = 1, flu_capture = 2, flu_promote = 4, flu_tactical = 6, flu_all = 7, flu_evasion = 8, flu_quiet_check = 16 };
enum flu_pick_type { flu_next, flu_best };
enum flu_piece_code { flu_no_piece, flu_w_pawn = 2, flu_b_pawn, flu_w_knight, flu_b_knight, flu_w_bishop, flu_b_bishop, flu_w_rook, flu_b_rook, flu_w_queen, flu_b_queen, flu_w_king, flu_b_king };
enum flu_piece_type { flu_blanktype, flu_pawn, flu_knight, flu_bishop, flu_rook, flu_queen, flu_king };
enum flu_score : int { flu_score_draw };
enum flu_score_type { flu_score_quiet, flu_score_capture, flu_score_evasion };
enum flu_search_type { flu_normal_search, flu_quiescence_search, flu_probcut_search };
enum flu_special_type { flu_normal, flu_promotion = 1, flu_enpassant = 2, flu_castling = 3 };
enum flu_stages { flu_hashmove_state = 0, flu_tactical_init, flu_tactical_state, flu_killer_move_2, flu_countermove, flu_quiets_init, flu_quiet_state, flu_bad_tactical_state, flu_evasions_init,
	flu_evasions_state, flu_q_hashmove, flu_q_captures_init, flu_q_captures, flu_q_checks_init, flu_q_checks, flu_probcut_hashmove, flu_probcut_captures_init, flu_probcut_captures };
