typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Record {
    u8 pad00[4];
    char name[0x28];
    char* label;
    u8 pad30[0xA];
    s16 values[4];
    u8 pad42[0x22];
    s16 pair[2];
    u32 flags;
    s16 mode;
    s16 level;
    u8 pad70[4];
} Record;

typedef struct RecordTable {
    u8 pad00[0x10];
    u16 count;
    u16 pad12;
    Record* records;
} RecordTable;

extern char lbl_80251528[];
extern char lbl_8064C298;
extern char lbl_8064C2A0;
extern char lbl_8064C2A4;
extern RecordTable* fn_8015C390(int);
extern void fn_801E5448(s16 x, int y, float scale, const char* format, ...);

void fn_801A7BA0(s16 x, s16 y, float scale)
{
    char* strings = lbl_80251528;
    RecordTable* table = fn_8015C390(2);
    int i;
    Record* entry;

    if (table != 0) {
        entry = table->records;
        for (i = 0; i < table->count; i++, entry++) {
            char* status;
            u32 flags;
            s16 draw_y = y + i * 15;
            fn_801E5448(x, draw_y, scale, strings + 0x3C, entry->name,
                        entry->label);
            flags = entry->flags;
            if (flags & 1) status = &lbl_8064C298;
            else {
                status = &lbl_8064C2A4;
                if (flags & 2) status = &lbl_8064C2A0;
            }
            fn_801E5448(x + 230, draw_y, scale, strings + 0x48,
                        entry->level, status);
            switch (entry->mode) {
            case 0:
                fn_801E5448(x + 330, draw_y, scale, strings + 0x54,
                            entry->values[0], entry->values[1],
                            entry->values[2]);
                break;
            case 1:
                fn_801E5448(x + 330, draw_y, scale, strings + 0x6C,
                            entry->values[1], entry->values[2],
                            entry->values[3]);
                break;
            case 2:
                fn_801E5448(x + 330, draw_y, scale, strings + 0x84,
                            entry->pair[0], entry->pair[1]);
                break;
            }
        }
    }
}
