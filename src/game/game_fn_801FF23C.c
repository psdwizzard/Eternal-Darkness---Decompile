typedef signed short s16;
typedef unsigned char u8;

typedef struct Record {
    void* objects[11];
    u8 pad_2C[0x30];
    s16 ids[11];
} Record;

typedef struct Context {
    u8 data[20];
} Context;

extern int lbl_8064D7D8;
extern Context lbl_8063F020[2];
extern void** fn_801FF2F8(Context*, s16);

void fn_801FF23C(int count, Record* unused, Record* records)
{
    u8* id;
    void** object;
    int i;
    int j;

    for (i = 0; i < count; i++) {
        id = (u8*)records;
        object = records->objects;

        for (j = 0; j < 11; j++, id += 2, object++) {
            if (*(s16*)(id + 0x5C) != -1) {
                void** found = fn_801FF2F8(&lbl_8063F020[lbl_8064D7D8 ^ 1],
                                           *(s16*)(id + 0x5C));
                if (found == 0) {
                    *object = 0;
                    *(s16*)(id + 0x5C) = -1;
                } else {
                    *object = *found;
                }
            } else {
                *object = 0;
            }
        }
        records++;
    }
}
