typedef signed short s16;
typedef unsigned int u32;

/*
 * Large bitfield-to-vector dispatcher.  The first family is reconstructed;
 * the remaining families are intentionally preserved as NonMatching C while
 * their repeated case tables are recovered.
 */
void fn_801D3E0C(u32 value, s16* x, s16* y, s16* z)
{
    u32 magnitude;

    switch (value & 0x1F00) {
    case 0x300:
        switch (value & 0xF) {
        case 1:
            magnitude = value & 0x70000;
            switch (magnitude) {
            case 0x10000:
                *x = 0;
                *y = 0;
                *z = -5;
                return;
            case 0x20000:
                *x = 0;
                *y = 0;
                *z = -10;
                return;
            case 0x40000:
                *x = 0;
                *y = 0;
                *z = -15;
                return;
            }
            return;
        case 4:
            magnitude = value & 0x70000;
            switch (magnitude) {
            case 0x10000:
                *x = 0;
                *y = 0;
                *z = -5;
                return;
            case 0x20000:
                *x = 0;
                *y = 0;
                *z = -10;
                return;
            case 0x40000:
                *x = 0;
                *y = 0;
                *z = -15;
                return;
            }
            return;
        default:
            return;
        }
    default:
        return;
    }
}
