#include <algorithm>
#include "position.h"
#include "chrono.h"

int flu_time_now()
{
#if defined(_WIN64)
	return static_cast<int>(GetTickCount64());
#else
	struct timeval flu_tv;
	int flu_secsInMilli, flu_usecsInMilli;
	gettimeofday(&flu_tv, NULL);
	flu_secsInMilli = (flu_tv.tv_sec) * 1000;
	flu_usecsInMilli = flu_tv.tv_usec / 1000;
	return flu_secsInMilli + flu_usecsInMilli;
#endif
}

flu_time_tuple flu_calculate_time()
{
	int flu_optimaltime;
	int flu_maxtime;
	if (flu_limits.flu_time_is_limited)
	{
		return {flu_limits.flu_move_time, flu_limits.flu_move_time};
	}
	if (flu_limits.flu_moves_to_go == 1)
	{
		return {flu_limits.flu_time_left - flu_move_overhead, flu_limits.flu_time_left - flu_move_overhead};
	}
	if (flu_limits.flu_moves_to_go == 0)
	{
		flu_optimaltime = flu_limits.flu_time_left / 50 + flu_limits.flu_increment;
		flu_maxtime = std::min(6 * flu_optimaltime, flu_limits.flu_time_left / 4);
	}
	else
	{
		const int flu_movestogo = flu_limits.flu_moves_to_go;
		flu_optimaltime = flu_limits.flu_time_left / (flu_movestogo + 5) + flu_limits.flu_increment;
		flu_maxtime = std::min(6 * flu_optimaltime, flu_limits.flu_time_left / 4);
	}
	flu_optimaltime = std::min(flu_optimaltime, flu_limits.flu_time_left - flu_move_overhead);
	flu_maxtime = std::min(flu_maxtime, flu_limits.flu_time_left - flu_move_overhead);
	return {flu_optimaltime, flu_maxtime};
}