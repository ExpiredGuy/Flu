#include "position.h"
#include "hash.h"
#include "uci.h"
#include "util.h"

int main(const int flu_argc, char** flu_argv)
{
	Position::init();
	flu_init_hash();
	if (flu_argc > 1 && strstr(flu_argv[1], "bench"))
		flu_bench();
	else
		flu_loop();
	return 0;
}s