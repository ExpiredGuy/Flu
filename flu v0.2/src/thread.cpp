#include <cstring>
#include "position.h"
#include "search.h"
#include "thread.h"
//-------------------------------------------//
void flu_clear_threads()
{
	for (int flu_i = 0; flu_i < flu_num_threads; ++flu_i)
	{
		const auto flu_search_thread = static_cast<flu_searchthread*>(flu_get_thread(flu_i));
		std::memset(&flu_search_thread->flu_history_table, 0, sizeof flu_search_thread->flu_history_table);
		for (int flu_j = 0; flu_j < 14; ++flu_j)
		{
			for (int flu_k = 0; flu_k < 64; ++flu_k)
			{
				for (int flu_l = 0; flu_l < 14; ++flu_l)
				{
					for (int flu_m = 0; flu_m < 64; ++flu_m)
					{
						flu_search_thread->flu_counter_move_history[flu_j][flu_k][flu_l][flu_m] = flu_j < 2 ? -1 : 0;
					}
				}
			}
		}
		for (auto& flu_j : flu_search_thread->flu_counter_move_table)
		{
			for (auto& flu_k : flu_j)
			{
				flu_k = flu_move_none;
			}
		}
	}
}
//-------------------------------------------//
void flu_get_ready()
{
	flu_main_thread.flu_root_height = flu_main_thread.flu_position.flu_history_index;
	for (int flu_i = 1; flu_i < flu_num_threads; ++flu_i)
	{
		const auto flu_t = static_cast<flu_searchthread*>(flu_get_thread(flu_i));
		flu_t->flu_root_height = flu_main_thread.flu_root_height;
		memcpy(&flu_t->flu_position, &flu_main_thread.flu_position, sizeof(FluPosition));
		flu_t->flu_position.flu_my_thread = flu_t;
	}
	for (int flu_i = 0; flu_i < flu_num_threads; flu_i++)
	{
		const auto flu_t = static_cast<flu_searchthread*>(flu_get_thread(flu_i));
		flu_t->flu_do_nmp = true;
		for (auto& flu_s : flu_t->flu_ss)
		{
			flu_search_info* flu_info = &flu_s;
			flu_info->flu_pv[0] = flu_move_none;
			flu_info->flu_pv_len = 0;
			flu_info->flu_ply = 0;
			flu_info->flu_singular_extension = false;
			flu_info->flu_chosen_move = flu_move_none;
			flu_info->flu_excluded_move = flu_move_none;
			flu_info->flu_static_eval = flu_undefined;
			flu_info->flu_killers[0] = flu_info->flu_killers[1] = flu_move_none;
			flu_info->flu_counter_move_history = &flu_t->flu_counter_move_history[flu_no_piece][0];
		}
		memset(&flu_t->flu_pawn_table, 0, sizeof flu_t->flu_pawn_table);
	}
}
//-------------------------------------------//
void* flu_get_thread(const int flu_thread_id) { return flu_thread_id == 0 ? &flu_main_thread : &flu_search_threads[flu_thread_id - 1]; }
//-------------------------------------------//
void flu_init_threads()
{
	flu_search_threads = new flu_searchthread[flu_num_threads - 1];
	for (int flu_i = 0; flu_i < flu_num_threads; ++flu_i)
	{
		static_cast<flu_searchthread*>(flu_get_thread(flu_i))->flu_thread_id = static_cast<uint16_t>(flu_i);
	}
	flu_clear_threads();
}
//-------------------------------------------//
void flu_reset_threads(const int flu_thread_num)
{
	flu_num_threads = flu_thread_num;
	delete[] flu_search_threads;
	flu_search_threads = new flu_searchthread[flu_num_threads - 1];
	for (int flu_i = 1; flu_i < flu_thread_num; ++flu_i)
	{
		static_cast<flu_searchthread*>(flu_get_thread(flu_i))->flu_thread_id = static_cast<uint16_t>(flu_i);
	}
	flu_clear_threads();
	flu_get_ready();
}
