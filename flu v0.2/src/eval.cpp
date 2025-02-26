#include "position.h"
#include "board.h"
#include "eval.h"

#ifdef _MSC_VER
#pragma warning(disable: 4127)
#pragma warning(disable: 4244)
#pragma warning(disable: 5054)
#else
#pragma GCC diagnostic ignored "-Wdeprecated-enum-enum-conversion"
#endif

int flu_evaluate(const Position& flu_p)
{
    int flu_score = 0;
    for (uint8_t flu_i = 0; flu_i < 64; flu_i++)
    {
        if (const piece_code flu_pc = flu_p.mailbox[flu_i]; flu_pc != 0)
        {
            switch (flu_pc)
            {
                case 2: flu_score += flu_piece_values[0][flu_pc]; break;
                case 3: flu_score += flu_piece_values[0][flu_pc]; break;
                case 4: flu_score += flu_piece_values[0][flu_pc]; break;
                case 5: flu_score += flu_piece_values[0][flu_pc]; break;
                case 6: flu_score += flu_piece_values[0][flu_pc]; break;
                case 7: flu_score += flu_piece_values[0][flu_pc]; break;
                case 8: flu_score += flu_piece_values[0][flu_pc]; break;
                case 9: flu_score += flu_piece_values[0][flu_pc]; break;
                case 10: flu_score += flu_piece_values[0][flu_pc]; break;
                case 11: flu_score += flu_piece_values[0][flu_pc]; break;
                default: break;
            }
        }
    }
    return flu_score;
}
