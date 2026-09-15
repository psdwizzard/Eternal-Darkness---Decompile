typedef signed char s8;
typedef unsigned char u8;

typedef struct Entry {
    u8 pad[0x2b];
    u8 field_2b;
    u8 pad_2c[3];
    u8 field_2f;
    u8 pad_30[8];
} Entry;

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
            u8 half = count >> 1;
            u8 level = (step / 2) * ((value - 150) / step) + 60;
            Entry* records;

            entry[1] = kind;
            entry[5] = step;
            records = *(Entry**)(object + 0x4c);
            for (i = 0; i < count; i++)
                records[i].field_2b = level;
            records = *(Entry**)(object + 0x4c);
            for (i = 0; i < half; i++)
                records[i].field_2f = level;
            records = *(Entry**)(object + 0x4c) + half;
            for (i = 0; i < half; i++)
                records[i].field_2f = value;
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
