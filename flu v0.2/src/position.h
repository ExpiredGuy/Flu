#pragma once
#include <string>
#include "bitop.h"
#include "const.h"
#include "enum.h"

//-------------------------------------------//
struct flu_state_history
{
	uint64_t flu_key;
	uint64_t flu_pawnhash;
	uint64_t flu_materialhash;
	uint64_t flu_king_blockers[2][2];
	uint64_t flu_check_bb;
	uint8_t flu_castle_rights;
	int flu_ep_square;
	int flu_kingpos[2];
	int flu_halfmove_clock;
	int flu_fullmove_clock;
	flu_piece_code flu_captured_piece;
};
//-------------------------------------------//
class FluPosition
{
public:
	uint64_t flu_key;
	uint64_t flu_pawnhash;
	uint64_t flu_materialhash;
	uint64_t flu_kingblockers[2][2];
	uint64_t flu_check_bb;
	uint8_t flu_castle_rights;
	int flu_ep_square;
	int flu_kingpos[2];
	int flu_halfmove_clock;
	int flu_fullmove_clock;
	flu_piece_code flu_captured_piece;
	uint64_t flu_piece_bb[14];
	uint64_t flu_occupied_bb[2];
	flu_piece_code flu_mailbox[64];
	int flu_piece_count[14];
	flu_color flu_active_side;
	flu_state_history flu_history_stack[512];
	int flu_history_index;
	flu_move flu_move_stack[512];
	flu_searchthread* flu_my_thread;
	int flu_non_pawn[2];
	bool flu_game_cycle;
	static void flu_init();
	[[nodiscard]] bool flu_is_attacked(int flu_sq, int flu_side) const;
	[[nodiscard]] bool flu_is_capture(flu_move flu_m) const;
	[[nodiscard]] bool flu_is_tactical(flu_move flu_m) const;
	[[nodiscard]] bool flu_is_pseudo_legal(flu_move flu_m) const;
	[[nodiscard]] bool flu_is_legal(flu_move flu_m) const;
	[[nodiscard]] bool flu_pawn_on7_th() const;
	[[nodiscard]] int flu_smallest_attacker(uint64_t flu_attackers, flu_color flu_col) const;
	[[nodiscard]] bool flu_see(flu_move flu_m, int flu_threshold) const;
	[[nodiscard]] uint64_t flu_attackers_to(int flu_sq, int flu_side, bool flu_free = false) const;
	[[nodiscard]] uint64_t flu_attackers_to(int flu_sq, int flu_side, uint64_t flu_occ) const;
	[[nodiscard]] uint64_t flu_all_attackers_to(int flu_sq, uint64_t flu_occ) const;
	[[nodiscard]] uint64_t flu_get_attack_set(int flu_sq, uint64_t flu_occ) const;
	bool flu_gives_check(flu_move flu_m);
	[[nodiscard]] bool flu_gives_discovered_check(flu_move flu_m) const;
	[[nodiscard]] bool flu_advanced_pawn_push(flu_move flu_m) const;
	void flu_do_move(flu_move flu_m);
	void flu_undo_move(flu_move flu_m);
	void flu_do_null_move();
	void flu_undo_null_move();
	void flu_set_piece_at(int flu_sq, flu_piece_code flu_pc);
	void flu_remove_piece_at(int flu_sq, flu_piece_code flu_pc);
	void flu_move_piece(int flu_from, int flu_to, flu_piece_code flu_pc);
	[[nodiscard]] uint64_t flu_bad_squares() const;
	[[nodiscard]] bool flu_horizontal_check(uint64_t flu_occ, int flu_sq) const;
	void flu_update_blockers();
	void flu_read_fen(const char* flu_fen);
};
//-------------------------------------------//
inline bool FluPosition::flu_gives_discovered_check(const flu_move flu_m) const
{
	return (flu_kingblockers[~flu_active_side][0] | flu_kingblockers[~flu_active_side][1]) & FLU_SET_BIT(flu_from_sq(flu_m));
}
//-------------------------------------------//
FluPosition* flu_start_position();
FluPosition* flu_import_fen(const char* flu_fen, int flu_thread_id);
