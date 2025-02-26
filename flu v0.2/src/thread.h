#pragma once
#include <array>
#include <csetjmp>
#include "search.h"
#include "hash.h"
//-------------------------------------------//
#pragma warning(disable: 4324)
//-------------------------------------------//
struct flu_pawnhash_entry
{
	int flu_king_pos[2];
	int flu_pawn_shelter[2];
	flu_score flu_scores[2];
	uint64_t flu_attack_spans[2];
	uint64_t flu_passed_pawns[2];
	uint64_t flu_pawn_hash;
	uint8_t flu_castling;
	uint8_t flu_semiopen_files[2];
};
//-------------------------------------------//
struct flu_materialhash_entry
{
	bool flu_is_special_endgame;
	bool flu_is_drawn;
	int (*flu_evaluation)(const FluPosition&);
	int flu_phase;
	flu_score flu_score;
	uint64_t flu_key;
};
//-------------------------------------------//
struct flu_searchthread
{
	bool flu_do_nmp;
	int flu_root_height;
	int16_t flu_history_table[2][64][64];
	int16_t flu_seldepth;
	jmp_buf flu_jbuffer;
	flu_materialhash_entry flu_material_table[flu_material_entries];
	flu_move flu_counter_move_table[14][64];
	flu_pawnhash_entry flu_pawn_table[flu_pawn_entries];
	flu_piece_to_history flu_counter_move_history[14][64];
	FluPosition flu_position;
	flu_search_info flu_ss[flu_max_ply + 2];
	uint16_t flu_thread_id;
	uint64_t flu_nodes;
};
//-------------------------------------------//
inline int flu_num_threads = 1;
//-------------------------------------------//
inline bool flu_is_main_thread(const FluPosition* flu_p) { return flu_p->flu_my_thread->flu_thread_id == 0; }
//-------------------------------------------//
inline flu_searchthread flu_main_thread;
inline flu_searchthread* flu_search_threads;
void flu_clear_threads();
void flu_get_ready();
void flu_init_threads();
void flu_reset_threads(int flu_thread_num);
void* flu_get_thread(int flu_thread_id);
