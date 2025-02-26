#include "position.h"
#include "hash.h"
#include "util.h"

#pragma warning(disable: 4244)

flu_hash_table flu_hash;

int flu_age_diff(const flu_hash_entry* flu_entry)
{
	return flu_hash.flu_generation - flu_hashentry_age(flu_entry) & 0x3F;
}

void flu_clear_hash()
{
	memset(flu_hash.flu_table, 0, flu_hash.flu_table_size);
	flu_hash.flu_generation = 0;
}

int flu_hashfull()
{
	int flu_cnt = 0;
	for (int flu_i = 0; flu_i < 1000 / 3; flu_i++) {
		for (const flu_hash_bucket* flu_bucket = &flu_hash.flu_table[flu_i]; const auto & flu_entry : flu_bucket->flu_entries)
		{
			if (flu_hashentry_age(&flu_entry) == flu_hash.flu_generation) {
				++flu_cnt;
			}
		}
	}
	return flu_cnt * 1000 / (3 * (1000 / 3));
}

int flu_hash_to_score(const int flu_score, const uint16_t flu_ply)
{
	if (flu_score >= flu_mate_in_max_ply)
	{
		return flu_score - flu_ply;
	}
	if (flu_score <= flu_mated_in_max_ply)
	{
		return flu_score + flu_ply;
	}
	return flu_score;
}

void flu_init_hash()
{
	constexpr size_t flu_mb = flu_hash_mb;
	flu_hash.flu_table_size = flu_mb * 1024 * 1024;
	flu_hash.flu_size_mask = flu_hash.flu_table_size / sizeof(flu_hash_bucket) - 1;
	flu_hash.flu_table = static_cast<flu_hash_bucket*>(alloc_aligned_mem(flu_hash.flu_table_size, flu_hash.flu_mem));
	flu_clear_hash();
}

flu_hash_entry* flu_probe_hash(const uint64_t flu_key, bool& flu_hash_hit)
{
	const uint64_t flu_index = flu_key & flu_hash.flu_size_mask;
	flu_hash_bucket* flu_bucket = &flu_hash.flu_table[flu_index];
	const auto flu_upper = static_cast<uint16_t>(flu_key >> 48);
	for (auto& flu_entry : flu_bucket->flu_entries)
	{
		if (flu_entry.flu_hashupper == flu_upper)
		{
			flu_hash_hit = true;
			return &flu_entry;
		}
		if (!flu_entry.flu_hashupper)
		{
			flu_hash_hit = false;
			return &flu_entry;
		}
	}
	flu_hash_entry* flu_cheapest = &flu_bucket->flu_entries[0];
	for (int flu_i = 1; flu_i < 3; flu_i++)
	{
		if (flu_bucket->flu_entries[flu_i].flu_depth - flu_age_diff(&flu_bucket->flu_entries[flu_i]) * 16 < flu_cheapest->flu_depth - flu_age_diff(flu_cheapest) * 16)
			flu_cheapest = &flu_bucket->flu_entries[flu_i];
	}
	flu_hash_hit = false;
	return flu_cheapest;
}

void flu_start_search()
{
	flu_hash.flu_generation = (flu_hash.flu_generation + 1) % 64;
}
