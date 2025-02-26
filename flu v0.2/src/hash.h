#pragma once
#include <cstdint>
#include <random>
#include "enum.h"

inline constexpr int flu_hash_mb = 128;
inline constexpr int flu_material_entries = 65536;
inline constexpr int flu_material_hash_size_mask = flu_material_entries - 1;
inline constexpr int flu_pawn_entries = 16384;
inline constexpr int flu_pawn_hash_size_mask = flu_pawn_entries - 1;
inline constexpr uint8_t flu_flag_alpha = 1;
inline constexpr uint8_t flu_flag_beta = 2;
inline constexpr uint8_t flu_flag_exact = 3;

struct flu_hash_entry
{
	int16_t flu_static_eval;
	int16_t flu_value;
	flu_move flu_movecode;
	uint16_t flu_hashupper;
	uint8_t flu_depth;
	uint8_t flu_flags;
};

inline uint8_t flu_hashentry_flag(const flu_hash_entry* flu_tte)
{
	return flu_tte->flu_flags & 0x3;
}

inline uint8_t flu_hashentry_age(const flu_hash_entry* flu_tte)
{
	return flu_tte->flu_flags >> 2;
}

struct flu_hash_bucket
{
	flu_hash_entry flu_entries[3];
	char flu_padding[2];
};

struct flu_hash_table
{
	flu_hash_bucket* flu_table;
	uint64_t flu_size_mask;
	uint64_t flu_table_size;
	uint8_t flu_generation;
	void* flu_mem;
};

extern flu_hash_table flu_hash;

class flu_prng
{
	static uint64_t flu_rand64()
	{
		std::random_device flu_rd;
		std::mt19937_64 flu_gen(flu_rd());
		std::uniform_int_distribution<uint64_t> flu_dis;
		return flu_dis(flu_gen);
	}
public:
	uint64_t flu_s;
	explicit flu_prng(const uint64_t flu_seed) : flu_s(flu_seed)
	{
	}
	static uint64_t flu_rand() { return flu_rand64(); }
};

flu_hash_entry* flu_probe_hash(uint64_t flu_key, bool& flu_hash_hit);
int flu_age_diff(const flu_hash_entry* flu_entry);
int flu_hash_to_score(int flu_score, uint16_t flu_ply);
int flu_hashfull();
int flu_score_to_hash(int flu_score, uint16_t flu_ply);
void flu_clear_hash();
void flu_init_hash();
void flu_reset_hash(int flu_mb);
void flu_save_entry(flu_hash_entry* flu_entry, uint64_t flu_key, flu_move flu_m, int flu_depth, int flu_score, int flu_static_eval, uint8_t flu_flag);
void flu_start_search();
