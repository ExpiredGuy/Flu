#pragma once
#include "enum.h"

struct flu_pst
{
	score flu_psqt[14][64];
};

inline flu_pst flu_psq;
void flu_init_values();
