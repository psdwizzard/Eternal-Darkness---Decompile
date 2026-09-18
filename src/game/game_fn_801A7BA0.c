typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Set {
    u8 pad[0x10];
    u16 count;
    u16 pad12;
    u8* entries;
} Set;

extern char lbl_80251528[];
extern char lbl_8064C298;
extern char lbl_8064C2A0;
extern char lbl_8064C2A4;
extern Set* fn_8015C390(int);
extern void fn_801E5448(s16, s16, const char*, ...);

void fn_801A7BA0(s16 x, s16 y, float scale)
{
    char* strings = lbl_80251528;
    Set* set = fn_8015C390(2);
    int line_y;
    int status_x;
    int detail_x;
    s16 draw_y;
    int i;
    u8* entry;
    if (set != 0) {
        entry = set->entries;
        line_y = y;
        status_x = (s16)x + 230;
        detail_x = (s16)x + 330;
        for (i = 0; i < set->count; i++, entry += 0x74, line_y += 15) {
            char* status;
            u32 flags;
            draw_y = line_y;
            fn_801E5448(x, draw_y, strings + 0x3C, entry + 4,
                        *(char**)(entry + 0x2C), scale);
            flags = *(u32*)(entry + 0x68);
            if (flags & 1) status = &lbl_8064C298;
            else {
                status = &lbl_8064C2A4;
                if (flags & 2) status = &lbl_8064C2A0;
            }
            fn_801E5448(status_x, draw_y, strings + 0x48,
                        *(s16*)(entry + 0x6E), status, scale);
            switch (*(s16*)(entry + 0x6C)) {
            case 0:
                fn_801E5448(detail_x, draw_y, strings + 0x54,
                            *(s16*)(entry + 0x3A), *(s16*)(entry + 0x3C),
                            *(s16*)(entry + 0x3E), scale);
                break;
            case 1:
                fn_801E5448(detail_x, draw_y, strings + 0x6C,
                            *(s16*)(entry + 0x3C), *(s16*)(entry + 0x3E),
                            *(s16*)(entry + 0x40), scale);
                break;
            case 2:
                fn_801E5448(detail_x, draw_y, strings + 0x84,
                            *(s16*)(entry + 0x64), *(s16*)(entry + 0x66), scale);
                break;
            }
        }
    }
}
