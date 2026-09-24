typedef signed char s8;
typedef unsigned char u8;

extern void fn_8018E230(u8*, u8*, u8, u8, s8, u8);
extern void fn_8018E8B8(u8*, u8, int);

void fn_80198C8C(u8* object, u8 mode, u8 value, s8 step, u8 kind, u8 limit)
{
    u8* entry = *(u8**)(object + 0x4c);
    u8 count = object[1];
    int i;

    if (mode == 6) {
        object[0xa2] = 9;
        if (limit != 0) {
            if (entry[7] != 0 && limit >= entry[7])
                goto done;
            entry[4] = value;
            entry[5] = step;
            entry[1] = kind;
            entry[7] = limit;
        } else {
            u8 level;
            u8 half;
            u8* p;

            half = count >> 1;
            level = (step / 2) * ((value - 150) / step) + 60;
            entry[1] = kind;
            entry[5] = step;
            p = *(u8**)(object + 0x4c);
            for (i = 0; i < count; i++) {
                p[0x2b] = level;
                p += 0x38;
            }
            p = *(u8**)(object + 0x4c);
            for (i = 0; i < half; i++) {
                p[0x2f] = level;
                p += 0x38;
            }
            p = *(u8**)(object + 0x4c) + half * 0x38;
            for (i = 0; i < half; i++) {
                p[0x2f] = value;
                p += 0x38;
            }
        }
    } else {
        object[0xa2] = 8;
        if (limit != 0) {
            if (entry[7] != 0 && limit >= entry[7])
                goto done;
            for (i = 0; i < count;) {
                fn_8018E230(entry, entry + 4, mode, value, step, kind);
                entry[7] = limit;
                entry += 0x38;
                i++;
            }
        } else {
            for (i = 0; i < count;) {
                fn_8018E230(entry, entry + 0x2b, mode, value, step, kind);
                fn_8018E8B8(entry + 0x20, entry[0x2b], 0);
                fn_8018E8B8(entry + 0x20, entry[0x2b], 1);
                entry += 0x38;
                i++;
            }
        }
    }
done:
    object[0xa4] = mode;
}
