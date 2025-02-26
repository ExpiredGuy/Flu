#pragma once

struct flu_time_info
{
	bool flu_depth_is_limited;
	bool flu_infinite;
	bool flu_time_is_limited;
	int flu_depth_limit;
	int flu_increment;
	int flu_moves_to_go;
	int flu_move_time;
	int flu_time_left;
};

inline int flu_ideal_usage;
inline int flu_max_usage;
inline int flu_move_overhead = 100;
inline int flu_start_time;
inline int flu_depth_limit;
inline int flu_timer_count;
inline flu_time_info flu_limits;
inline timeval flu_curr_time;
inline timeval flu_start_ts;

int flu_time_now();

inline int flu_time_elapsed()
{
	return flu_time_now() - flu_start_time;
}

using flu_time_tuple = struct flu_timetuple
{
	int flu_optimum_time;
	int flu_maximum_time;
};

flu_time_tuple flu_calculate_time();
