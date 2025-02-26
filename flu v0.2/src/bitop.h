#pragma once
#include <cstdint>

#if defined(_WIN32) || defined(_WIN64)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#else
#  include <sys/time.h>
#endif

#if defined(_MSC_VER)
#include <bit>
inline int flu_popcnt(const uint64_t flu_bb) { return std::popcount(flu_bb); }
inline int flu_lsb(const uint64_t flu_bb) { return std::countr_zero(flu_bb); }
#elif defined(__GNUC__)
inline int flu_popcnt(uint64_t flu_bb) { return __builtin_popcountll(flu_bb); }
inline int flu_lsb(uint64_t flu_bb) { return __builtin_ctzll(flu_bb); }
#endif

inline int flu_pop_lsb(uint64_t& flu_bb)
{
    const uint64_t flu_x = flu_bb;
    flu_bb &= flu_bb - 1;
    return flu_lsb(flu_x);
}
