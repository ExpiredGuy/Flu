#pragma once
#include <algorithm>
#include "board.h"
using flu_piece_to_history = std::array<std::array<int16_t, 64>, 14>;

struct flu_search_info
{
	bool flu_singular_extension;
	int flu_static_eval;
	int8_t flu_ply;
	flu_move flu_chosen_move;
	flu_move flu_excluded_move;
	flu_move flu_killers[2];
	flu_move flu_pv[flu_max_ply + 1];
	flu_piece_to_history* flu_counter_move_history;
	uint8_t flu_pv_len;
};

inline constexpr int flu_aspiration_init = 15;
inline constexpr int flu_futility_history_limit[2] = { 16000, 9000 };
inline constexpr int flu_improvement_value = 20;
inline constexpr int flu_probcut_margin = 80;
inline constexpr int flu_razor_margin[3] = { 0, 180, 350 };
inline constexpr int flu_singular_depth = 8;
inline constexpr int flu_strong_history = 13000;
inline constexpr int flu_timer_granularity = 2047;

const int flu_futility_move_counts[2][9] = {
	{0, 3, 4, 5, 8, 13, 17, 23, 29},
	{0, 5, 7, 10, 16, 24, 33, 44, 58},
};

static const int flu_skip_size[16] = { 1, 1, 1, 2, 2, 2, 1, 3, 2, 2, 1, 3, 3, 2, 2, 1 };
static const int flu_skip_depths[16] = { 1, 2, 2, 4, 4, 3, 2, 5, 4, 3, 2, 6, 5, 4, 3, 2 };

inline int flu_lmr(const bool flu_improving, const int flu_depth, const int flu_num_moves)
{
	return flu_reductions[flu_improving][std::min(flu_depth, 63)][std::min(flu_num_moves, 63)];
}

inline bool flu_is_depth = false;
inline bool flu_is_infinite = false;
inline bool flu_is_movetime = false;
inline int flu_global_state = 0;
inline int flu_pv_length = 0;
inline flu_move flu_main_pv[flu_max_ply + 1];
inline flu_move flu_ponder_move;
inline volatile bool flu_is_timeout = false, flu_is_pondering = false;

bool flu_is_draw(FluPosition* flu_pos);
inline bool flu_is_valid(flu_move flu_m);
inline uint64_t flu_sum_nodes();
inline void flu_get_time_limit();
inline void flu_history_scores(const FluPosition* flu_pos, const flu_search_info* flu_info, flu_move flu_m, int16_t* flu_history, int16_t* flu_counter_move_history, int16_t* flu_follow_up_history);
inline void flu_initialize_nodes();
int flu_alpha_beta(flu_searchthread* flu_thread, flu_search_info* flu_info, int flu_depth, int flu_alpha, int flu_beta);
int flu_q_search(flu_searchthread* flu_thread, flu_search_info* flu_info, int flu_depth, int flu_alpha, int flu_beta);
int flu_q_search_delta(const FluPosition* flu_pos);
int16_t flu_history_bonus(int flu_depth);
void flu_add_history_bonus(int16_t* flu_history, int16_t flu_bonus);
void flu_check_time(const flu_searchthread* flu_thread);
int flu_print_info(const FluPosition* flu_pos, const flu_search_info* flu_info, int flu_depth, int flu_score, int flu_alpha, int flu_beta);
void flu_save_killer(const FluPosition* flu_pos, flu_search_info* flu_info, flu_move flu_m, int16_t flu_bonus);
void flu_update_countermove_histories(const flu_search_info* flu_info, flu_piece_code flu_pc, int flu_to, int16_t flu_bonus);
void flu_update_heuristics(const FluPosition* flu_pos, flu_search_info* flu_info, int flu_best_score, int flu_beta, int flu_depth, flu_move flu_m, const flu_move* flu_quiets, int flu_quiets_count);
void flu_update_time(bool flu_failed_low, bool flu_same_pv, int flu_init_time);
void* flu_aspiration_thread(void* flu_t);
void* flu_think(void* flu_p);