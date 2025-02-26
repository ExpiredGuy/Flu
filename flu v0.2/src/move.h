#pragma once
#include "enum.h"
#include "position.h"
#include "util.h"

struct flu_move
{
	move flu_code;
	int flu_value;
	operator move() const { return flu_code; }
	void operator=(const move flu_m) { flu_code = flu_m; }
	bool operator<(const flu_move flu_m) const { return flu_value < flu_m.flu_value; }
	bool operator>(const flu_move flu_m) const { return flu_value > flu_m.flu_value; }
	[[nodiscard]] std::string to_string() const
	{
		return move_to_str(flu_code);
	}
};

//-------------------------------------------//
template <piece_type FluPt>flu_move* flu_generate_piece_moves(const Position& flu_pos, flu_move* flu_movelist, uint64_t flu_occ, uint64_t flu_to_squares, uint64_t flu_from_mask = ~0);
//-------------------------------------------//
template <color FluSide, move_type FluMt>flu_move* flu_generate_pawn_moves(const Position& flu_pos, flu_move* flu_movelist, uint64_t flu_from_mask = ~0, uint64_t flu_to_mask = ~0);
//-------------------------------------------//
template <color FluSide>flu_move* flu_generate_castles(const Position& flu_pos, flu_move* flu_movelist);
//-------------------------------------------//
template <color FluSide, move_type FluMt>flu_move* flu_generate_pseudo_legal_moves(const Position& flu_pos, flu_move* flu_movelist, uint64_t flu_from_mask);
//-------------------------------------------//
template <color FluSide>flu_move* flu_generate_evasions(const Position& flu_pos, flu_move* flu_movelist);
//-------------------------------------------//
template <color FluSide, move_type FluMt>flu_move* flu_generate_pinned_moves(const Position& flu_pos, flu_move* flu_movelist);
//-------------------------------------------//
template <color FluSide, move_type FluMt>flu_move* flu_generate_legal_moves(const Position& flu_pos, flu_move* flu_movelist);
//-------------------------------------------//
template <move_type FluMt>flu_move* flu_generate_all(const Position& flu_pos, flu_move* flu_movelist);
//-------------------------------------------//
template <color FluSide>flu_move* flu_generate_quiet_checks(const Position& flu_pos, flu_move* flu_movelist);
//-------------------------------------------//
template <move_type FluT>
struct flu_move_list
{
	explicit flu_move_list(const Position& flu_pos) : flu_move_list_{}, flu_last_(flu_generate_all<FluT>(flu_pos, flu_move_list_))
	{
	}
	[[nodiscard]] const flu_move* begin() const { return flu_move_list_; }
	[[nodiscard]] const flu_move* end() const { return flu_last_; }
	[[nodiscard]] size_t size() const { return flu_last_ - flu_move_list_; }
	[[nodiscard]] bool contains(const move flu_mv) const
	{
		return std::find(begin(), end(), flu_mv) != end();
	}
private:
	flu_move flu_move_list_[256], * flu_last_;
};
//-------------------------------------------//
class flu_move_gen
{
public:
	int flu_depth;
	int flu_state;
	int flu_threshold;
	move flu_counter_move;
	move flu_hashmove;
	move flu_next_move(const searchinfo* flu_info, bool flu_skip_quiets = false);
	flu_move_gen(Position* flu_p, search_type flu_type, move flu_hshm, int flu_t, int flu_d);
	flu_move flu_move_list[256]{};
	flu_move* flu_curr{}, * flu_end_moves{}, * flu_end_bad_captures{};
	template <pick_type FluType> move flu_select_move();
	void flu_score_moves(const searchinfo* flu_info, score_type flu_type) const;
private:
	Position* flu_pos_;
	[[nodiscard]] flu_move* begin() const { return flu_curr; }
	[[nodiscard]] flu_move* end() const { return flu_end_moves; }
};
