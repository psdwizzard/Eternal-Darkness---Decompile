/* fn_80231318 (0x80231318, 448 bytes) */

extern void* memset(void*, int, unsigned int);
extern void fn_802317A4(int prevPos, int pos, int prevValue, int value, float* out);

typedef struct InterpTable {
    char pad0[0xD4];
    int scale;      /* 0xD4 */
    int pos[1];     /* 0xD8 */
} InterpTable;

typedef struct InterpKeys {
    short index[0x80];      /* 0x000 */
    int count;              /* 0x100 */
    char pad104[0x8];
    InterpTable* table;     /* 0x10C */
} InterpKeys;

typedef struct SizeInfo {
    char pad0[0x1C];
    int* sizes;     /* 0x1C */
} SizeInfo;

typedef struct InterpOwner {
    char pad0[0x28];
    int sizeIndex;          /* 0x28 */
    char pad2C[0xC];
    SizeInfo** info;        /* 0x38 */
} InterpOwner;

int fn_80231318(InterpOwner* owner, InterpKeys* keys, int* values, float* out) {
    InterpTable* table = keys->table;
    int size = (*owner->info)->sizes[owner->sizeIndex];
    int n = (int)(size + ((unsigned int)size >> 31)) >> 1;
    int value;
    short* index;
    int pos;
    int i;
    int prevPos;
    int prevValue;
    int raw;

    if (values != 0) {
        index = &keys->index[1];
        pos = 0;
        prevPos = 0;
        prevValue = values[0] * table->scale;
        for (i = 1; i < keys->count; i++) {
            raw = values[*index];
            value = raw & 0x7FFF;
            if (value == raw) {
                pos = table->pos[*index];
                value *= table->scale;
                fn_802317A4(prevPos, pos, prevValue, value, out);
                prevPos = pos;
                prevValue = value;
            }
            index++;
        }

        for (; pos < n; pos++) {
            out[pos] *= (float)prevValue;
        }
        return 1;
    }
    memset(out, 0, n * 4);
    return 0;
}
