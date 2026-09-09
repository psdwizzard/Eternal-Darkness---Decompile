#include "game_state_8063C6B8.h"

void fn_801F6ED0(void* previous, void* replacement)
{
    int i;

    for (i = 0; i < 12; i++) {
        if (lbl_8063C6B8[i].field_68 == previous ||
            lbl_8063C6B8[i].field_68 == 0) {
            lbl_8063C6B8[i].field_68 = replacement;
        }
        if (lbl_8063CD18[i].field_68 == previous ||
            lbl_8063CD18[i].field_68 == 0) {
            lbl_8063CD18[i].field_68 = replacement;
        }
    }
}
