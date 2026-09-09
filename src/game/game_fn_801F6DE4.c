#include "game_state_8063C6B8.h"

void fn_801F6DE4(void)
{
    int i;

    for (i = 0; i < 12; i++) {
        if (lbl_8063C6B8[i].field_7c != 0) {
            lbl_8063C6B8[i].field_6c = 0;
            lbl_8063C6B8[i].field_7c = 0;
        }
        if (lbl_8063CD18[i].field_7c != 0) {
            lbl_8063CD18[i].field_6c = 0;
            lbl_8063CD18[i].field_7c = 0;
        }
    }
}
