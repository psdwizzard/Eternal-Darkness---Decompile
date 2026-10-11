typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Decoder {
    u8 pad0[0x18];
    u32 count;
    u8 pad1[0x60 - 0x1C];
    u8 header[0x20];
    u16 command;
    u16 type;
    u32 size;
    u8 pad2[0x164 - 0x88];
    u32* input;
    u8 pad3[0x16C - 0x168];
    u32 index;
    u32 position;
    u8 pad4[0x188 - 0x174];
    u32 block_pos;
    u32 block_size;
    u8 pad5[0x1AC - 0x190];
    u8 mode;
    u8 pad6;
    u8 active;
} Decoder;

extern int fn_801083B4(void*, int);
extern int fn_80108C2C(Decoder*, int, u32);

int fn_80108ECC(Decoder* dec)
{
    u16 command;
    u16 type;
    u32 size;
    u32 time;
    int pending;
    int result;

    dec->active = 1;
    if (dec->block_pos == *(u32*)((u8*)dec + 0x68) &&
        dec->block_size == *(u32*)((u8*)dec + 0x6C)) {
        dec->position += *(u32*)((u8*)dec + 0x68);
        dec->index++;
        if (dec->index < dec->count) {
            if (dec->mode == 4) return 0;
            if (fn_801083B4(dec->header, 0x14) == -1) return 1;
            dec->block_pos = 0;
            dec->block_size = 0;
        } else {
            return 2;
        }
    }
    if (fn_801083B4(&dec->command, 8) == -1) return 1;
    command = dec->command;
    type = dec->type;
    size = dec->size;
    if (command == 1) {
        if (dec->mode == 4) return 0;
        if (fn_801083B4(dec->input, 4) == -1) return 1;
        time = *dec->input;
        if (dec->mode == 4) return 0;
        if (fn_801083B4(dec->input, size - 4) == -1) return 1;
        for (;;) {
            pending = 1;
            if (dec->mode == 4) return 0;
            result = fn_80108C2C(dec, type, time);
            switch (result) {
            case 1:
                return 1;
            case 2:
                pending = 0;
                break;
            case 3:
                break;
            default:
                if (dec->mode == 4) return 0;
                break;
            }
            if (pending) break;
        }
        dec->block_pos++;
    } else if (command != 0) {
        return 1;
    }
    return 0;
}
