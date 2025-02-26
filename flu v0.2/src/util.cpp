#include <iostream>
#include <sstream>
#include <vector>
#include "position.h"
#include "search.h"
#include "chrono.h"
#include "thread.h"
#include "util.h"
#if defined(__linux__) && !defined(__ANDROID__)
#include <sys/mman.h>
#endif
//-------------------------------------------//
void* flu_alloc_aligned_mem(const size_t flu_alloc_size, void*& flu_mem)
{
	constexpr size_t flu_alignment = 64;
	const size_t flu_size = flu_alloc_size + flu_alignment - 1;
	flu_mem = malloc(flu_size);
	const auto flu_ret = reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(flu_mem) + flu_alignment - 1 & ~(flu_alignment - 1));
	return flu_ret;
}

std::vector<std::string> flu_split_string(const char* flu_c)
{
	const std::string flu_ss(flu_c);
	std::vector<std::string> flu_out;
	std::istringstream flu_iss(flu_ss);
	for (std::string flu_s; flu_iss >> flu_s;)
		flu_out.push_back(flu_s);
	return flu_out;
}

unsigned char flu_algebraic_to_index(const std::string& flu_s)
{
	const char flu_file = flu_s[0] - 'a';
	const char flu_rank = flu_s[1] - '1';
	return flu_rank << 3 | flu_file;
}
//-------------------------------------------//
flu_piece_type flu_get_piece_type(const char flu_c)
{
	switch (flu_c)
	{
	case 'n':
	case 'N':
		return flu_knight;
	case 'b':
	case 'B':
		return flu_bishop;
	case 'r':
	case 'R':
		return flu_rook;
	case 'q':
	case 'Q':
		return flu_queen;
	case 'k':
	case 'K':
		return flu_king;
	default:
		break;
	}
	return flu_blanktype;
}
//-------------------------------------------//
char flu_piece_char(const flu_piece_code flu_c, const bool flu_lower)
{
	const auto flu_p = static_cast<flu_piece_type>(flu_c >> 1);
	const int flu_col = flu_c & 1;
	char flu_o{};
	switch (flu_p)
	{
	case flu_pawn:
		flu_o = 'p';
		break;
	case flu_knight:
		flu_o = 'n';
		break;
	case flu_bishop:
		flu_o = 'b';
		break;
	case flu_rook:
		flu_o = 'r';
		break;
	case flu_queen:
		flu_o = 'q';
		break;
	case flu_king:
		flu_o = 'k';
		break;
	case flu_blanktype:
		break;
	default:
		flu_o = ' ';
		break;
	}
	if (!flu_lower && !flu_col)
		flu_o = static_cast<char>(flu_o + ('A' - 'a'));
	return flu_o;
}
//-------------------------------------------//
std::string flu_move_to_str(const flu_move flu_code)
{
	char flu_s[100];
	if (flu_code == 65 || flu_code == 0)
		return "none";
	const int flu_from = flu_from_sq(flu_code);
	int flu_to = flu_to_sq(flu_code);
	char flu_prom_char = 0;
	if (flu_type_of(flu_code) == flu_promotion)
		flu_prom_char = flu_piece_char(static_cast<flu_piece_code>(flu_promotion_type(flu_code) * 2), true);
	if (flu_type_of(flu_code) == flu_castling)
	{
		const int flu_side = flu_from > 56 ? 1 : 0;
		const int flu_castle_index = 2 * flu_side + (flu_to > flu_from ? 1 : 0);
		flu_to = flu_castle_king_to[flu_castle_index];
	}
	sprintf(flu_s, "%c%d%c%d%c", (flu_from & 0x7) + 'a', (flu_from >> 3 & 0x7) + 1, (flu_to & 0x7) + 'a', (flu_to >> 3 & 0x7) + 1, flu_prom_char);
	return flu_s;
}
//-------------------------------------------//
void flu_bench()
{
	uint64_t flu_nodes = 0;
	const int flu_bench_start = flu_time_now();
	flu_is_timeout = false;
	flu_limits.moves_to_go = 0;
	flu_limits.time_left = 0;
	flu_limits.increment = 0;
	flu_limits.move_time = 0;
	flu_limits.depth_limit = 16;
	flu_limits.time_is_limited = false;
	flu_limits.depth_is_limited = true;
	flu_limits.infinite = false;
	for (int flu_i = 0; flu_i < 71; flu_i++)
	{
		std::cout << "\nPosition " << flu_i + 1 << "/71" << std::endl;
		flu_clear_threads();
		flu_clear_hash();
		FluPosition* flu_p = flu_import_fen(flu_fen_positions[flu_i].c_str(), 0);
		flu_get_ready();
		flu_think(flu_p);
		flu_nodes += flu_main_thread.flu_nodes;
	}
	const int flu_time_taken = flu_time_now() - flu_bench_start;
	std::cout << std::endl;
	std::cout << "Time  " << flu_time_taken << std::endl;
	std::cout << "Nodes " << flu_nodes << std::endl;
	std::cout << "Noders/Sec   " << flu_nodes * 1000 / (static_cast<unsigned long long>(flu_time_taken) + 1) << std::endl;
}